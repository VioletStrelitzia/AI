#pragma once
#include "core.h"

namespace yuki::nfp {
    /**
     * @brief 用来描述棋盘上位置的类。
     * 坐标系：
     *   0 1 2 3
     * 0 ...
     * 1 ...
     * 2 ...
     * 3 ...
     * @param r 行
     * @param c 列
     */
    struct NFPPosition {
        i32 r, c;

        NFPPosition() = default;

        ~NFPPosition() = default;

        NFPPosition(i32 const& r, i32 const& c);

        NFPPosition operator+(NFPPosition const& other);

        NFPPosition operator-(NFPPosition const& other);

        bool operator==(NFPPosition const& other) const;

        bool operator!=(NFPPosition const& other) const;
    };
}
