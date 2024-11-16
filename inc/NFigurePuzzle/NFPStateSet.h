#pragma once
#include "NFPState.h"

namespace yuki::nfp {
    class NFPStateSet {
    private:
        set<usize> s;

    public:
        NFPStateSet() = default;
        ~NFPStateSet() = default;

        void clear();

        bool visited(NFPState const& state);

        void visit(NFPState const& state);

        void remove(NFPState const& state);
    };
}
