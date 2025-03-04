#include "DecisionTree.h"
#include "DTDataset.h"
#include "DecisionTreeBuilder.h"
#include "core.h"

using namespace yuki;
using namespace yuki::atri;
int main() {
	string datasetName("watermelon3.0-lack");

	dt::Dataset dataset(format("../../../../resources/DT/{}.csv", datasetName));
	
    
	for (auto const& x1: dataset.valueStrMap) {
		cout << x1.first << " | ";
		for (auto const& p: x1.second) {
			cout << "(" << p.first << ", " << p.second << ") ";
		}
		cout << endl;
	}

	auto tree = dt::DecisionTreeBuilder::learn<dt::DecisionTreeBuilder::CriterionType::INFO_GAIN, false, false>(&dataset);
	cout << *tree;

	i32 i = 0;
	f64 count = 0.;
	for (auto& e: dataset.examples) {
		unordered_map<string, f64> sample;
		for (auto& attr: dataset.attributes) {
			sample[attr.name] = e.data[attr.index];
		}
		
		//for (auto& attr: dataset.attributes) {
		//	cout << attr.name << ' ' << dataset.valueStrMap[attr.name][sample[attr.name]] << endl;
		//}

		//cout << dataset.valueStrMap[dataset.target.name][tree->classify(sample)] << ' ' << dataset.valueStrMap[dataset.target.name][e.target] << endl;
		if (tree->classify(sample) == dataset.rawValues[i].back()) {
			++count;
		}
		++i;
	}
	tree->dot(format("../../../../resources/DT/trees/{}.dot", datasetName));
	cout << "Accuracy: " << count << '/' << dataset.rawValues.size() << " = " << count / dataset.rawValues.size() << endl;
    system("pause");
    
    return 0;
}