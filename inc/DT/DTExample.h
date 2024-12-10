#pragma once
#include "core.h"
#include "Attribute.h"

namespace yuki::atri::dt {
    class Example {
    public:
        vector<f64> data;
        f64 target;

    public:
        Example();
        
        Example(vector<f64> const& data_, f64 const& target_, bool const& isPop = false);
    };

    auto subExamples(Attribute const* const& attributeIndex, f64 const& value , vector<Example*> const& examples) -> vector<Example*>;

    auto countTargetValue(f64 const& targetValue, vector<Example*> const& examples) -> i32;
}