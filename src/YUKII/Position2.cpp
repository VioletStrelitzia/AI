#include "YPosition2.h"

namespace yuki::atri {
    Vector2::Vector2(i32 const& r, i32 const& c):
        r(r), c(c) {}

    auto Vector2::operator + (Vector2 const& other) -> Vector2 {
        return Vector2(r + other.r, c + other.c);
    }

    auto Vector2::operator - (Vector2 const& other) -> Vector2 {
        return Vector2(r - other.r, c - other.c);
    }

    auto Vector2::operator == (Vector2 const& other) const -> bool {
        return r == other.r && c == other.c;
    }

    auto Vector2::operator != (Vector2 const& other) const -> bool {
        return r != other.r || c != other.c;
    }
}