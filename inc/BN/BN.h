#pragma once
#include "Ycore.h"

namespace yuki::atri::bn {

struct Node {
    string name = "unknown";
    f64 p = -1;
    vector<Node*> parent;
    vector<Node*> children;
};

class BayesianNet {
private:
    vector<Node> net;
    unordered_map<string, Node*> map;

public:
    BayesianNet(i32 const& n, vector<string> const& nameList);
    ~BayesianNet() = default;

    auto addEdge(i32 const& start, i32 const& end) -> void;
    auto addEdge(string const& startName, string const& endName) -> void;

    auto operator [] (i32 const& idx) -> Node&;
    auto operator [] (string const& name) const -> Node const&;

};

}
