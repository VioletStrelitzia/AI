#include "DecisionTree.h"

namespace yuki::atri::dt {
    auto DecisionTree::classify(unordered_map<string, f64> const& input) -> f64 {
        return root->classify(input);
    }

    auto DecisionTree::dot(string path, bool const& genGraph = true, string const& extension = "pdf") -> void {
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

    auto DecisionTree::predict(void* input_, void* output_) -> void {
        *static_cast<f64*>(output_) = root->classify(*static_cast<unordered_map<string, f64>*>(input_));
    }

    auto operator << (ostream& os, DecisionTree const& tree) -> ostream& {
        if (tree.root) {
            tree.root->printTree();
        }
        return os;
    }

    auto operator << (ofstream& ofs, DecisionTree const& tree) -> ofstream& {
        
        return ofs;
    }
}