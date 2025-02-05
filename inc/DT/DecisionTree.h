#pragma once
#include "DecisionTreeNode.h"
#include "ModelBase.h"

namespace yuki::atri::dt {
/**
 * @brief 决策树类
 * 
 */
class DecisionTree: public ModelBase {
public:
    vector<Attribute>            attributes;         ///< 属性集合
    Attribute                    target;             ///< 目标属性
    unordered_map<string, i32>   attributeIndexMap;  ///< 属性的序号映射
    unordered_map<string, unordered_map<f64, string>> valueStrMap;
    
    DecisionTreeNode* root = nullptr;     ///< 树的根节点

    friend class DecisionTreeBuilder;
public:
    /**
     * @brief 分类
     * 
     * @param input 输入
     * @return f64 分类
     */
    auto classify(unordered_map<string, f64> const& input) -> f64 {
        return root->classify(input);
    }

    auto predict(void* input_, void* output_) -> void override {
        *static_cast<f64*>(output_) = root->classify(*static_cast<unordered_map<string, f64>*>(input_));
    }

    /**
     * @brief 为树生成 dot 文件
     * 
     * @param path dot 文件的路径
     * @param genGraph 是否生成图
     * @param extension 生成图的文件格式
     */
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
    ~DecisionTree() {
        delete root;
    }
    friend auto operator << (ostream& os, DecisionTree const& tree) -> ostream&;
    friend auto operator << (ofstream& os, DecisionTree const& tree) -> ofstream&;
};
}