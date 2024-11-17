#include "Position2.h"

namespace yuki::atri {
    Position2::Position2(i32 const& r, i32 const& c):
        r(r), c(c) {}

    auto Position2::operator + (Position2 const& other) -> Position2 {
        return Position2(r + other.r, c + other.c);
    }

    auto Position2::operator - (Position2 const& other) -> Position2 {
        return Position2(r - other.r, c - other.c);
    }

    auto Position2::operator == (Position2 const& other) const -> bool {
        return r == other.r && c == other.c;
    }

    auto Position2::operator != (Position2 const& other) const -> bool {
        return r != other.r || c != other.c;
    }
}