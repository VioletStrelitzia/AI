#include "NQueen.h"

using namespace yuki;
using namespace yuki::atri;
int main() {
	csp::testBacktrackingSearch(12);
	csp::testMinConflict(16, 500);
    system("pause");
    return 0;
}