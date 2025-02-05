#pragma once
#include "Ycore.h"
#include "Ytools.h"
#include "DecisionTree.h"
#include "DTDataset.h"

namespace yuki::atri::dt {
class DecisionTreeBuilder {
public:
    /**
     * @brief 分裂度量标准
     * 
     */
    enum CriterionType {
        INFO_GAIN = 0,
        INFO_RATIO,
        GINI_INDEX
    };

    /**
     * @brief 获取度量标准的输出字符串
     * 
     * @param criterion 度量标准
     * @return string 字符串
     */
    static auto getCriterionTypeStr(CriterionType const& criterion) -> string {
        switch (criterion) {
        case CriterionType::INFO_GAIN:  return "INFO_GAIN";
        case CriterionType::INFO_RATIO: return "INFO_RATIO";
        case CriterionType::GINI_INDEX: return "GINI_INDEX";
        default: return "REEOR";
        }
    }

    /**
     * @brief 对样本集排序（快速排序）
     * 
     * @param examples 样本集
     * @param attr 排序的标准属性
     * @param left 左端点
     * @param right 右端点
     */
    static auto quickSort(vector<pair<Example*, f64>>& examples, Attribute* const& attr, i32 const& left, i32 const& right) -> void;

    /**
     * @brief 对样本集排序
     * 
     * @param examples 样本集
     * @param attr 排序的标准属性
     */
    static auto quickSort(vector<pair<Example*, f64>>& examples, Attribute* const& attr) -> void;

    /**
     * @brief 计算目标属性在样本集的概率分布（Probability Distribution）
     * 
     * @param target 目标属性
     * @param examples 样本集
     * @return unordered_map<f64, f64> 概率分布
     */
    static auto targetProbDist(Attribute* const& target, vector<pair<Example*, f64>> const& examples) -> unordered_map<f64, f64>;

    /**
     * @brief 计算目标属性在样本集的概率分布（Probability Distribution）
     * 
     * @param target 目标属性
     * @param examples 样本集
     * @param begin 起点
     * @param end 终点
     * @return unordered_map<f64, f64> 概率分布
     */
    static auto targetProbDist(
        Attribute* const&                  target,
        vector<pair<Example*, f64>> const& examples,
        i32 const&                         begin,
        i32 const&                         end
    ) -> unordered_map<f64, f64>;

    /**
     * @brief 获取样本集总权重
     * 
     * @param examples 样本集
     * @return f64 样本集总权重
     */
    static auto getTotalWeight(vector<pair<Example*, f64>> const& examples) -> f64;

    /**
     * @brief 获取给定区间的样本集总权重
     * 
     * @param examples 样本集
     * @param begin 起点
     * @param end 终点
     * @return f64 给定区间的样本集总权重
     */
    static auto getTotalWeight(
        vector<pair<Example*, f64>> const& examples,
        i32 const&                         begin,
        i32 const&                         end
    ) -> f64;

    /**
     * @brief 获取样本集中给定属性可用（未缺失）的样本集合
     * 
     * @param attr 属性
     * @param examples 样本集
     * @return vector<pair<Example*, f64>> 给定属性可用（未缺失）的样本集合
     */
    static auto getAvailEx(
        Attribute* const&                  attr,
        vector<pair<Example*, f64>> const& examples
    ) -> vector<pair<Example*, f64>>;

    /**
     * @brief 将样本集中给定属性缺失的样本分离
     * 
     * @param attr 属性
     * @param examples 样本集
     * @return vector<pair<Example*, f64>> 给定属性缺失的样本集合
     */
    static auto sepAbsentEx(
        Attribute* const&            attr,
        vector<pair<Example*, f64>>& examples
    ) -> vector<pair<Example*, f64>>;

    /**
     * @brief 将样本集按照某个属性划分为一些子样本集
     * 
     * @param attr 用于划分的属性
     * @param examples 样本集
     * @return vector<vector<pair<Example*, f64>>> 子样本集集合
     */
    static auto splitExamples(
        Attribute* const&                  attr,
        vector<pair<Example*, f64>> const& examples
    ) -> vector<vector<pair<Example*, f64>>>;

    /**
     * @brief 将缺失当前划分属性值的样本按照有取值的样本分配概率权重进各个子集
     * 
     * @param subExamples 子样本集集合
     * @param absentExamples 缺失值样本集合
     */
    static auto mergeExamples(
        vector<vector<pair<Example*, f64>>>& subExamples,
        vector<pair<Example*, f64>> const&   absentExamples
    ) -> void;

    /**
     * @brief 从一个属性集合移除指定属性
     * 
     * @param attr 要移除的属性
     * @param attributes 属性集合
     * @return vector<Attribute*> 移除了指定属性的属性集合
     */
    static auto removeAttritude(
        Attribute* const&         attr,
        vector<Attribute*> const& attributes
    ) -> vector<Attribute*>;

    /**
     * @brief 从样本集里选取占比最多的 target 取值作为叶子结点
     * 
     * @param target 目标属性
     * @param examples 样本集
     * @return f64 叶子结点
     */
    static auto pluralityValue(
        Attribute* const&                  target,
        vector<pair<Example*, f64>> const& examples
    ) -> f64;

    /**
     * @brief 判断样本的目标属性分类是否相同
     * 
     * @param examples 样本
     * @return bool 样本分类的目标属性是否相同
     * @retval true 样本分类的目标属性相同
     * @retval false 样本分类的目标属性不相同
     */
    static auto isSameClassify(vector<pair<Example*, f64>> const& examples) -> bool;

    /**
     * @brief 计算给定属性在数据集中的熵
     * 
     * @param attr 要计算熵的属性
     * @param target 目标属性
     * @param subExamples 数据集中的样本集合
     * @return f64 给定属性的熵值
     */
    static auto entropyRemain(
        Attribute* const&                          attr,
        Attribute* const&                          target,
        vector<vector<pair<Example*, f64>>> const& subExamples
    ) -> f64;

    /**
     * @brief 计算给定属性在数据集中的信息增益
     * 
     * @param attr 要计算信息增益的属性
     * @param target 目标属性
     * @param examples 数据集中的样本集合
     * @return f64 给定属性的信息增益
     */
    static auto infoGain(
        Attribute* const& attr,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples
    ) -> f64;

    /**
     * @brief 计算指定属性对于样本集的信息增益率
     * 
     * @param attr 属性
     * @param target 目标属性
     * @param examples 样本集
     * @return f64 指定属性对于样本集的信息增益率
     */
    static auto infoGainRatio(
        Attribute* const& attr,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples
    ) -> f64;

    /**
     * @brief 计算指定属性对于样本集的基尼指数
     * 
     * @param attr 属性
     * @param target 目标属性
     * @param examples 样本集
     * @return f64 指定属性对于样本集的基尼指数
     */
    static auto giniIndex(
        Attribute* const& attr,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples
    ) -> f64;

    /**
     * @brief 获取信息增益最大的属性
     * 
     * @tparam Criterion 度量标准
     * @param attributes 候选属性集合
     * @param target 目标属性
     * @param examples 样本集
     * @param nodeInfo 节点信息
     * @return Attribute* 信息增益最大的属性
     */
    template <CriterionType Criterion = INFO_GAIN, bool PrintInfo = false>
    static auto importance(
        vector<Attribute*> const&    attributes,
        Attribute* const&            target,
        vector<pair<Example*, f64>>& examples,
        pair<string, f64>*           nodeInfo = nullptr
    ) -> Attribute* {

        function<f64(Attribute* const&, Attribute* const&, vector<pair<Example*, f64>>&)> func;   ///< 计算度量值的函数
        function<bool(f64 const&, f64 const&)> firstBetter;  ///< 判断度量值更优的函数
        if constexpr (Criterion == CriterionType::INFO_GAIN) {
            func = infoGain;
            firstBetter = greater();  // cur(first) > select(second)
        } else if constexpr (Criterion == CriterionType::INFO_RATIO) {
            func = infoGainRatio;
            firstBetter = greater();  // cur(first) > select(second)
        } else /* if constexpr (Criterion == CriterionType::GINI_INDEX) */ {
            func = giniIndex;
            firstBetter = less();  // cur(first) < select(second)
        }

        vector<i32> attrIdxs(1, 0);  ///< 保存度量值相等的属性（可能同时存在多个最优分裂属性）
        f64 cur;

        auto totalWeight      = getTotalWeight(examples);
        auto availExamples    = getAvailEx(attributes[0], examples);
        auto normalizedWeight = getTotalWeight(availExamples) / totalWeight;
        auto select           = normalizedWeight * func(attributes[0], target, availExamples);
        
        if constexpr (PrintInfo) {
            cout << attributes[0]->name << ' ' << select << endl;
        }
        for (i32 i = 1, end = static_cast<i32>(attributes.size()); i < end; ++i) {
            availExamples    = getAvailEx(attributes[i], examples);
            normalizedWeight = getTotalWeight(availExamples) / totalWeight;
            cur              = normalizedWeight * func(attributes[i], target, availExamples);
            if constexpr (PrintInfo) {
                cout << attributes[i]->name << ' ' << cur << endl;          
            }
            if (firstBetter(cur, select)) {
                attrIdxs.clear();
                select = cur;
                attrIdxs.push_back(i);
            } else if (cur == select) {
                attrIdxs.push_back(i);
            }
        }
        if constexpr (PrintInfo) {
            cout << endl;
        }

        if (nodeInfo) {
            nodeInfo->first = getCriterionTypeStr(Criterion);
            nodeInfo->second = select;
        }
        Attribute* dst = attributes[random::choose(attrIdxs)];
        
        if constexpr (PrintInfo) {
            cout << "choose " << dst->name << endl;
        }
        return dst;
    }

    /**
     * @brief 结点信息类
     * @details 用于迭代学习算法
     */
    struct NodeData {
        vector<Attribute*> attributes;  ///< 候选属性
        vector<pair<Example*, f64>> examples;  ///< 样本集
        vector<pair<Example*, f64>> parentExamples;  ///< 双亲样本集
        i32 curDepth = 0;  ///< 当前深度
    };

    /**
     * @brief 采用 learn 算法建树
     * 
     * @tparam Criterion 度量标准
     * @tparam PreCut 是否预剪枝
     * @tparam UsingQueue 是否使用队列迭代
     * @param attributes 候选属性集合
     * @param target 目标属性
     * @param examples 样本集
     * @param parentExamples 双亲样本集
     * @param depth 深度
     * @param maxDepth 最大深度
     * @param valueStrMap 数值和字符串的映射
     * @return DecisionTreeNode* 决策树
     */
    template <CriterionType Criterion = GINI_INDEX, bool PreCut = false, bool UsingQueue = true>
    static auto fit(
        vector<Attribute*> const&                          attributes,
        Attribute* const&                                  target,
        vector<pair<Example*, f64>>&                       examples,
        vector<pair<Example*, f64>> const&                 parentExamples,
        i32 const&                                         depth,
        i32 const&                                         maxDepth,
        unordered_map<string, unordered_map<f64, string>>* valueStrMap = nullptr
    ) -> DecisionTreeNode* {
        if constexpr (UsingQueue) {
            queue<pair<DecisionTreeNode*&, NodeData>> q;
            DecisionTreeNode* root;
            q.push({ root, { attributes, examples, {}, 0 } });

            while (!q.empty()) {
                auto& x = q.front();

                if (x.second.examples.empty()) {
                    x.first = new DiscreteDecisionTreeNode(
                        target->name,
                        &target->name,
                        pluralityValue(target, x.second.parentExamples),
                        0,
                        { "Exampls empty", 1. },
                        valueStrMap
                    );
                } else if (isSameClassify(x.second.examples)) {
                    x.first = new DiscreteDecisionTreeNode(
                        target->name,
                        &target->name,
                        x.second.examples.front().first->target,
                        static_cast<i32>(x.second.examples.size()),
                        { "All same", 1. },
                        valueStrMap
                    );
                } else if (x.second.attributes.empty()) {
                    x.first = new DiscreteDecisionTreeNode(
                        target->name,
                        &target->name,
                        pluralityValue(target, x.second.examples),
                        static_cast<i32>(x.second.examples.size()),
                        { "Attributes empty", 1. },
                        valueStrMap
                    );
                } else {
                    pair<string, f64> nodeInfo;
                    Attribute* attr = importance<Criterion>(x.second.attributes, target, x.second.examples, &nodeInfo);
                    vector<pair<Example*, f64>> absentExamples = sepAbsentEx(attr, x.second.examples);
                    vector<vector<pair<Example*, f64>>> subExs = splitExamples(attr, x.second.examples);
                    mergeExamples(subExs, absentExamples);
                    switch (attr->type) {
                    case AttributeType::DISCRETE: {
                        vector<Attribute*> subAttributes = removeAttritude(attr, x.second.attributes);
                        auto node = new DiscreteDecisionTreeNode(
                            attr->name,
                            &target->name,
                            pluralityValue(target, x.second.examples),
                            static_cast<i32>(x.second.examples.size()),
                            nodeInfo,
                            valueStrMap
                        );

                        for (f64 const& value: attr->values) {
                            node->children[value] = nullptr;
                        }
                        // 先添加子结点再将子结点加入队列，防止数据结构添加新结点的时候内存改变导致引用失效
                        i32 i = 0;
                        for (f64 const& value: attr->values) {
                            q.push({ node->children[value], { subAttributes, subExs[i], x.second.examples, x.second.curDepth + 1 }});
                            ++i;
                        }
                        x.first = node;
                    } break;
                    case AttributeType::CONTINUOUS: {
                        if (subExs.size() == 2) {
                            auto node = new ContinuousBinaryDecisionTreeNode(
                                attr->name,
                                &target->name,
                                *(attr->values.begin()),
                                pluralityValue(target, x.second.examples),
                                static_cast<i32>(x.second.examples.size()),
                                nodeInfo,
                                valueStrMap
                            );
                            q.push({ node->lchild, { x.second.attributes, subExs[0], x.second.examples, x.second.curDepth + 1} });
                            q.push({ node->rchild, { x.second.attributes, subExs[1], x.second.examples, x.second.curDepth + 1} });
                            x.first = node;
                        }
                    } break;
                    default:
                        x.first = nullptr;
                    }
                }
                q.pop();
            }
            return root;
        } else {
            if (examples.empty()) {
                return new DiscreteDecisionTreeNode(
                    target->name,
                    &target->name,
                    pluralityValue(target, parentExamples),
                    0,
                    { "Exampls empty", 1. },
                    valueStrMap
                );
            } else if (isSameClassify(examples)) {
                return new DiscreteDecisionTreeNode(
                    target->name,
                    &target->name,
                    examples.front().first->target,
                    static_cast<i32>(examples.size()),
                    { "All same", 1. },
                    valueStrMap
                );
            } else if (attributes.empty()) {
                return new DiscreteDecisionTreeNode(
                    target->name,
                    &target->name,
                    pluralityValue(target, examples),
                    static_cast<i32>(examples.size()),
                    { "Attributes empty", 1. },
                    valueStrMap
                );
            } else {
                // 存储结点信息
                pair<string, f64> nodeInfo;
                Attribute* attr = importance<Criterion>(attributes, target, examples, &nodeInfo);
                vector<pair<Example*, f64>> absentExamples = sepAbsentEx(attr, examples);
                vector<vector<pair<Example*, f64>>> subExs = splitExamples(attr, examples);
                mergeExamples(subExs, absentExamples);
                switch (attr->type) {
                case AttributeType::DISCRETE: {
                    vector<Attribute*> subAttributes = removeAttritude(attr, attributes);
                    DiscreteDecisionTreeNode* root =
                        new DiscreteDecisionTreeNode(
                            attr->name,
                            &target->name,
                            pluralityValue(target, examples),
                            static_cast<i32>(examples.size()),
                            nodeInfo,
                            valueStrMap
                        );
                    if (maxDepth > 0 && depth >= maxDepth) {
                        for (f64 const& value: attr->values) {
                            root->children[value] = nullptr;
                        }
                    } else {
                        i32 i = 0;
                        for (f64 const& value: attr->values) {
                            root->children[value] = fit<Criterion, PreCut, UsingQueue>(
                                        subAttributes, target, subExs[i], examples, depth + 1, maxDepth);
                            ++i;
                        }
                    }
                    return root;
                } case AttributeType::CONTINUOUS: {
                    if (subExs.size() == 2) {
                        auto root = new ContinuousBinaryDecisionTreeNode(
                            attr->name,
                            &target->name,
                            (*attr)->values.begin(),
                            pluralityValue(target, examples),
                            static_cast<i32>(examples.size()),
                            nodeInfo,
                            valueStrMap
                        );
                        if (maxDepth > 0 && depth >= maxDepth) {
                            root->lchild = nullptr;
                            root->rchild = nullptr;
                        } else {
                            root->lchild =fit<Criterion, PreCut, UsingQueue>(
                                attributes, target, subExs[0], examples, depth + 1, maxDepth);
                            root->rchild =fit<Criterion, PreCut, UsingQueue>(
                                attributes, target, subExs[1], examples, depth + 1, maxDepth);
                        
                        }
                        return root;
                    }
                } default:
                    return nullptr;
                }
            }
        }
    }

public:
    /**
     * @brief 建树
     * 
     * @tparam Criterion 度量标准
     * @tparam PreCut 是否预剪枝
     * @tparam UsingQueue 是否使用队列迭代
     * @param dataset 样本集
     * @param maxDepth 最大深度
     * @return DecisionTree* 决策树
     */
    template <CriterionType Criterion = GINI_INDEX, bool PreCut = false, bool UsingQueue = true>
    static auto learn(
        Dataset*   dataset,
        i32 const& maxDepth = -1
    ) -> DecisionTree* {
        DecisionTree* decisionTree = new DecisionTree();
        decisionTree->attributes = dataset->attributes;
        decisionTree->target = dataset->target;
        decisionTree->valueStrMap = dataset->valueStrMap;

        // 存指针和序号，减少拷贝开销
        vector<Attribute*> attributes;
        for (Attribute& attr: dataset->attributes) {
            attributes.push_back(&attr);
        }
        vector<pair<Example*, f64>> examples;
        for (Example& example: dataset->examples) {
            for (auto& x: example.data) {
                if (x == Attribute::ABSENT) {
                    cout << "  ";
                } else {
                    cout << x << ' ';                    
                }
            }
            cout << example.target << endl;
            examples.push_back({ &example, 1. });
        }

        cout << "Decision tree learning start..." << endl;
        decisionTree->root = fit<Criterion, UsingQueue>(
            attributes,
            &decisionTree->target, examples,
            {},
            0,
            maxDepth,
            &decisionTree->valueStrMap
        );
        cout << "Decision tree learning finished." << endl;

        return decisionTree;
    }

    /**
     * @brief 后剪枝
     * 
     * @param tree 决策树
     * @param dataset 测试集
     */
    static auto postCut(
        DecisionTree* tree,
        Dataset*      dataset
    ) -> void {
        vector<unordered_map<string, f64>> samples(dataset->examples.size());
        i32 i = 0;
        for (auto& e: dataset->examples) {
            for (auto& attr: dataset->attributes) {
                samples[i][attr.name] = e.data[attr.index];
            }
            ++i;
        }

        vector<DecisionTreeNode**> q;
        DecisionTreeNode** curNode;
        i32 idx = 0;

        switch (tree->root->type) {
        case DecisionTreeNodeType::CONTINUOUS_BINARY:
            if (static_cast<ContinuousBinaryDecisionTreeNode*>(tree->root)->lchild) {
                q.push_back(&static_cast<ContinuousBinaryDecisionTreeNode*>(tree->root)->lchild);
            }
            if (static_cast<ContinuousBinaryDecisionTreeNode*>(tree->root)->rchild) {
                q.push_back(&static_cast<ContinuousBinaryDecisionTreeNode*>(tree->root)->rchild);
            }
            break;
        case DecisionTreeNodeType::DISCRETE_MUT: {
            auto& children = static_cast<DiscreteDecisionTreeNode*>(tree->root)->children;
            for (auto it = children.begin(); it != children.end(); ++it) {
                if ((*it).second) {
                    q.push_back(&((*it).second));
                }
            }            
        } break;
        default:
            break;
        }

        for (idx = 0; idx < q.size(); ++idx) {
            curNode = q[idx];
            switch ((*curNode)->type) {
            case DecisionTreeNodeType::CONTINUOUS_BINARY:
                static_cast<ContinuousBinaryDecisionTreeNode*>(*curNode)->printTree();cout << endl;
                if (static_cast<ContinuousBinaryDecisionTreeNode*>(*curNode)->lchild) {
                    q.push_back(&static_cast<ContinuousBinaryDecisionTreeNode*>(*curNode)->lchild);
                }
                if (static_cast<ContinuousBinaryDecisionTreeNode*>(*curNode)->rchild) {
                    q.push_back(&static_cast<ContinuousBinaryDecisionTreeNode*>(*curNode)->rchild);
                }
                break;
            case DecisionTreeNodeType::DISCRETE_MUT: {
                auto& children = static_cast<DiscreteDecisionTreeNode*>(*curNode)->children;
                for (auto it = children.begin(); it != children.end(); ++it) {
                    if ((*it).second) {
                        q.push_back(&((*it).second));
                    }
                }
            } break;
            default:
                break;
            }
        }
        idx = static_cast<i32>(q.size());
        cout << q.size() << endl;
        while (idx) {
            curNode = q[--idx];
            DecisionTreeNode* temp = *curNode;

            f64 count = 0.;
            for (i = 0; i < samples.size(); ++i) {
                if (tree->classify(samples[i]) == dataset->rawValues[i].back()) {
                    ++count;
                }
            }
            f64 beforeCut = count / dataset->rawValues.size();

            *curNode = nullptr;
            count = 0.;
            for (i = 0; i < samples.size(); ++i) {
                if (tree->classify(samples[i]) == dataset->rawValues[i].back()) {
                    ++count;
                }
            }
            f64 afterCut = count / dataset->rawValues.size();
            //static i32 x = 0;
            //tree->dot(format("../../resources/DT/trees/temp{}.dot", x++));

            cout << beforeCut << ' ' << afterCut << endl;
            if (afterCut <= beforeCut) {
                *curNode = temp;
            } else {
                delete temp;
            }
        }

    }


};
}