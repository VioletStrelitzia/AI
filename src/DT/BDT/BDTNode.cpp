#include "BDTNode.h"

namespace yuki::atri::dt::bdt {
    BooleanDecisionTreeNode::BooleanDecisionTreeNode(bool const& value, string const& labelAttribute):
        value(value), attribute(labelAttribute) {}

    BooleanDecisionTreeNode::BooleanDecisionTreeNode(string const& attribute):
        attribute(attribute) {}

    BooleanDecisionTreeNode::~BooleanDecisionTreeNode() {
        for (pair<f64, BooleanDecisionTreeNode*> c : options) {
            delete c.second;
        }
    }
}