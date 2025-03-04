#pragma once
#include "core.h"
#include "DTExample.h"
#include "TreeNodeBase.h"
#include "tools.h"

namespace yuki::atri::dt {
/**
 * @brief 决策树结点枚举类型
 * 
 */
enum DecisionTreeNodeType {
    BASE_DTNODE = 0,        ///< 基类
    BINARY,                 ///< 二叉结点
    DISCRETE_MUT,           ///< 离散节点
    CONTINUOUS_BINARY,      ///< 连续二叉结点
    DISCRETE_LEAF,          ///< 离散叶结点
    CONTINUOUS_BINARY_LEAF  ///< 连续二叉叶结点
};

/**
 * @brief 决策树结点的基类
 * 
 */
class DecisionTreeNode: public TreeNodeBase {
protected:
    string attribute;  ///< 属性
    DecisionTreeNodeType type;  ///< 决策树结点的类型

    string* target;
    unordered_map<string, unordered_map<f64, string>>* valueStrMap;

public:
    friend class DecisionTree;
    friend class DecisionTreeBuilder;

    DecisionTreeNode() = default;
    DecisionTreeNode(
        string const&                                      attribute,
        DecisionTreeNodeType const&                        type,
        string* const&                                     target,
        unordered_map<string, unordered_map<f64, string>>* valueStrMap):
        attribute(attribute),
        type(type),
        target(target),
        valueStrMap(valueStrMap) {}

    virtual ~DecisionTreeNode() = default;

    virtual auto allChildrenEmpty() const -> bool = 0;

    /**
     * @brief 评估样本并返回叶结点的类别
     * 
     * @param sample 样本
     * @return f64 类别
     */
    virtual auto classify(unordered_map<string, f64> const& sample) const -> f64 = 0;

    auto printTree(i32 const& depth = 0) const -> void override {}
};

/**
 * @brief 决策树分裂属性为离散值的结点
 * 
 */
class DiscreteDecisionTreeNode: public DecisionTreeNode {
private:
    f64 classification;
    unordered_map<f64, DecisionTreeNode*> children;  // 子节点

    i32 sampleCount;
    pair<string, f64> splitInfo;

public:
    friend class DecisionTree;
    friend class DecisionTreeBuilder;

    DiscreteDecisionTreeNode(
        string const&                                      attribute,
        string* const&                                     target,
        f64 const                                          classification,
        i32 const                                          sampleCount,
        pair<string, f64> const                            splitInfo = { "", 0. },
        unordered_map<string, unordered_map<f64, string>>* valueStrMap = nullptr):
        DecisionTreeNode(attribute, DecisionTreeNodeType::DISCRETE_MUT, target, valueStrMap),
        classification(classification),
        sampleCount(sampleCount),
        splitInfo(splitInfo) {}

    ~DiscreteDecisionTreeNode() {
        for (auto& p: children) {
            delete p.second;
        }
    }

    auto allChildrenEmpty() const -> bool override {
        for (auto& p: children) {
            if (p.second) return false;
        }
        return true;
    }

    /**
     * @brief 评估样本并返回叶结点的类别
     * 
     * @param sample 样本
     * @return f64 类别
     */
    auto classify(unordered_map<string, f64> const& sample) const -> f64 override;

    /// @brief 打印树的结构（递归）
    /// @param depth 深度
    auto printTree(i32 const& depth = 0) const -> void override;

    auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
        if (children.empty()) {
            outFile << format("{} [label=\"{}\\nSamples: {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                idx, fromParent, sampleCount, *target, (*valueStrMap)[*target][classification], splitInfo.first, splitInfo.second, "#64a1c3");
        } else {
            string color = "#e58139";
            for (auto const& child: children) {
                if (child.second == nullptr) {
                    color = "#9183e3";
                    break;
                }
            }
            outFile << format("{} [label=\"{}\\nSamples: {}\\nSplit by {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                idx, fromParent, sampleCount, attribute, *target, (*valueStrMap)[*target][classification], splitInfo.first, splitInfo.second, color);
            i32 curIdx = idx;
            for (auto const& child: children) {
                if (child.second != nullptr) {
                    ++idx;
                    outFile << format("{} -> {};\n", curIdx, idx);
                    child.second->dot(outFile, idx, format("{} == {}", attribute, (*valueStrMap)[attribute][child.first]));                    
                }
            }
        }
    }
};

/**
 * @brief 决策树分裂属性为连续值的结点
 * 
 */
class ContinuousBinaryDecisionTreeNode: public DecisionTreeNode {
private:
    f64 value;
    f64 classification;
    DecisionTreeNode** children;
    DecisionTreeNode*& lchild;
    DecisionTreeNode*& rchild;

    i32 sampleCount;
    pair<string, f64> splitInfo;

public:
    friend class DecisionTree;
    friend class DecisionTreeBuilder;

    ContinuousBinaryDecisionTreeNode(
        string const&                                      attribute,
        string* const&                                     target,
        f64 const&                                         value,
        f64 const&                                         classification,
        i32 const&                                         sampleCount,
        pair<string, f64> const&                           splitInfo = { "", 0. },
        unordered_map<string, unordered_map<f64, string>>* valueStrMap = nullptr):
        DecisionTreeNode(attribute, DecisionTreeNodeType::CONTINUOUS_BINARY, target, valueStrMap),
        value(value),
        classification(classification),
        children(new DecisionTreeNode*[2]),
        lchild(children[0]),
        rchild(children[1]),
        sampleCount(sampleCount),
        splitInfo(splitInfo) {
            lchild = rchild = nullptr;
        }

    ~ContinuousBinaryDecisionTreeNode() {
        delete lchild;
        delete rchild;
        delete[] children;
    }

    auto allChildrenEmpty() const -> bool override {
        return !lchild && !rchild;
    }

    /**
     * @brief 评估样本并返回叶结点的类别
     * 
     * @param sample 样本
     * @return f64 类别
     */
    auto classify(unordered_map<string, f64> const& sample) const -> f64 override;

    /// @brief 打印树的结构（递归）
    /// @param depth 深度
    auto printTree(i32 const& depth = 0) const -> void override;

    auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
        if (lchild && rchild) {
            outFile << format("{} [label=\"{}\\nSamples: {}\\nSplit by {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                idx, fromParent, sampleCount, attribute, splitInfo.first, splitInfo.second, "#e58139");
        } else if (!lchild && !rchild) {
            outFile << format("{} [label=\"{}\\nSamples: {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                idx, fromParent, sampleCount, *target, (*valueStrMap)[*target][classification], splitInfo.first, splitInfo.second, "#64a1c3");
        } else {
            outFile << format("{} [label=\"{}\\nSamples: {}\\nSplit by {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                idx, fromParent, sampleCount, attribute, *target, (*valueStrMap)[*target][classification], splitInfo.first, splitInfo.second, "#9183e3");
        }
        i32 curIdx = idx;
        if (lchild) {
            ++idx;
            outFile << format("{} -> {};\n", curIdx, idx);
            lchild->dot(outFile, idx, format("{} <= {}", attribute, value));
        }
        if (rchild) {
            ++idx;
            outFile << format("{} -> {};\n", curIdx, idx);
            rchild->dot(outFile, idx, format("{} >  {}", attribute, value));                
        }

    }
};

// 叶结点，包含类别信息
class DiscreteDecisionTreeLeafNode: public DecisionTreeNode {
private:
    f64 classification; // 叶结点的类别

    i32 sampleCount;
    pair<string, f64> splitInfo;

public:
    friend class DecisionTree;
    friend class DecisionTreeBuilder;

    DiscreteDecisionTreeLeafNode(
        string const& targetAttribute,
        f64 const& classification,
        i32 const& sampleCount_ = 0,
        pair<string, f64> const& splitInfo_ = { "default", 0. },
        unordered_map<string, unordered_map<f64, string>>* valueStr_ = nullptr);

    auto allChildrenEmpty() const -> bool override {
        return true;
    }

    /**
     * @brief 评估样本并返回叶结点的类别
     * 
     * @param sample 样本
     * @return f64 类别
     */
    auto classify(unordered_map<string, f64> const& sample) const -> f64 override;

    /// @brief 打印树的结构（递归）
    /// @param depth 深度
    auto printTree(i32 const& depth = 0) const -> void override;

    auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
        outFile << format("{} [label=\"{}\\nSamples: {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
            idx, fromParent, sampleCount, attribute, classification, splitInfo.first, splitInfo.second, "#e58139");
    }
};

// 叶结点，包含类别信息
class ContinuousDecisionTreeLeafNode: public DecisionTreeNode {
private:
    f64 classification; // 叶结点的类别

    i32 sampleCount;
    pair<string, f64> splitInfo;

public:
    friend class DecisionTree;
    friend class DecisionTreeBuilder;

    ContinuousDecisionTreeLeafNode(
        string const& targetAttribute,
        f64 const& classification,
        i32 const& sampleCount_ = 0,
        pair<string, f64> const& splitInfo_ = { "default", 0. });

    auto allChildrenEmpty() const -> bool override {
        return true;
    }

    /**
     * @brief 评估样本并返回叶结点的类别
     * 
     * @param sample 样本
     * @return f64 类别
     */
    auto classify(unordered_map<string, f64> const& sample) const -> f64 override;

    /// @brief 打印树的结构（递归）
    /// @param depth 深度
    auto printTree(i32 const& depth = 0) const -> void override;

    auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
        outFile << format("{} [label=\"{}\\nSamples: {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
            idx, fromParent, sampleCount, attribute, classification, splitInfo.first, splitInfo.second, "#e58139");
    }
};
}