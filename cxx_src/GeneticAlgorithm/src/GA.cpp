#include "GA.h"

namespace yuki::atri::ga {
    template <typename Gene>
    auto GA<Gene>::FitnessInfo::print() -> void {
        for (i32 i = 0; i < fitnesses.size(); ++i) {
            for (i32 j = 0; j < 5 && i < fitnesses.size(); ++j, ++i) {
                cout << std::setw(5) << fitnesses[i] << ' ';
            }
            cout << endl;
        }
        cout << sum << endl;
    }
}