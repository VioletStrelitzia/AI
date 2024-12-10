#include "core.h"

namespace yuki::atri {
    class Evaluation {
    public:
        Evaluation() = default;
        ~Evaluation() = default;

        virtual auto run(void* input_) -> void = 0;
    };
}