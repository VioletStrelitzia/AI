#pragma once
#include "CSP.hpp"
#include "Position2.h"

namespace yuki::atri::csp {

using Queen = Variable<Vector2>;

bool nQueenBinaryConstraint(pair<Vector2, Vector2> const& scope, CSP<Vector2> const& csp);

void testBacktrackingSearch(i32 const& maxN = 16);

void testMinConflict(i32 const& n = 16, i32 const& end = 500);
}
