#include "NFPStateSet.h"

namespace yuki::atri::nfp {
    void StateSet::clear() {
        s.clear();
    }

    bool StateSet::visited(State const& NFPState) {
        return s.find(NFPState.data) != s.end();
    }

    void StateSet::visit(State const& NFPState) {
        s.insert(NFPState.data);
    }

    void StateSet::remove(State const& NFPState) {
        s.erase(NFPState.data);
    }
}
