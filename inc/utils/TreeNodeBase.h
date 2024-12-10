#pragma once
#include "core.h"

namespace yuki {
    class TreeNodeBase {
    public:
        TreeNodeBase() = default;
        virtual ~TreeNodeBase() = default;

        virtual auto printTree(i32 const& depth = 0) const -> void = 0;

        virtual auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void = 0; 
    };
}