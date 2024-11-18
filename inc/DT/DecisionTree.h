#pragma once
#include "DecisionTreeNode.h"
#include "DTDataset.h"

namespace yuki::atri::dt {
    class DecisionTree {
    public:
        vector<string>      attributes;             // 属性集合
        string              targetAttribute;        // 目标属性
        vector<set<string>> attributeValues;        // 属性的取值
        set<string>         targetAttributeValues;  // 目标属性的取值
        map<string, i32>    attributeIndexMap;      // 属性的序号映射
        DecisionTreeNode*   root;                   // 树的根节点

    public:
        DecisionTree(/* args */);
        ~DecisionTree();

        friend auto ID3(DecisionTree& tree) -> void;
    };


}