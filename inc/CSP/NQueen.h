#pragma once
#include "CSP.hpp"

namespace yuki::csp {
    struct Position {
        int r, c;
    };

    using Queen = Variable<Position>;

    bool nQueenBinaryConstraint(pair<Position, Position> const& scope, CSP<Position> const& csp);

    void testBacktrackingSearch(i32 const& maxN = 16);

    void testMinConflict(i32 const& n = 16, i32 const& end = 500);
}
