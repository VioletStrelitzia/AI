#include "NFPPosition.h"

namespace yuki::nfp {
    NFPPosition::NFPPosition(int const& r, int const& c) :
        r(r), c(c) {}

    NFPPosition NFPPosition::operator+(NFPPosition const& other) {
        return { r + other.r, c + other.c };
    }

    NFPPosition NFPPosition::operator-(NFPPosition const& other) {
        return { r - other.r, c - other.c };
    }

    bool NFPPosition::operator==(NFPPosition const& other) const {
        return r == other.r && c == other.c;
    }

    bool NFPPosition::operator!=(NFPPosition const& other) const {
        return r != other.r || c != other.c;
    }
}
