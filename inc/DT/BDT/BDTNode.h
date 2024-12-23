#pragma once
#include "core.h"

namespace yuki::atri::dt::bdt {
    class BooleanDecisionTreeNode {
    public:
        string attribute;
        bool   value;
        map<f64, BooleanDecisionTreeNode*> options;

    public:
        /// @brief 构造叶子节点
        /// @param value 叶节点的取值
        BooleanDecisionTreeNode(bool const& value, string const& labelAttribute);

        /// @brief 构造非叶子结点
        /// @param attribute 特征
        BooleanDecisionTreeNode(string const& attribute);

        ~BooleanDecisionTreeNode();
    };
}