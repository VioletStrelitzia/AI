#include "NFPStateSet.h"

namespace yuki::nfp {
    void NFPStateSet::clear() {
        s.clear();
    }

    bool NFPStateSet::visited(NFPState const& NFPState) {
        return s.find(NFPState.data) != s.end();
    }

    void NFPStateSet::visit(NFPState const& NFPState) {
        s.insert(NFPState.data);
    }

    void NFPStateSet::remove(NFPState const& NFPState) {
        s.erase(NFPState.data);
    }
}
