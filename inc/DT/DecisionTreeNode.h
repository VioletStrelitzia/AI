#pragma once
#include "core.h"
#include "DTExample.h"
#include "TreeNodeBase.h"
#include "YukiTools.h"

namespace yuki::atri::dt {
    enum DecisionTreeNodeType {
        BASE_DTNODE = 0,
        BINARY,
        DISCRETE_MUT,
        CONTINUOUS_BINARY,
        DISCRETE_LEAF,
        CONTINUOUS_BINARY_LEAF
    };

    // 决策树结点的基类
    class DecisionTreeNode: public TreeNodeBase {
    protected:
        string attribute;  // 属性
        DecisionTreeNodeType type;

    public:
        friend class DecisionTree;
        friend class DecisionTreeBuilder;

        DecisionTreeNode(string const& attribute_, DecisionTreeNodeType const& type_ = DecisionTreeNodeType::BASE_DTNODE);
        virtual ~DecisionTreeNode() = default;

        /// @brief 评估样本并返回叶结点的类别
        /// @param sample 样本
        /// @return 类别
        virtual auto classify(map<string, f64>& sample) const -> f64 = 0;
    };

    class BinaryDecisionTreeNode: public DecisionTreeNode {
    protected:
        f64 value;
        f64 classification;

        i32 sampleCount;
        pair<string, f64> splitInfo;

        shared_ptr<DecisionTreeNode> lchild;
        shared_ptr<DecisionTreeNode> rchild;
    public:
        friend class DecisionTree;
        friend class DecisionTreeBuilder;

        BinaryDecisionTreeNode(
            string const& attribute_,
            f64 const& value_,
            f64 const& classification_,
            i32 const& sampleCount_ = 0,
            pair<string, f64> const& splitInfo_ = { "default", 0. },
            shared_ptr<DecisionTreeNode> const& lchild_ = nullptr,
            shared_ptr<DecisionTreeNode> const& rchild_ = nullptr):
            DecisionTreeNode(attribute_, DecisionTreeNodeType::BINARY),
            value(value_),
            classification(classification_),
            sampleCount(sampleCount_),
            splitInfo(splitInfo_),
            lchild(lchild_),
            rchild(rchild_) {}

        virtual ~BinaryDecisionTreeNode() = default;

        /// @brief 评估样本并返回叶结点的类别
        /// @param sample 样本
        /// @return 类别
        virtual auto classify(map<string, f64>& sample) const -> f64 {
            auto valueIt = sample.find(attribute);
            if (valueIt != sample.end()) {
                if ((*valueIt).second <= value) {
                    if (lchild) {
                        return lchild->classify(sample);
                    }
                } else if (rchild) {
                    return rchild->classify(sample);
                }
                return classification;
            }
            return Attribute::ABSENT;
        }

        auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
            string color = "#e58139";
            if (lchild && rchild) {
                color = "#64a1c3";
            } else if (!lchild && !rchild) {
                color = "#451247";
            }
            outFile << format(
                "{} [label=\"{}\\nSamples: {}\\nSplit by {}\\n{}: {}\\nclass: {}\", fillcolor=\"{}\"];\n",
                idx, fromParent, sampleCount, attribute, splitInfo.first, splitInfo.second, classification, color);
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

    /// @brief 离散决策树的内部结点
    class DiscreteDecisionTreeNode: public DecisionTreeNode {
    private:
        f64 classification;
        map<f64, shared_ptr<DecisionTreeNode>> children;  // 子节点

        i32 sampleCount;
        pair<string, f64> splitInfo;

    public:
        friend class DecisionTree;
        friend class DecisionTreeBuilder;

        DiscreteDecisionTreeNode(
            string const& attribute_,
            f64 const& classification_,
            i32 const& sampleCount_ = 0,
            pair<string, f64> const& splitInfo_ = { "default", 0. });

        /// @brief 评估样本并返回叶结点的类别
        /// @param sample 样本
        /// @return 类别
        auto classify(map<string, f64>& sample) const -> f64 override;

        /// @brief 打印树的结构（递归）
        /// @param depth 深度
        auto printTree(i32 const& depth = 0) const -> void override;

        auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
            if (children.empty()) {
                outFile << format("{} [label=\"{}\\nSamples: {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                    idx, fromParent, sampleCount, attribute, classification, splitInfo.first, splitInfo.second, "#64a1c3");
            } else {
                string color = "#e58139";
                for (auto const& child: children) {
                    if (child.second == nullptr) {
                        color = "#9183e3";
                        break;
                    }
                }
                outFile << format("{} [label=\"{}\\nSamples: {}\\nSplit by {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                    idx, fromParent, sampleCount, attribute, splitInfo.first, splitInfo.second, color);
                i32 curIdx = idx;
                for (auto const& child: children) {
                    if (child.second != nullptr) {
                        ++idx;
                        outFile << format("{} -> {};\n", curIdx, idx);
                        child.second->dot(outFile, idx, format("{} == {}", attribute, child.first));                    
                    }
                }
            }
        }
    };

    class ContinuousBinaryDecisionTreeNode: public DecisionTreeNode {
    private:
        f64 value;
        f64 classification;
        shared_ptr<DecisionTreeNode> lchild, rchild;

        i32 sampleCount;
        pair<string, f64> splitInfo;
    
    public:
        friend class DecisionTree;
        friend class DecisionTreeBuilder;

        ContinuousBinaryDecisionTreeNode(
            string const& attribute_,
            f64 const& value_,
            f64 const& classification_,
            i32 const& sampleCount_ = 0,
            pair<string, f64> const& splitInfo_ = { "default", 0. });
    
        /// @brief 评估样本并返回叶结点的类别
        /// @param sample 样本
        /// @return 类别
        auto classify(map<string, f64>& sample) const -> f64 override;

        /// @brief 打印树的结构（递归）
        /// @param depth 深度
        auto printTree(i32 const& depth = 0) const -> void override;

        auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
            if (lchild && rchild) {
                outFile << format("{} [label=\"{}\\nSamples: {}\\nSplit by {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                    idx, fromParent, sampleCount, attribute, splitInfo.first, splitInfo.second, "#e58139");
            } else if (!lchild && !rchild) {
                outFile << format("{} [label=\"{}\\nSamples: {}\\nclass: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                    idx, fromParent, sampleCount, classification, splitInfo.first, splitInfo.second, "#64a1c3");
            } else {
                outFile << format("{} [label=\"{}\\nSamples: {}\\nSplit by {}\\nclass: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                    idx, fromParent, sampleCount, attribute, classification, splitInfo.first, splitInfo.second, "#9183e3");
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
            pair<string, f64> const& splitInfo_ = { "default", 0. });

        /// @brief 评估样本并返回叶结点的类别
        /// @param sample 样本
        /// @return 类别
        auto classify(map<string, f64>& sample) const -> f64 override;

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

        /// @brief 评估样本并返回叶结点的类别
        /// @param sample 样本
        /// @return 类别
        auto classify(map<string, f64>& sample) const -> f64 override;

        /// @brief 打印树的结构（递归）
        /// @param depth 深度
        auto printTree(i32 const& depth = 0) const -> void override;

        auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
            outFile << format("{} [label=\"{}\\nSamples: {}\\n{}: {}\\n{}: {:1.4}\", fillcolor=\"{}\"];\n",
                idx, fromParent, sampleCount, attribute, classification, splitInfo.first, splitInfo.second, "#e58139");
        }
    };
}