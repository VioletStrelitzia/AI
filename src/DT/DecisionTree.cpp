#include "DecisionTree.h"

namespace yuki::atri::dt {
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