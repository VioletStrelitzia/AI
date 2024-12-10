#pragma once
#include "core.h"
#include "YukiTools.h"

namespace yuki::atri::dt {
    enum AttributeType {
        BASE_ATTRIBUTE = 0,
        DISCRETE,
        CONTINUOUS
    };

    class Attribute {
    public:
        static f64 const ABSENT;
        i32           index;
        string        name;
        AttributeType type;
        set<f64>      values;
    };
}
