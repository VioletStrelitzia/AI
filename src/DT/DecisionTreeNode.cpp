#include "DecisionTreeNode.h"

namespace yuki::atri::dt {
    DecisionTreeNode::DecisionTreeNode(string const& attribute_, DecisionTreeNodeType const& nodeType_):
        attribute(attribute_), type(nodeType_) {}

    DiscreteDecisionTreeNode::DiscreteDecisionTreeNode(
        string const& attribute_,
        f64 const& classification_,
        i32 const& sampleCount_,
        pair<string, f64> const& splitInfo_):
        DecisionTreeNode(attribute_, DecisionTreeNodeType::DISCRETE_MUT),
        classification(classification_),
        sampleCount(sampleCount_),
        splitInfo(splitInfo_) {}

    // 评估样本并返回叶结点的类别
    auto DiscreteDecisionTreeNode::classify(map<string, f64>& sample) const -> f64 {
        auto valueIt = sample.find(attribute);
        // 如果 sample 里找到了该结点用于分裂的属性的值
        if (valueIt != sample.end()) {
            auto childIt = children.find((*valueIt).second);
            // 如果子结点记录有该属性取值并且未被剪枝
            if (childIt != children.end() && (*childIt).second != nullptr) {
                return (*childIt).second->classify(sample);
            }
        }
        return classification;
    }

    // 用于打印树的结构（递归）
    auto DiscreteDecisionTreeNode::printTree(i32 const& depth) const -> void {
        if (!children.empty()) {
            for (pair<f64, shared_ptr<DecisionTreeNode>> p : children) {
                printSpacer(depth + 1);
                cout << attribute << " == " << p.first << endl;
                p.second->printTree(depth + 1);
            }
        } else {
            printSpacer(depth + 1);
            cout << attribute << ": " << classification << endl;
        }
    }

    ContinuousBinaryDecisionTreeNode::ContinuousBinaryDecisionTreeNode(
        string const& attribute_,
        f64 const& value_,
        f64 const& classification_,
        i32 const& sampleCount_,
        pair<string, f64> const& splitInfo_):
        DecisionTreeNode(attribute_, DecisionTreeNodeType::CONTINUOUS_BINARY),
        value(value_),
        classification(classification_),
        sampleCount(sampleCount_),
        splitInfo(splitInfo_) {}

    // 评估样本并返回叶结点的类别
    auto ContinuousBinaryDecisionTreeNode::classify(map<string, f64>& sample) const -> f64 {
        // 根据属性索引和样本值选择子结点
        auto valueIt = sample.find(attribute);
        // 如果 sample 里找到了该结点用于分裂的属性的值
        if (valueIt != sample.end()) {
            // 查找左、右结点，如果不存在则返回当前结点的目标分类
            if ((*valueIt).second <= value) {
                if (lchild) {
                    return lchild->classify(sample);
                }
            } else if (rchild) {
                return rchild->classify(sample);
            }
        }
        return classification;
    }

    // 用于打印树的结构（递归）
    auto ContinuousBinaryDecisionTreeNode::printTree(i32 const& depth) const -> void {
        if (lchild && rchild) {
            printSpacer(depth + 1);
            cout << attribute << " <= " << value << endl;
            lchild->printTree(depth + 2);
            printSpacer(depth + 1);
            cout << attribute << " > " << value << endl;
            rchild->printTree(depth + 2);
        } else {
            printSpacer(depth + 1);
            cout << attribute << ": " << classification << endl;
        }
    }

    DiscreteDecisionTreeLeafNode::DiscreteDecisionTreeLeafNode(
        string const& targetAttribute,
        f64 const& classification,
        i32 const& sampleCount_,
        pair<string, f64> const& splitInfo_):
        DecisionTreeNode(targetAttribute, DecisionTreeNodeType::DISCRETE_LEAF),
        classification(classification),
        sampleCount(sampleCount_),
        splitInfo(splitInfo_) {}

    // 评估样本并返回叶结点的类别
    auto DiscreteDecisionTreeLeafNode::classify(map<string, f64>& sample) const -> f64 {
        // 直接返回叶节点的类别
        return classification;
    }

    // 用于打印树的结构（递归）
    auto DiscreteDecisionTreeLeafNode::printTree(i32 const& depth) const -> void {
        printSpacer(depth + 1);
        cout << attribute << ": " << classification << endl;
    }

    ContinuousDecisionTreeLeafNode::ContinuousDecisionTreeLeafNode(
        string const& targetAttribute,
        f64 const& classification,
        i32 const& sampleCount_,
        pair<string, f64> const& splitInfo_):
        DecisionTreeNode(targetAttribute, DecisionTreeNodeType::DISCRETE_LEAF),
        classification(classification),
        sampleCount(sampleCount_),
        splitInfo(splitInfo_) {}

    // 评估样本并返回叶结点的类别
    auto ContinuousDecisionTreeLeafNode::classify(map<string, f64>& sample) const -> f64 {
        // 直接返回叶节点的类别
        return classification;
    }

    // 用于打印树的结构（递归）
    auto ContinuousDecisionTreeLeafNode::printTree(i32 const& depth) const -> void {
        printSpacer(depth + 1);
        cout << attribute << ": " << classification << endl;
    }
}