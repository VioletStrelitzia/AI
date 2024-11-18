#pragma once
#include "core.h"
#include "YukiTools.h"

namespace yuki::atri::dt {
    // 决策树结点的基类
    class DecisionTreeNode {
    public:
        virtual ~DecisionTreeNode() = default;

        // 评估样本并返回叶结点的类别
        virtual auto classify(map<string, string>& sample) const -> string = 0;

        // 用于打印树的结构（递归）
        virtual auto printTree(i32 const& depth = 0) const -> void = 0;
    };

    // 内部结点
    class DecisionTreeInternalNode : public DecisionTreeNode {
    private:
        string attribute;  // 用于分裂的属性
        map<string, shared_ptr<DecisionTreeNode>> children;  // 子节点

    public:
        DecisionTreeInternalNode(string const& attribute_):
            attribute(attribute_) {}

        // 评估样本并返回叶结点的类别
        string classify(map<string, string>& sample) const override {
            // 根据属性索引和样本值选择子结点
            // 这里需要根据实际的数据类型和条件来实现
            auto valueIt = sample.find(attribute);
            if (valueIt != sample.end()) {
                auto childIt = children.find((*valueIt).second);
                if (childIt != children.end()) {
                    sample.erase(valueIt);
                    return (*childIt).second->classify(sample);
                }
            }
            return "";
        }

        // 用于打印树的结构（递归）
        void printTree(i32 const& depth = 0) const override {
            printSpacer(depth);
            if (!children.empty()) {
                cout << "Split on " << attribute << endl;
                for (pair<string, shared_ptr<DecisionTreeNode>> p : children) {
                    printSpacer(depth);
                    cout << "If " << attribute << " == " << p.first << endl;
                    p.second->printTree(depth + 1);
                }
            }
        }
    };

    // 叶结点，包含类别信息
    class DecisionTreeLeafNode : public DecisionTreeNode {
    private:
        string targetAttribute;
        string classification; // 叶结点的类别

    public:
        DecisionTreeLeafNode(string const& targetAttribute, string const& classification)
            : targetAttribute(targetAttribute), classification(classification) {}

        // 评估样本并返回叶结点的类别
        string classify(map<string, string>& sample) const override {
            // 直接返回叶节点的类别
            return classification;
        }

        // 用于打印树的结构（递归）
        void printTree(i32 const& depth = 0) const override {
            printSpacer(depth);
            cout << targetAttribute << ": " << classification << endl;
        }
    };
}