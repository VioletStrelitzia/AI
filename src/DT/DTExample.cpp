#include "DTExample.h"

namespace yuki::atri::dt {
    Example::Example():
        data(), targetValue("0") {}

    Example::Example(vector<string> const& data_, string const& label_, bool const& isPop):
        data(data_), targetValue(label_) {
        if (isPop) {
            data.pop_back();
        }
    }

    auto subExamples(i32 const& attributeIndex, string const& value , vector<Example*> const& examples) -> vector<Example*> {
        vector<Example*> subExamples;
        for (Example* const& example: examples) {
            if (example->data[attributeIndex] == value) {
                subExamples.push_back(example);
            }
        }
        return subExamples;
    }

    auto countTargetValue(string const& targetValue, vector<Example*> const& examples) -> i32 {
        i32 count = 0;
        for (Example* const& example: examples) {
            if (example->targetValue == targetValue) {
                ++count;
            }
        }
        return count;
    }
}