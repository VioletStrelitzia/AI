#pragma once
#include "core.h"
#include "YukiTools.h"
#include "DecisionTree.h"

namespace yuki::atri::dt {
    class DecisionTreeBuilder {
    public:
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
        /// @param begin 起点迭代器
        /// @param end 终点迭代器
        /// @return 概率分布
        static auto targetProbDist(Attribute* const& target, vector<pair<Example*, f64>> const& examples,
            i32 const& begin, i32 const& end) -> unordered_map<f64, f64>;

        /// @brief 
        /// @param examples 
        /// @return 
        static auto getTotalWeight(vector<pair<Example*, f64>> const& examples) -> f64;

        /// @brief 
        /// @param examples 
        /// @param begin 
        /// @param end 
        /// @return 
        static auto getTotalWeight(vector<pair<Example*, f64>> const& examples, i32 const& begin, i32 const& end) -> f64;

        /// @brief 
        /// @param attr 
        /// @param examples 
        /// @return 
        static auto getAvailEx(Attribute* const& attr, vector<pair<Example*, f64>> const& examples) -> vector<pair<Example*, f64>>;

        /// @brief 
        /// @param attr 
        /// @param examples 
        /// @return 
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

        /// @brief 判断样本的目标属性分类是否相同
        /// @param examples 样本
        /// @return 样本分类的目标属性是否相同
        static auto isSameClassify(vector<pair<Example*, f64>> const& examples) -> bool;

        /// @brief 计算给定属性在数据集中的熵
        /// @param attr 要计算熵的属性
        /// @param target 目标属性
        /// @param examples 数据集中的样本集合
        /// @return 给定属性的熵值
        static auto entropyRemain(Attribute* const& attr, Attribute* const& target, vector<vector<pair<Example*, f64>>> const& subExamples) -> f64;

        /// @brief 计算给定属性在数据集中的信息增益
        /// @param attr 要计算信息增益的属性
        /// @param target 目标属性
        /// @param examples 数据集中的样本集合
        /// @return 给定属性的信息增益
        static auto infoGain(
            Attribute* const& attr,
            Attribute* const& target,
            vector<pair<Example*, f64>>& examples) -> f64;

        /// @brief 计算指定属性对于样本集的信息增益率
        /// @param attrIdx 属性（序号）
        /// @param examples 样本集
        /// @return 指定属性对于样本集的信息增益率
        static auto infoGainRatio(
            Attribute* const& attr,
            Attribute* const& target,
            vector<pair<Example*, f64>>& examples) -> f64;

        static auto giniIndex(
            Attribute* const& attr,
            Attribute* const& target,
            vector<pair<Example*, f64>>& examples) -> f64;

        /// @brief 获取信息增益最大的属性
        /// @param attributes 候选属性集合
        /// @param target 目标属性
        /// @param examples 数据集中的样本集合
        /// @return 信息增益最大的属性
        static auto importance(
            vector<Attribute*> const& attributes,
            Attribute* const& target,
            vector<pair<Example*, f64>>& examples,
            string const& criterion = "InfoGain",
            pair<string, f64>* nodeInfo = nullptr) -> Attribute*;

        /// @brief 采用 learn 算法建树
        /// @param attributes 候选属性集合
        /// @param target 目标属性
        /// @param examples 数据集中的样本集合
        /// @param parentExamples 
        /// @return 决策树
        static auto fit(
            vector<Attribute*> const& attributes,
            Attribute* const& target,
            vector<pair<Example*, f64>>& examples,
            vector<pair<Example*, f64>> const& parentExamples,
            string const& criterion = "InfoGain",
            i32 const& depth = 0,
            i32 const& maxDepth = -1
            ) -> shared_ptr<DecisionTreeNode>;

        struct NodeData {
            vector<Attribute*> attributes;
            vector<pair<Example*, f64>> examples;
            vector<pair<Example*, f64>> parentExamples;
            i32 depth = 0;
        };

        /// @brief 采用 learn 算法建树
        /// @param attributes 候选属性集合
        /// @param target 目标属性
        /// @param examples 数据集中的样本集合
        /// @param parentExamples 
        /// @return 决策树
        static auto fitQueue(
            vector<Attribute*> const& attributes,
            Attribute* const& target,
            vector<pair<Example*, f64>>& examples,
            vector<pair<Example*, f64>> const& parentExamples,
            string const& criterion = "InfoGain",
            i32 const& depth = 0,
            i32 const& maxDepth = -1
            ) -> shared_ptr<DecisionTreeNode>;

    public:
        static auto learn(Dataset* dataset,
            string const& criterion = "InfoGain",
            i32 const& maxDepth = -1) -> DecisionTree* {
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
            decisionTree->root = fitQueue(attributes, &decisionTree->target, examples, {}, criterion, 0, maxDepth);
            cout << "Decision tree learning finished." << endl;

            return decisionTree;
        }
    };
}