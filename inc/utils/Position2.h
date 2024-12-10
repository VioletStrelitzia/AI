#pragma once
#include "core.h"

namespace yuki::atri {
    class Vector2 {
    public:
        i32 r, c;

    public:
        Vector2() = default;

        ~Vector2() = default;

        Vector2(i32 const& r, i32 const& c);

        Vector2 operator + (Vector2 const& other);

        Vector2 operator - (Vector2 const& other);

        bool operator == (Vector2 const& other) const;

        bool operator != (Vector2 const& other) const;
    };
}