#pragma once
#include "core.h"

namespace yuki {
    template <typename ElemType>
    struct TreeNode {
        ElemType data;
        vector<TreeNode*> child;

        TreeNode() = default;

        TreeNode(ElemType const& data, initializer_list<TreeNode*> const& child = initializer_list<TreeNode*>());

        ~TreeNode() = default;

        auto addChild(ElemType const& data) -> void;
    };
    
    template <typename ElemType>
    TreeNode<ElemType>::TreeNode(ElemType const& data, initializer_list<TreeNode*> const& child) :
        data(data), child(child) {}

    template <typename ElemType>
    auto TreeNode<ElemType>::addChild(ElemType const& data) -> void {
        child.push_back(new TreeNode(data));
    }
}