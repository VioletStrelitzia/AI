#pragma once
#include "core.h"
#include "tools.h"
#include "DecisionTree.h"

namespace yuki::atri::dt {
class DecisionTreeBuilder {
public:
    enum CriterionType {
        INFO_GAIN = 0,
        INFO_RATIO,
        GINI_INDEX
    };

    static auto getCriterionTypeStr(CriterionType const& criterion) -> string {
        switch (criterion) {
        case CriterionType::INFO_GAIN: return "INFO_GAIN";
        case CriterionType::INFO_RATIO: return "INFO_RATIO";
        case CriterionType::GINI_INDEX: return "GINI_INDEX";
        default: return "REEOR";
        }
    }

    /// @brief 对样本集排序（快速排序）
    /// @param examples 样本集
    /// @param attr 排序的标准属性
    /// @param left 左端点
    /// @param right 右端点
    static auto quickSort(vector<pair<Example*, f64>>& examples, Attribute* const& attr, i32 const& left, i32 const& right) -> void;

    /// @brief 对样本集排序
    /// @param examples 样本集
    /// @param attr 排序的标准属性
    static auto quickSort(vector<pair<Example*, f64>>& examples, Attribute* const& attr) -> void;

    /// @brief 计算目标属性在样本集的概率分布（Probability Distribution）
    /// @param target 目标属性
    /// @param examples 样本集
    /// @return 概率分布
    static auto targetProbDist(Attribute* const& target, vector<pair<Example*, f64>> const& examples) -> unordered_map<f64, f64>;

    /// @brief 计算目标属性在样本集的概率分布（Probability Distribution）
    /// @param target 目标属性
    /// @param examples 样本集
    /// @param begin 起点迭代器
    /// @param end 终点迭代器
    /// @return unordered_map<f64, f64> 概率分布
    static auto targetProbDist(Attribute* const& target, vector<pair<Example*, f64>> const& examples,
        i32 const& begin, i32 const& end) -> unordered_map<f64, f64>;

    /// @brief 获取样本集总权重
    /// @param examples 样本集
    /// @return f64 样本集总权重
    static auto getTotalWeight(vector<pair<Example*, f64>> const& examples) -> f64;

    /// @brief 获取给定区间的样本集总权重
    /// @param examples 样本集
    /// @param begin 起点
    /// @param end 终点
    /// @return f64 给定区间的样本集总权重
    static auto getTotalWeight(vector<pair<Example*, f64>> const& examples, i32 const& begin, i32 const& end) -> f64;

    /// @brief 获取样本集中给定属性可用（未缺失）的样本集合
    /// @param attr 属性
    /// @param examples 样本集
    /// @return vector<pair<Example*, f64>> 给定属性可用（未缺失）的样本集合
    static auto getAvailEx(Attribute* const& attr, vector<pair<Example*, f64>> const& examples) -> vector<pair<Example*, f64>>;

    /// @brief 将样本集中给定属性缺失的样本分离
    /// @param attr 属性
    /// @param examples 样本集
    /// @return 给定属性缺失的样本集合
    static auto sepAbsentEx(Attribute* const& attr, vector<pair<Example*, f64>>& examples) -> vector<pair<Example*, f64>>;

    /// @brief 将样本集按照某个属性划分为一些子样本集
    /// @param attr 用于划分的属性
    /// @param examples 样本集
    /// @return 子样本集集合
    static auto splitExamples(Attribute* const& attr, vector<pair<Example*, f64>> const& examples) -> vector<vector<pair<Example*, f64>>>;

    /// @brief 将缺失当前划分属性值的样本按照有取值的样本分配概率权重进各个子集
    /// @param subExamples 子样本集集合
    /// @param absentExamples 缺失值样本集合
    static auto mergeExamples(vector<vector<pair<Example*, f64>>>& subExamples, vector<pair<Example*, f64>> const& absentExamples) -> void;

    /// @brief 从一个属性集合移除指定属性
    /// @param attr 要移除的属性
    /// @param attributes 属性集合
    /// @return 移除了指定属性的属性集合
    static auto removeAttritude(Attribute* const& attr, vector<Attribute*> const& attributes) -> vector<Attribute*>;

    /// @brief 从样本集里选取占比最多的 target 取值作为叶子结点
    /// @param target 目标属性
    /// @param examples 样本集
    /// @return 叶子结点
    static auto pluralityValue(Attribute* const& target, vector<pair<Example*, f64>> const& examples) -> f64;

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
    static auto entropyRemain(Attribute* const& attr, Attribute* const& target, vector<vector<pair<Example*, f64>>> const& subExamples) -> f64;

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
        vector<pair<Example*, f64>>& examples) -> f64;

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
        vector<pair<Example*, f64>>& examples) -> f64;

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
        vector<pair<Example*, f64>>& examples) -> f64;

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
    template <CriterionType Criterion = INFO_GAIN>
    static auto importance(
           vector<Attribute*> const& attributes,
                   Attribute* const& target,
        vector<pair<Example*, f64>>& examples,
                  pair<string, f64>* nodeInfo = nullptr) -> Attribute* {
        vector<i32> attrIdxs(1, 0);
        f64 select, cur;
        vector<pair<Example*, f64>> availExamples;
        if constexpr (Criterion == CriterionType::INFO_GAIN) {
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
        } else if constexpr (Criterion == CriterionType::INFO_RATIO) {
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
        } else /*if constexpr (Criterion == CriterionType::GINI_INDEX)*/ {
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
            nodeInfo->first = getCriterionTypeStr(Criterion);
            nodeInfo->second = select;
        }
        return attributes[random::choose(attrIdxs)];
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
     * @brief 采用 learn 算法建树（递归）
     * 
     * @tparam Criterion 度量标准
     * @tparam UsingQueue 是否使用队列迭代
     * @param attributes 候选属性集合
     * @param target 目标属性
     * @param examples 样本集
     * @param parentExamples 双亲样本集
     * @param curDepth 深度
     * @param maxDepth 最大深度
     * @return shared_ptr<DecisionTreeNode> 决策树
     */
    template <CriterionType Criterion = GINI_INDEX, bool PreCut = false, bool UsingQueue = true>
    static auto fit(
        vector<Attribute*> const& attributes,
        Attribute* const& target,
        vector<pair<Example*, f64>>& examples,
        vector<pair<Example*, f64>> const& parentExamples,
        i32 const& depth,
        i32 const& maxDepth
    ) -> shared_ptr<DecisionTreeNode> {
        if constexpr (UsingQueue) {
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
                            attr->name, pluralityValue(target, examples), static_cast<i32>(examples.size()), nodeInfo);
                    if (maxDepth > 0 && depth >= maxDepth) {
                        for (f64 const& value: attr->values) {
                            root->children[value] = nullptr;
                        }
                    } else {
                        i32 i = 0;
                        for (f64 const& value: attr->values) {
                            root->children[value] =
                                shared_ptr<DecisionTreeNode>(
                                    fit<Criterion, PreCut, UsingQueue>(
                                        subAttributes, target, subExs[i], examples, depth + 1, maxDepth));
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
                            root->lchild =
                                shared_ptr<DecisionTreeNode>(
                                    fit<Criterion, PreCut, UsingQueue>(
                                        attributes, target, subExs[0], examples, depth + 1, maxDepth));
                            root->rchild =
                                shared_ptr<DecisionTreeNode>(
                                    fit<Criterion, PreCut, UsingQueue>(
                                        attributes, target, subExs[1], examples, depth + 1, maxDepth));
                        
                        }
                        dstRoot = shared_ptr<DecisionTreeNode>(root);
                    }
                    return dstRoot;
                } default:
                    return nullptr;
                }
            }
        } else {
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
                    Attribute* attr = importance<Criterion>(x.second.attributes, target, x.second.examples, &nodeInfo);
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
                            q.push({ node->children[value], { subAttributes, subExs[i], x.second.examples, x.second.curDepth + 1 }});
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
                            q.push({ node->lchild, { x.second.attributes, subExs[0], x.second.examples, x.second.curDepth + 1} });
                            node->rchild = shared_ptr<DecisionTreeNode>();
                            q.push({ node->rchild, { x.second.attributes, subExs[1], x.second.examples, x.second.curDepth + 1} });
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

public:
    /**
     * @brief 建树
     * 
     * @tparam Criterion 度量标准
     * @param dataset 样本集
     * @param maxDepth 最大深度
     * @return DecisionTree* 决策树
     */
    template <CriterionType Criterion = GINI_INDEX, bool PreCut = false, bool UsingQueue = true>
    static auto learn(Dataset* dataset, i32 const& maxDepth = -1) -> DecisionTree* {
        DecisionTree* decisionTree = new DecisionTree();
        decisionTree->attributes = dataset->attributes;
        decisionTree->target = dataset->target;

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
        decisionTree->root = fit<Criterion, UsingQueue>(attributes, &decisionTree->target, examples, {}, 0, maxDepth);
        cout << "Decision tree learning finished." << endl;

        return decisionTree;
    }


};
}