#include "DecisionTreeNode.h"

namespace yuki::atri::dt {
    // 评估样本并返回叶结点的类别
    auto DiscreteDecisionTreeNode::classify(unordered_map<string, f64> const& sample) const -> f64 {
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
            bool flag = false;
            for (pair<f64, DecisionTreeNode*> p : children) {
                if (p.second) {
                    printSpacer(depth + 1);
                    cout << attribute << " == ";
                    if (valueStrMap) {
                        cout << (*valueStrMap)[attribute][p.first] << endl;
                    } else {
                        cout << p.first << endl;
                    }
                    p.second->printTree(depth + 1);
                } else {
                    flag = true;
                }
            }
            if (flag) {
                printSpacer(depth + 1);
                cout << attribute << " == 其他" << endl;
                cout << *target << ": " << (*valueStrMap)[*target][classification] << endl;
            }
        } else {
            printSpacer(depth + 1);
            cout << *target << ": " << (*valueStrMap)[*target][classification] << endl;
        }
    }

    // 评估样本并返回叶结点的类别
    auto ContinuousBinaryDecisionTreeNode::classify(unordered_map<string, f64> const& sample) const -> f64 {
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
            if (lchild) {
                lchild->printTree(depth + 2);
            } else {
                cout << *target << ": " << (*valueStrMap)[*target][classification] << endl;
            }
            printSpacer(depth + 1);
            cout << attribute << " > " << value << endl;
            if (rchild) {
                rchild->printTree(depth + 2);
            } else {
                cout << *target << ": " << (*valueStrMap)[*target][classification] << endl;
            }
        } else {
            printSpacer(depth + 1);
            cout << *target << ": " << (*valueStrMap)[*target][classification] << endl;
        }
    }

    DiscreteDecisionTreeLeafNode::DiscreteDecisionTreeLeafNode(
        string const& targetAttribute,
        f64 const& classification,
        i32 const& sampleCount_,
        pair<string, f64> const& splitInfo_,
        unordered_map<string, unordered_map<f64, string>>* valueStr_):
        classification(classification),
        sampleCount(sampleCount_),
        splitInfo(splitInfo_) {}

    // 评估样本并返回叶结点的类别
    auto DiscreteDecisionTreeLeafNode::classify(unordered_map<string, f64> const& sample) const -> f64 {
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
        classification(classification),
        sampleCount(sampleCount_),
        splitInfo(splitInfo_) {}

    // 评估样本并返回叶结点的类别
    auto ContinuousDecisionTreeLeafNode::classify(unordered_map<string, f64> const& sample) const -> f64 {
        // 直接返回叶节点的类别
        return classification;
    }

    // 用于打印树的结构（递归）
    auto ContinuousDecisionTreeLeafNode::printTree(i32 const& depth) const -> void {
        printSpacer(depth + 1);
        cout << attribute << ": " << classification << endl;
    }
}