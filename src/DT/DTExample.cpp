#include "DTExample.h"

namespace yuki::atri::dt {
    Example::Example():
        data(), target(0.) {}

    Example::Example(vector<f64> const& data_, f64 const& label_, bool const& isPop):
        data(data_), target(label_) {
        if (isPop) {
            data.pop_back();
        }
    }

    auto subExamples(Attribute const* const& attr, f64 const& value, vector<Example*> const& examples) -> vector<Example*> {
        vector<Example*> subExamples;
        for (Example* const& example: examples) {
            if (example->data[attr->index] == value) {
                subExamples.push_back(example);
            }
        }
        return subExamples;
    }

    auto countTargetValue(f64 const& targetValue, vector<Example*> const& examples) -> i32 {
        i32 count = 0;
        for (Example* const& example: examples) {
            if (example->target == targetValue) {
                ++count;
            }
        }
        return count;
    }
}