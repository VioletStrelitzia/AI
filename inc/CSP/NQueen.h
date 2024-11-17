#pragma once
#include "CSP.hpp"
#include "Position2.h"

namespace yuki::atri::csp {
    
    using Queen = Variable<Position2>;

    bool nQueenBinaryConstraint(pair<Position2, Position2> const& scope, CSP<Position2> const& csp);

    void testBacktrackingSearch(i32 const& maxN = 16);

    void testMinConflict(i32 const& n = 16, i32 const& end = 500);
}
