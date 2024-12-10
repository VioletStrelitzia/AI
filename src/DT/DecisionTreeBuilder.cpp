#include "DecisionTreeBuilder.h"

namespace yuki::atri::dt {
    auto DecisionTreeBuilder::quickSort(vector<pair<Example*, f64>>& examples, Attribute* const& attr, i32 const& left, i32 const& right) -> void {
        if (left < right) {
            // 左闭右闭
            i32 i = left + 1, j = right, p = left;
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

        return randomChoose(targetV);
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
                HL_A += n_k[i] / n * entropy(targetProbDist(target, exs));
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
        HL = entropy(targetProbDist(target, examples));

        switch (attr->type) {
        case AttributeType::DISCRETE: {
            // 如果属性 attr 是离散的，可以直接计算剩余期望熵
            HL_A = entropyRemain(attr, target, splitExamples(attr, examples));
        } break;
        case AttributeType::CONTINUOUS: {
            // 如果属性 attr 是离散的，需要枚举所有取值作为二分点的情况，并取剩余期望熵最小的点作为二分点
            f64 temp, splitValue;
            quickSort(examples, attr);
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
            H_A = entropy(targetProbDist(target, examples));
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
            H_A = entropy(P);
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
                    GI += n_k / n * yuki::gini(targetProbDist(target, exs));
                }
            }
        } break;
        case AttributeType::CONTINUOUS: {
            // 如果属性 attr 是离散的，需要枚举所有取值作为二分点的情况，并取剩余期望熵最小的点作为二分点
            GI = DBL_MAX;
            f64 splitValue, curGI, n2 = n * n;
            quickSort(examples, attr);

            for (i32 i = 0, end = static_cast<i32>(examples.size() - 1); i < end; ++i) {
                // 这里还是用 splitExamples 较好，不要计数，如果值相同会无限递归
                attr->values.clear();
                attr->values.insert(examples[i].first->data[attr->index]);
                vector<vector<pair<Example*, f64>>> subExs = splitExamples(attr, examples);
                curGI = 0.;
                for (vector<pair<Example*, f64>> exs: subExs) {
                    n_k = 0.;
                    for (pair<Example*, f64> const& exp: exs) {
                        n_k += exp.second;
                    }
                    curGI += n_k / n * gini(targetProbDist(target,exs));
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

    auto DecisionTreeBuilder::importance(
        vector<Attribute*> const& attributes, Attribute* const& target,
        vector<pair<Example*, f64>>& examples,
        string const& criterion, pair<string, f64>* nodeInfo) -> Attribute* {
        vector<i32> attrIdxs(1, 0);
        f64 select, cur;
        vector<pair<Example*, f64>> availExamples;
        if (criterion == "InfoGain") {
            availExamples = getAvailEx(attributes[0], examples);
            select = getTotalWeight(availExamples) / getTotalWeight(examples) * infoGain(attributes[0], target, availExamples);
            cout << attributes[0]->name << select << endl;
            for (i32 i = 1, end = static_cast<i32>(attributes.size()); i < end; ++i) {
                availExamples = getAvailEx(attributes[i], examples);
                cur = getTotalWeight(availExamples) / getTotalWeight(examples) * infoGain(attributes[i], target, availExamples);
                cout << attributes[i]->name << cur << endl;
                if (cur > select) {
                    attrIdxs.clear();
                    select = cur;
                    attrIdxs.push_back(i);
                } else if (cur == select) {
                    attrIdxs.push_back(i);
                }
            }
            cout << endl;
        } else if (criterion == "InfoGainRatio") {
            availExamples = getAvailEx(attributes[0], examples);
            select = getTotalWeight(availExamples) / getTotalWeight(examples) * infoGainRatio(attributes[0], target, availExamples);
            cout << attributes[0]->name << ' ' << select << ' ' << getTotalWeight(examples) << endl;
            for (i32 i = 1, end = static_cast<i32>(attributes.size()); i < end; ++i) {
                availExamples = getAvailEx(attributes[i], examples);
                cur = getTotalWeight(availExamples) / getTotalWeight(examples) * infoGainRatio(attributes[i], target, availExamples);
                cout << attributes[i]->name << cur << endl;
                if (cur > select) {
                    attrIdxs.clear();
                    select = cur;
                    attrIdxs.push_back(i);
                } else if (cur == select) {
                    attrIdxs.push_back(i);
                } 
            }
            cout << endl;
        } else /*if (criterion == "GiniIndex")*/ {
            availExamples = getAvailEx(attributes[0], examples);
            select = getTotalWeight(availExamples) / getTotalWeight(examples) * giniIndex(attributes[0], target, availExamples);
            for (i32 i = 1, end = static_cast<i32>(attributes.size()); i < end; ++i) {
                availExamples = getAvailEx(attributes[i], examples);
                cur = getTotalWeight(availExamples) / getTotalWeight(examples) * giniIndex(attributes[i], target, availExamples);
                if (cur < select) {
                    attrIdxs.clear();
                    select = cur;
                    attrIdxs.push_back(i);
                } else if (cur == select) {
                    attrIdxs.push_back(i);
                } 
            }
        }
        if (nodeInfo) {
            nodeInfo->first = criterion;
            nodeInfo->second = select;
        }
        return attributes[randomChoose(attrIdxs)];
    }

    auto DecisionTreeBuilder::fit(
        vector<Attribute*> const& attributes,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples,
        vector<pair<Example*, f64>> const& parentExamples,
        string const& criterion,
        i32 const& depth,
        i32 const& maxDepth
    ) -> shared_ptr<DecisionTreeNode> {
        if (examples.empty()) {
            return shared_ptr<DecisionTreeNode>(
                new DiscreteDecisionTreeNode(
                    target->name, pluralityValue(target, parentExamples), 0, { "Exampls empty", 1. }));
        } else if (isSameClassify(examples)) {
            return shared_ptr<DecisionTreeNode>(
                new DiscreteDecisionTreeNode(
                    target->name, examples[0].first->target, static_cast<i32>(examples.size()), { "All same", 1. }));
        } else if (attributes.empty()) {
            return shared_ptr<DecisionTreeNode>(
                new DiscreteDecisionTreeNode(
                    target->name, pluralityValue(target, examples), static_cast<i32>(examples.size()), { "Attributes empty", 1. }));
        } else {
            pair<string, f64> nodeInfo;
            Attribute* attr = importance(attributes, target, examples, criterion, &nodeInfo);
            vector<pair<Example*, f64>> absentExamples = sepAbsentEx(attr, examples);
            vector<vector<pair<Example*, f64>>> subExs = splitExamples(attr, examples);
            mergeExamples(subExs, absentExamples);
            switch (attr->type) {
            case AttributeType::DISCRETE: {
                vector<Attribute*> subAttributes = removeAttritude(attr, attributes);
                DiscreteDecisionTreeNode* root =
                    new DiscreteDecisionTreeNode(
                        attr->name, pluralityValue(target, examples), static_cast<i32>(examples.size()), nodeInfo);
                if (maxDepth > 0 && depth >= maxDepth) {
                    for (f64 const& value: attr->values) {
                        root->children[value] = nullptr;
                    }
                } else {
                    i32 i = 0;
                    for (f64 const& value: attr->values) {
                        root->children[value] = shared_ptr<DecisionTreeNode>(fit(subAttributes, target, subExs[i], examples, criterion, depth + 1, maxDepth));
                        ++i;
                    }
                }
                return shared_ptr<DecisionTreeNode>(root);
            } case AttributeType::CONTINUOUS: {
                shared_ptr<DecisionTreeNode> dstRoot;
                if (subExs.size() == 2) {
                    ContinuousBinaryDecisionTreeNode* root =
                        new ContinuousBinaryDecisionTreeNode(
                            attr->name, *attr->values.begin(), pluralityValue(target, examples), (i32)examples.size(), nodeInfo);
                    if (maxDepth > 0 && depth >= maxDepth) {
                        root->lchild = nullptr;
                        root->rchild = nullptr;
                    } else {
                        root->lchild = shared_ptr<DecisionTreeNode>(fit(attributes, target, subExs[0], examples, criterion, depth + 1, maxDepth));
                        root->rchild = shared_ptr<DecisionTreeNode>(fit(attributes, target, subExs[1], examples, criterion, depth + 1, maxDepth));
                    
                    }
                    dstRoot = shared_ptr<DecisionTreeNode>(root);
                }
                return dstRoot;
            } default:
                return nullptr;
            }
        }
    }

    auto DecisionTreeBuilder::fitQueue(
        vector<Attribute*> const& attributes,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples,
        vector<pair<Example*, f64>> const& parentExamples,
        string const& criterion,
        i32 const& depth,
        i32 const& maxDepth
        ) -> shared_ptr<DecisionTreeNode> {
        queue<pair<shared_ptr<DecisionTreeNode>&, NodeData>> q;
        shared_ptr<DecisionTreeNode> root;
        q.push({ root, { attributes, examples, {}, 0 } });

        while (!q.empty()) {
            auto& x = q.front();

            if (x.second.examples.empty()) {
                x.first = shared_ptr<DecisionTreeNode>(
                    new DiscreteDecisionTreeNode(
                        target->name, pluralityValue(target, x.second.parentExamples), 0, { "Exampls empty", 1. }));
            } else if (isSameClassify(x.second.examples)) {
                x.first = shared_ptr<DecisionTreeNode>(
                    new DiscreteDecisionTreeNode(
                        target->name, x.second.examples[0].first->target, (i32)x.second.examples.size(), { "All same", 1. }));
            } else if (x.second.attributes.empty()) {
                x.first = shared_ptr<DecisionTreeNode>(
                    new DiscreteDecisionTreeNode(
                        target->name, pluralityValue(target, x.second.examples), (i32)x.second.examples.size(), { "Attributes empty", 1. }));
            } else {
                pair<string, f64> nodeInfo;
                Attribute* attr = importance(x.second.attributes, target, x.second.examples, criterion, &nodeInfo);
                vector<pair<Example*, f64>> absentExamples = sepAbsentEx(attr, x.second.examples);
                vector<vector<pair<Example*, f64>>> subExs = splitExamples(attr, x.second.examples);
                mergeExamples(subExs, absentExamples);
                switch (attr->type) {
                case AttributeType::DISCRETE: {
                    vector<Attribute*> subAttributes = removeAttritude(attr, x.second.attributes);
                    DiscreteDecisionTreeNode* node =
                        new DiscreteDecisionTreeNode(
                            attr->name, pluralityValue(target, x.second.examples), (i32)x.second.examples.size(), nodeInfo);
                    for (f64 const& value: attr->values) {
                        node->children[value] = shared_ptr<DecisionTreeNode>();
                    }
                    // 这里还是先添加子结点再将子结点加入队列，防止数据结构添加新结点的时候内存改变导致引用失效
                    i32 i = 0;
                    for (f64 const& value: attr->values) {
                        q.push({ node->children[value], { subAttributes, subExs[i], x.second.examples, x.second.depth + 1 }});
                        ++i;
                    }
                    x.first = shared_ptr<DecisionTreeNode>(node);
                } break;
                case AttributeType::CONTINUOUS: {
                    if (subExs.size() == 2) {
                        ContinuousBinaryDecisionTreeNode* node =
                            new ContinuousBinaryDecisionTreeNode(
                                attr->name, *attr->values.begin(), pluralityValue(target, x.second.examples), (i32)x.second.examples.size(), nodeInfo);
                        node->lchild = shared_ptr<DecisionTreeNode>();
                        q.push({ node->lchild, { x.second.attributes, subExs[0], x.second.examples, x.second.depth + 1} });
                        node->rchild = shared_ptr<DecisionTreeNode>();
                        q.push({ node->rchild, { x.second.attributes, subExs[1], x.second.examples, x.second.depth + 1} });
                        x.first = shared_ptr<DecisionTreeNode>(node);
                    }
                } break;
                default:
                    x.first = nullptr;
                }
            }
            q.pop();
        }
        return root;
    }
}