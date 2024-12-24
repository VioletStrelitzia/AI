#include "Example.h"

namespace yuki {

template <typename Data = vector<f64>, typename Target = NoTargetType>
class Dataset {
private:
    vector<Example<Data, Target>> _data;

public:
    using DataType = Data;
    using TargetType = Target;
    using ExampleType = Example<Data, Target>;

    Dataset() = default;
    ~Dataset() = default;

    auto addExample(ExampleType const& e) -> void {
        _data.push_back(e);
    }

    auto addExample(ExampleType&& e) -> void {
        _data.emplace_back(e);
    }

    operator vector<Example<Data, Target>>&() {
        return _data;
    }

    operator const vector<Example<Data, Target>>&() const {
        return _data;
    }
};

}