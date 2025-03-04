#pragma once
#include "DecisionTreeNode.h"
#include "ModelBase.h"

namespace yuki::atri::dt {
/**
 * @brief 决策树类，继承于模型基类
 * 
 */
class DecisionTree: public ModelBase {
public:
    vector<Attribute>            attributes;         ///< 属性集合
    Attribute                    target;             ///< 目标属性
    unordered_map<string, i32>   attributeIndexMap;  ///< 属性的序号映射
    unordered_map<string, unordered_map<f64, string>> valueStrMap;
    
    DecisionTreeNode* root = nullptr;     ///< 树的根节点

    friend class DecisionTreeBuilder;
public:
    /**
     * @brief 分类
     * 
     * @param input 输入
     * @return f64 分类
     */
    auto classify(unordered_map<string, f64> const& input) -> f64;

    /**
     * @brief 预测
     * 
     * @param input_ 输入 
     * @param output_ 输出
     */
    auto predict(void* input_, void* output_) -> void override;

    /**
     * @brief 为树生成 dot 文件
     * 
     * @param path dot 文件的路径
     * @param genGraph 是否生成图
     * @param extension 生成图的文件格式
     */
    auto dot(string path, bool const& genGraph = true, string const& extension = "pdf") -> void;

    DecisionTree() = default;
    ~DecisionTree() {
        delete root;
    }
    friend auto operator << (ostream& os, DecisionTree const& tree) -> ostream&;
    friend auto operator << (ofstream& os, DecisionTree const& tree) -> ofstream&;
};
}