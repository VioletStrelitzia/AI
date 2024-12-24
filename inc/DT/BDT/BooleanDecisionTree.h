#pragma once
#include "tools.h"
#include "ModelBase.h"
#include "BDTNode.h"
#include "DTDataset.h"

namespace yuki::atri::dt::bdt {
    /// @brief 基于 ID3 算法的布尔决策树
    class BooleanDecisionTree: public ModelBase {
    public:
        vector<Attribute>             attributes;         ///> 特征列表
        Attribute                     targetAttribute;    ///> 标签的名称
        unordered_map<string, i32>    attributeIndexMap;  ///> 属性的索引映射
        BooleanDecisionTreeNode*      root;               ///> 决策树根结点

    public:
        BooleanDecisionTree(Dataset& dataset);

        ~BooleanDecisionTree();

        auto getExamples(vector<Example*> const& examples, i32 const& attributeIndex, f64 const& value) -> vector<Example*>;

        /// @brief 计算给定属性在数据集中的熵
        /// @param attributeIndex 要计算熵的属性
        /// @param examples 数据集中的样本集合
        /// @return f64 给定属性的熵值
        auto entropyRemain(i32 const& attributeIndex, vector<Example*> const& examples) -> f64;

        /// @brief 计算给定属性在数据集中的信息增益
        /// @param attributeIndex 要计算信息增益的属性
        /// @param examples 数据集中的样本集合
        /// @return f64 给定属性的信息增益
        auto infoGain(i32 const& attributeIndex, vector<Example*> const& examples) -> f64;

        /// @brief 获取信息增益最大的属性
        /// @param attributeIndexs 候选属性集合
        /// @param examples 数据集中的样本集合
        /// @return 信息增益最大的属性
        auto importance(vector<i32> const& attributeIndexs, vector<Example*> const& examples) -> i32;

        auto removeAttritude(i32 const& attributeIndex, vector<i32> const& attributeIndexs) -> vector<i32>;

        auto pluralityValue(vector<Example*> const& examples) -> BooleanDecisionTreeNode*;

        auto filterExamples(vector<Example*> const& examples, i32 const& attributeIndex, f64 const& value) -> vector<Example*>;

        auto learn(vector<Example*> const& remainExamples, vector<i32> const& remainAttributeIndexs, vector<Example*> const& parentExamples = {}) -> BooleanDecisionTreeNode*;

        auto train(void* dataset_) -> void override;
        
        auto load(string const& filename) -> void override;

        auto save(string const& filename) -> void override;

        /// @brief 样本中有多少个正例
        /// @param examples 样本
        /// @return i32 样本中正例个数
        i32 positiveCount(vector<Example*> const& examples);

        /// @brief 判断样本分类是否相同
        /// @param examples 样本
        /// @return bool 样本分类是否相同
        bool isSameClassify(vector<Example*> const& examples);

        void printTree();

        void _printTree(BooleanDecisionTreeNode*& root, i32 const& depth);
    };
}