#include "core.h"
#include "NQueen.h"
#include "NFPAlgorithm.h"
#include "BooleanDecisionTree.h"

using namespace yuki;
using namespace yuki::atri;

int main() {
	//csp::testBacktrackingSearch();
	//csp::testMinConflict();
    //nfp::test();
	dt::Dataset dataset("../../resources/BDTTrainData.csv");
	for (auto& a: dataset.attributes) {
		cout << a << ' ';
	}
	cout << endl << dataset.targetAttribute << endl;
	for (auto& e: dataset.examples) {
		for (auto& s: e.data) {
			cout << s << ' ';
		}
		cout << "\nlable " << e.targetValue << endl;
	}
	dt::bdt::BooleanDecisionTree t(dataset);
	t.build(dataset);
	t.printTree();
	//system("pause");
	return 0;
}