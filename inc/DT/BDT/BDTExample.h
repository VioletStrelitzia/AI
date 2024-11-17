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

        Example(vector<string> const& data, bool const& label):
            data(data), label(label) {}
    };
}