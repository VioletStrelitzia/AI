#pragma once
#include "core.h"

namespace yuki::atri::dt {
    class DecisionTreeNode {
    public:
        map<string, DecisionTreeNode*> child;

    public:
        DecisionTreeNode() = default;

        virtual ~DecisionTreeNode() = default;
    };
}