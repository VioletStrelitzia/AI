#include "DecisionTreeBuilder.h"

namespace yuki::atri::dt {
    auto DecisionTreeBuilder::quickSort(vector<pair<Example*, f64>>& examples, Attribute* const& attr, i32 const& left, i32 const& right) -> void {
        if (left < right) {
            // 左闭右闭
            i32 i = left + 1, j = right, p = left;
            swap(examples[left], examples[(left + right) >> 1]);
            while (true) {
                while (examples[i].first->data[attr->index] <= examples[p].first->data[attr->index] && i < right) ++i;
                while (examples[j].first->data[attr->index] >= examples[p].first->data[attr->index] && j > left) --j;
                if (i < j) {
                    swap(examples[i], examples[j]);
                } else {
                    break;
                }
            }
            swap(examples[j], examples[p]);
            quickSort(examples, attr, left, j);
            quickSort(examples, attr, i, right);
        }
    }

    auto DecisionTreeBuilder::quickSort(vector<pair<Example*, f64>>& examples, Attribute* const& attr) -> void {
        quickSort(examples, attr, 0, (i32)examples.size() - 1);
    } 

    auto DecisionTreeBuilder::targetProbDist(Attribute* const& target, vector<pair<Example*, f64>> const& examples) -> unordered_map<f64, f64> {
        unordered_map<f64, f64> PMap;
        f64 n = 0.;
        for (f64 const& targetValue: target->values) {
            PMap[targetValue] = 0.;
        }
        for (pair<Example*, f64> const& exp: examples) {
            PMap[exp.first->target] += exp.second;
            n += exp.second;
        }
        for (f64 const& targetValue: target->values) {
            PMap[targetValue] /= n;
        }
        return PMap;
    }

    auto DecisionTreeBuilder::targetProbDist(Attribute* const& target,vector<pair<Example*, f64>> const& examples,
        i32 const& begin, i32 const& end) -> unordered_map<f64, f64> {
        unordered_map<f64, f64> PMap;
        f64 n = 0.;
        for (f64 const& targetValue: target->values) {
            PMap[targetValue] = 0.;
        }
        for (i32 i = begin; i < end; ++i) {
            PMap[examples[i].first->target] += examples[i].second;
            n += examples[i].second;
        }
        for (f64 const& targetValue: target->values) {
            PMap[targetValue] /= n;
        }
        return PMap;
    }

    auto DecisionTreeBuilder::getTotalWeight(vector<pair<Example*, f64>> const& examples) -> f64 {
        f64 totalWeight = 0.;
        for (pair<Example*, f64> const& exp: examples) {
            totalWeight += exp.second;
        }
        return totalWeight;
    }

    auto DecisionTreeBuilder::getTotalWeight(vector<pair<Example*, f64>> const& examples, i32 const& begin, i32 const& end) -> f64 {
        f64 totalWeight = 0.;
        for (i32 i = begin; i < end; ++i) {
            totalWeight += examples[i].second;
        }
        return totalWeight;
    }

    auto DecisionTreeBuilder::getAvailEx(Attribute* const& attr, vector<pair<Example*, f64>> const& examples) -> vector<pair<Example*, f64>> {
        vector<pair<Example*, f64>> availExamples;
        for (pair<Example*, f64> const& exp: examples) {
            if (exp.first->data[attr->index] != Attribute::ABSENT) {
                availExamples.push_back(exp);
            }
        }
        return availExamples;
    }

    auto DecisionTreeBuilder::sepAbsentEx(Attribute* const& attr, vector<pair<Example*, f64>>& examples) -> vector<pair<Example*, f64>> {
        vector<pair<Example*, f64>> absentExamples;
        i32 end = static_cast<i32>(examples.size());
        for (i32 i = end - 1; i > -1 ;--i) {
            if (examples[i].first->data[attr->index] == Attribute::ABSENT) {
                absentExamples.push_back(examples[i]);
                swap(examples[i], examples[--end]);
            }
        }
        examples.erase(examples.begin() + end, examples.end());
        return absentExamples;
    }

    auto DecisionTreeBuilder::splitExamples(
        Attribute* const& attr,
        vector<pair<Example*, f64>> const& examples
        ) -> vector<vector<pair<Example*, f64>>> {
        vector<vector<pair<Example*, f64>>> subExamples(attr->values.size());
        switch (attr->type) {
        case AttributeType::DISCRETE: {
            i32 i = 0;
            map<f64, i32> index;
            for (f64 const& value: attr->values) {
                index[value] = i;
                ++i;
            }
            for (pair<Example*, f64> const& exp: examples) {
                subExamples[index[exp.first->data[attr->index]]].push_back(exp);
            }
        } break;
        case AttributeType::CONTINUOUS: {
            subExamples.push_back(vector<pair<Example*, f64>>());
            i32 i;
            bool flag;
            // 这里使用遍历匹配区间算法(nm)，而不是先排序再找区间端点(nlogn)，因为 n>>m，前者效率高
            for (pair<Example*, f64> const& exp: examples) {
                // 遍历各个区间，在区间内则加入
                auto cit = attr->values.cbegin();
                auto cnext = ++attr->values.cbegin();
                auto cend = attr->values.cend();
                i = 0, flag = false;

                // 区间 (-, values[0]]
                if (cit != cend && exp.first->data[attr->index] <= *cit) {
                    subExamples[i].push_back(exp);
                    continue;
                }

                // 区间 (values[i-1], values[i]]
                ++i;
                while (cnext != cend) {
                    if (*cit < exp.first->data[attr->index] && exp.first->data[attr->index] <= *cnext) {
                        subExamples[i].push_back(exp);
                        flag = true;
                        break;
                    }
                    ++cit, ++cnext, ++i;
                }
                if (flag) continue;
                
                // 区间 (values[end], +]
                if (cit != cend && exp.first->data[attr->index] > *cit) {
                    subExamples[i].push_back(exp);                  
                }
            }
        } break;
        }
        return subExamples;
    }

    auto DecisionTreeBuilder::mergeExamples(vector<vector<pair<Example*, f64>>>& subExamples, vector<pair<Example*, f64>> const& absentExamples) -> void {
        // 有效样本总权重
        f64 n = 0., p;
        vector<f64> n_k(subExamples.size(), 0.);
        i32 i = 0;
        for (vector<pair<Example*, f64>>& exs: subExamples) {
            for (pair<Example*, f64> const& exp: exs) {
                n_k[i] += exp.second;
                n += exp.second;
            }
            ++i;
        }
        i = 0;
        for (vector<pair<Example*, f64>>& exs: subExamples) {
            // 依有效样本概率分布将缺失值样本划分到各个子集中
            p = n_k[i] / n;
            for (pair<Example*, f64> const& absExp: absentExamples) {
                exs.push_back({ absExp.first, absExp.second * p });
            }
            ++i;
        }
    }

    auto DecisionTreeBuilder::removeAttritude(Attribute* const& attr, vector<Attribute*> const& attributes) -> vector<Attribute*> {
        vector<Attribute*> result;
        for (Attribute* const& a: attributes) {
            if (a->index != attr->index) {
                result.push_back(a);
            }
        }
        return result;
    }

    auto DecisionTreeBuilder::pluralityValue(Attribute* const& target, vector<pair<Example*, f64>> const& examples) -> f64 {
        unordered_map<f64, f64> counts;
        vector<f64> targetV;
        
        for (f64 const& targetValue: target->values) {
            counts[targetValue] = 0;
        }
        for (auto const& p: examples) {
            counts[p.first->target] += p.second;
        }

        targetV.push_back(*(target->values.cbegin()));
        f64 max = counts[targetV.back()];
        for (f64 const& targetValue: target->values) {
            if (max < counts[targetValue]) {
                max = counts[targetValue];
                targetV.clear();
                targetV.push_back(targetValue);
            } else if (max == counts[targetValue]) {
                targetV.push_back(targetValue);                
            }
        }

        return random::choose(targetV);
    }

    bool DecisionTreeBuilder::isSameClassify(vector<pair<Example*, f64>> const& examples) {
        f64 target = examples[0].first->target;
        for (pair<Example*, f64> const& exp: examples) {
            if (exp.first->target != target) {
                return false;
            }
        }
        return true;
    }

    auto DecisionTreeBuilder::entropyRemain(
        Attribute* const& attr,
        Attribute* const& target,
        vector<vector<pair<Example*, f64>>> const& subExamples) -> f64 {
        f64 HL_A = 0.,
            n = 0.;
        vector<f64> n_k(subExamples.size(), 0.);

        i32 i = 0;
        for (vector<pair<Example*, f64>> const& exs: subExamples) {
            for (pair<Example*, f64> const& exp: exs) {
                n_k[i] += exp.second;
                n += exp.second;
            }
            ++i;
        }
        i = 0;
        for (vector<pair<Example*, f64>> const& exs: subExamples) {
            if (!exs.empty()) {
                HL_A += n_k[i] / n * statistics::entropy(targetProbDist(target, exs));
            }
            ++i;
        }
        return HL_A;
    }
    
    auto DecisionTreeBuilder::infoGain(
        Attribute* const& attr,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples) -> f64 {
        f64 HL = 1.,  // 目标属性 target 在样本集的信息熵
            HL_A = DBL_MAX;  // 目标属性 target 在用属性 attr 分割样本集之后的加权信息熵，即条件信息熵
        
        // 计算目标属性 target 在样本集的信息熵
        HL = statistics::entropy(targetProbDist(target, examples));

        switch (attr->type) {
        case AttributeType::DISCRETE: {
            // 如果属性 attr 是离散的，可以直接计算剩余期望熵
            HL_A = entropyRemain(attr, target, splitExamples(attr, examples));
        } break;
        case AttributeType::CONTINUOUS: {
            // 如果属性 attr 是离散的，需要枚举所有取值作为二分点的情况，并取剩余期望熵最小的点作为二分点
            f64 temp, splitValue;
            rg::sort(examples, [&attr](pair<Example*, f64> const& p1, pair<Example*, f64> const& p2) -> bool {
                return p1.first->data[attr->index] < p2.first->data[attr->index];
            });
            //quickSort(examples, attr);
            for (i32 i = 0, end = (i32)examples.size() - 1; i < end && examples[i + 1].first->data[attr->index] != Attribute::ABSENT; ++i) {
                attr->values.clear();
                attr->values.insert(examples[i].first->data[attr->index]);
                temp = entropyRemain(attr, target, splitExamples(attr, examples));
                if (HL_A > temp) {
                    splitValue = (examples[i].first->data[attr->index] + examples[i + 1].first->data[attr->index]) / 2;
                    HL_A = temp;
                }
            }
            // 将二分点存到属性信息里
            attr->values.clear();
            attr->values.insert(splitValue);
        } break;
        }

        return HL - HL_A;
    }

    auto DecisionTreeBuilder::infoGainRatio(
        Attribute* const& attr,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples) -> f64 {
        f64 n = getTotalWeight(examples),
            H_A = 1.;

        f64 HL = infoGain(attr, target, examples);

        switch (attr->type) {
        case AttributeType::DISCRETE: {
            H_A = statistics::entropy(targetProbDist(target, examples));
        } break;
        case AttributeType::CONTINUOUS: {
            vector<f64> P(attr->values.size() + 1, 0.);
            i32 i;
            bool flag;
            for (pair<Example*, f64> const& exp: examples) {
                auto cit = attr->values.cbegin();
                auto cnext = ++attr->values.cbegin();
                auto cend = attr->values.cend();
                i = 0, flag = false;

                if (cit != cend && exp.first->data[attr->index] <= *cit) {
                    ++P[i];
                    continue;
                }

                ++i;
                while (cit != cend && cnext != cend) {
                    if (*cit < exp.first->data[attr->index] && exp.first->data[attr->index] <= *cnext) {
                        ++P[i];
                        flag = true;
                        break;
                    }
                    ++cit, ++cnext, ++i;
                }
                if (flag) continue;
                
                if (cit != cend && exp.first->data[attr->index] > *cit) {
                    ++P[i];                    
                }
            }
            for (f64& p: P) p /= n;
            H_A = statistics::entropy(P);
        } break;
        }
        if (H_A == 0) {
            return 0;
        }
        return HL / H_A;
    }

    auto DecisionTreeBuilder::giniIndex(
        Attribute* const& attr,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples) -> f64 {
        f64 GI, n = getTotalWeight(examples), n_k = 0.;

        switch (attr->type) {
        case AttributeType::DISCRETE: {
            GI = 0.;
            vector<vector<pair<Example*, f64>>> subExs = splitExamples(attr, examples);
            for (vector<pair<Example*, f64>> const& exs: subExs) {
                if (!exs.empty()) {
                    n_k = 0.;
                    for (pair<Example*, f64> const& exp: exs) {
                        n_k += exp.second;
                    }
                    GI += n_k / n * statistics::gini(targetProbDist(target, exs));
                }
            }
        } break;
        case AttributeType::CONTINUOUS: {
            // 如果属性 attr 是离散的，需要枚举所有取值作为二分点的情况，并取剩余期望熵最小的点作为二分点
            GI = DBL_MAX;
            f64 splitValue, curGI, n2 = n * n;
            rg::sort(examples, [&attr](pair<Example*, f64> const& p1, pair<Example*, f64> const& p2) -> bool {
                return p1.first->data[attr->index] < p2.first->data[attr->index];
            });
            //quickSort(examples, attr);

            for (i32 i = 0, end = static_cast<i32>(examples.size() - 1); i < end; ++i) {
                // 这里还是用 splitExamples 较好，不要直接遍历计数，如果值相同会无限递归
                attr->values.clear();
                attr->values.insert(examples[i].first->data[attr->index]);
                vector<vector<pair<Example*, f64>>> subExs = splitExamples(attr, examples);
                curGI = 0.;
                for (vector<pair<Example*, f64>> exs: subExs) {
                    n_k = 0.;
                    for (pair<Example*, f64> const& exp: exs) {
                        n_k += exp.second;
                    }
                    curGI += n_k / n * statistics::gini(targetProbDist(target,exs));
                }
                if (GI > curGI) {
                    splitValue = (examples[i].first->data[attr->index] + examples[i + 1].first->data[attr->index]) / 2;
                    GI = curGI;
                }
            }
            attr->values.clear();
            attr->values.insert(splitValue);
        } break;
        }

        return GI;
    }
}