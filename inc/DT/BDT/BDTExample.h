#pragma once
#include "core.h"

namespace yuki::atri::dt::bdt {
    class Example {
    public:
        vector<string> data;
        bool label;

    public:
        Example():
            data(), label(false) {}

        Example(vector<string> const& data_, bool const& label_, bool const& isPop = false):
            data(data_), label(label_) {
            if (isPop) {
                data.pop_back();
            }
        }
    };
}