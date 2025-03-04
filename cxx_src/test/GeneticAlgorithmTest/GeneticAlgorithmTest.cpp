#include "GA.h"

using namespace yuki;
using namespace yuki::atri::ga;

auto testGAFitFunction() -> void {
    // pow(x, 2.71828182845904523536) - 3. * pow(x, atan(3.14159265358979323846 * x)) + 3 + sin(3.14159265358979323846 * 5. * x)
    // pow(x, 2.71828182845904523536) - 3. * pow(x, atan(3.14159265358979323846 * x)) + 3
    // sin(x)
    
    function<f64(f64 const&)> fitFunc = [](f64 const& x) -> f64 {
        return pow(x, 2.71828182845904523536) - 3. * pow(x, atan(3.14159265358979323846 * x)) + 3 + sin(3.14159265358979323846 * 5. * x);
    };

    atri::ga::GA<bool> g(2, 0, 0.000001, 64, fitFunc);
    g.solution(100);
}

int main() {
    testGAFitFunction();
}