#pragma once
#include "DecisionTreeNode.h"
#include "DTDataset.h"

namespace yuki::atri::dt {
    class DecisionTree {
    public:
        vector<Attribute>            attributes;         // 属性集合
        Attribute                    target;             // 目标属性
        unordered_map<string, i32>   attributeIndexMap;  // 属性的序号映射
        
        shared_ptr<DecisionTreeNode> root = nullptr;     // 树的根节点

        friend class DecisionTreeBuilder;
    public:
        auto classify(map<string, f64>& sample) -> f64 {
            return root->classify(sample);
        }

        auto dot(string path, bool const& genGraph = true, string const& extension = "pdf") -> void {
            ofstream outFile;
            outFile.open(path, std::ios::out);
            if (outFile.is_open()) {
                outFile << "digraph Tree {\nnode [shape=box, style=\"filled\", color=\"black\", fontname=\"Microsoft YaHei\", fontsize=26];\nedge [fontname=\"Microsoft YaHei\", fontsize=26];\n";
                i32 idx = 0;
                root->dot(outFile, idx, "Root");
                outFile << "}";
            }
            outFile.close();

            if (genGraph) {
                while (path.back() != '.') {
                    path.pop_back();
                }
                path.pop_back();
                system(format("dot -T{} {}.dot -o {}.{}", extension, path, path, extension).c_str());
            }
        }

        DecisionTree() = default;
        ~DecisionTree() = default;
        friend auto operator << (ostream& os, DecisionTree const& tree) -> ostream&;
        friend auto operator << (ofstream& os, DecisionTree const& tree) -> ofstream&;
    };
}