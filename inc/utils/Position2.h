#pragma once
#include "core.h"

namespace yuki::atri {
    class Position2 {
    public:
        i32 r, c;

    public:
        Position2() = default;

        ~Position2() = default;

        Position2(i32 const& r, i32 const& c);

        Position2 operator + (Position2 const& other);

        Position2 operator - (Position2 const& other);

        bool operator == (Position2 const& other) const;

        bool operator != (Position2 const& other) const;
    };
}