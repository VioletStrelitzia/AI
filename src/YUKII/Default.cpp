#include "Default.h"

namespace yuki::dflt {
    auto OutOfRange::defaultInfo(string const& add) const -> string {
        return "OutOfRange\n" + add;
    }
    
    auto BadAlloc::defaultInfo(string const& add) const -> string {
        return "BadAlloc\n" + add;
    }
    
    auto DivideByZero::defaultInfo(string const& add) const -> string {
        return "DivideByZero\n" + add;
    }

    auto UnexpectedEnumParameter::defaultInfo(string const& add) const -> string {
        return "UnexpectedEnumParameter\n" + add;
    }

    auto LoadFailed::defaultInfo(string const& add) const -> string {
        return "Load Failed!\n" + add;
    }

    auto SaveFailed::defaultInfo(string const& add) const -> string {
        return "Save Failed!\n" + add;
    }

    auto DimensionMismatch::defaultInfo(string const& add) const -> string {
        return "DimensionMismatch\n" + add;
    }
}