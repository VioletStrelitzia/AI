#pragma once
#include "Ycore.h"
#include "Ytools.h"

namespace yuki {

class ArrayRef: public vector<i32> {
public:
    using std::vector<i32>::vector;

    auto checkShape(ArrayRef const& shape) -> ArrayRef& {
        i32 carry = 0, end = static_cast<i32>(size());
        for (i32 i = 0; i < end; ++i) {
            this->at(i) += carry;
            if (this->at(i) >= shape[i]) {
                carry = this->at(i) / shape[i];
                this->at(i) %= shape[i];
            } else if (this->at(i) < 0) {
                carry = -1;
                this->at(i) += shape[i];
                while (this->at(i) < 0) {
                    --carry;
                    this->at(i) += shape[i];
                }
            }
        }
        return *this;
    }

    auto selfAdd(ArrayRef const& shape) -> ArrayRef& {
        ++front();
        return checkShape(shape);
    }

    auto selfSub(ArrayRef const& shape) -> ArrayRef& {
        --front();
        return checkShape(shape);
    }
};

class Tensor {
private:
    vector<f64> _data;
    ArrayRef _shape;

public:
    using InitFunc = function<f64(ArrayRef const& pos, ArrayRef const& shape)>;

    static auto ones() -> Tensor {

    }

    Tensor() = default;

    Tensor(ArrayRef const& shape, InitFunc const& initFunc = nullptr):
        _data(statistics::product(shape)), _shape(shape) {
        if (initFunc) {

        }
    }

    ~Tensor() = default;

    auto dim() const -> i32 {
        return static_cast<i32>(_shape.size());
    }

};

}