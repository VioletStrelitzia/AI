#pragma once
#include "core.h"

namespace yuki::atri::dt::bdt {
    class DecisionTreeNode {
    public:
        string                         attritude;
        bool                           value;
        map<string, DecisionTreeNode*> options;

    public:
        /// @brief 构造叶子节点
        /// @param value 叶节点的取值
        DecisionTreeNode(bool const& value, string const& labelAttribute = ""):
            value(value), attritude(labelAttribute) {}

        /// @brief 构造非叶子结点
        /// @param attribute 特征
        DecisionTreeNode(string const& attribute):
            attritude(attribute) {}

        ~DecisionTreeNode() {
            for (pair<string, DecisionTreeNode*> c : options) {
                delete c.second;
            }
        }
    };
}