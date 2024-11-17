#pragma once
#include "NFPState.h"

namespace yuki::atri::nfp {
    class StateSet {
    private:
        set<usize> s;

    public:
        StateSet() = default;
        ~StateSet() = default;

        void clear();

        bool visited(State const& state);

        void visit(State const& state);

        void remove(State const& state);
    };
}
