#pragma once
#include "core.h"

namespace yuki::atri::dt {
    class Example {
    public:
        vector<string> data;
        string targetValue;

    public:
        Example();
        
        Example(vector<string> const& data_, string const& label_, bool const& isPop = false);
    };

    auto subExamples(i32 const& attributeIndex, string const& value , vector<Example*> const& examples) -> vector<Example*>;

    auto countTargetValue(string const& targetValue, vector<Example*> const& examples) -> i32;
}