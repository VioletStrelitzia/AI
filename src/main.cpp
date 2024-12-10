#include "core.h"
#include "NQueen.h"
#include "NFPAlgorithm.h"
#include "BooleanDecisionTree.h"
#include "DecisionTree.h"
#include "TreeNodeBase.h"
#include "DecisionTreeBuilder.h"
#include "KDTree.h"

using namespace yuki;
using namespace yuki::atri;

auto testDTQuickSort() -> void {
	vector<dt::Example> exs(6);
	exs[0].data = { 1.0, 0.2, 0.5 };
	exs[1].data = { 3.0, 0.6, 0.5 };
	exs[2].data = { -1.0, 0.4, 0.5 };
	exs[3].data = { 6.0, 0.2, 1 };
	exs[4].data = { 2.0, 0.2, 1 };
	exs[5].data = { -2.0, 0.4, 1 };

	exs[0].target = 1;
	exs[1].target = 0;
	exs[2].target = 1;
	exs[3].target = 0;
	exs[4].target = 1;
	exs[5].target = 0;

	dt::Attribute target;
	target.index = 0;
	target.name = "target";
	target.type = dt::AttributeType::DISCRETE;
	target.values = { 0, 1 };

	vector<dt::Attribute> attrs(3);
	attrs[0].index = 0;
	attrs[0].name = "first";
	attrs[0].type = dt::AttributeType::CONTINUOUS;
	attrs[0].values = { 0, 5 };
	
	attrs[1].index = 1;
	attrs[1].name = "second";
	attrs[1].type = dt::AttributeType::DISCRETE;
	attrs[1].values = { 0.2, 0.4, 0.6 };

	attrs[2].index = 2;
	attrs[2].name = "third";
	attrs[2].type = dt::AttributeType::DISCRETE;
	attrs[2].values = { 0.5, 1 };

	vector<pair<dt::Example*, f64>> exsp;
	for (auto& e: exs) {
		exsp.push_back({ &e, 1. });
	}

	dt::DecisionTreeBuilder::quickSort(exsp, &attrs[0]);

	for (auto& ep: exsp) {
		cout << ep.first->data[0] << ' ';
	}cout << endl;

	for (auto& ep: exsp) {
		cout << ep.first->target << ' ';
	}cout << endl;

	cout << dt::DecisionTreeBuilder::infoGain(&attrs[0], &target, exsp) << endl;
	
	cout << 4. / 6. * entropy({1. / 4., 3. / 4.}) + 2. / 6. * entropy({1.}) << endl;
}

int main() {
	//csp::testBacktrackingSearch();
	//csp::testMinConflict();
    //nfp::test();
	// BDTTrainData
	// watermelon2.0
	// watermelon3.0-lack
	// iris
	/*
	string datasetName("watermelon2.0-train");

	dt::Dataset dataset(format("../../resources/DT/{}.csv", datasetName));
	dt::Dataset testDataset(format("../../resources/DT/watermelon2.0-test.csv"));*/
	/*
	for (auto& a: dataset.attributes) {
		cout << a << ' ';
	}
	cout << endl << dataset.targetAttribute << endl;
	for (auto& e: dataset.examples) {
		for (auto& s: e.data) {
			cout << s << ' ';
		}
		cout << "\nlable " << e.lable << endl;
	}*/


	/*dt::bdt::BooleanDecisionTree t(dataset);
	t.train(&dataset);
	t.printTree();
	cout << endl;*/
	/*
	auto tree = dt::DecisionTreeBuilder::learn(&dataset, "InfoGain");
	cout << *tree;

	i32 i = 0;
	f64 count = 0.;
	for (auto& e: testDataset.examples) {
		map<string, f64> sample;
		for (auto& attr: testDataset.attributes) {
			sample[attr.name] = e.data[attr.index];
			//cout << attr.name << ' ' << e.data[attr.index] << endl;
		}
		//cout << tree->classify(sample) << ' ' << e.target << endl;
		if (tree->classify(sample) == testDataset.rawValues[i].back()) {
			++count;
		}
		++i;
	}
	tree->dot(format("../../resources/DT/trees/{}.dot", datasetName));
	cout << "Accuracy: " << count << '/' << testDataset.rawValues.size() << " = " << count / testDataset.rawValues.size() << endl;
	*/

	nns::KDTree kdtree(2);

	vector<vector<f64>> examples{
		{ 1, 1 }, { 0.9, 0 }, { 0, 1 }, { 2, 2 }, { 1.1, 0.5 }, { 0.7, 0.34 }
	};

	kdtree.build(examples);

	vector<f64> target{ 0.9, 0.5 };

	cout << kdtree.search(target) << endl;

	vector<vector<f64>> points(1, examples.front());

	for (int i = 1; i < examples.size(); ++i) {
		if (distance(points.back(), target) > distance(examples[i], target)) {
			points.clear();
			points.push_back(examples[i]);
		} else if (distance(points.back(), target) == distance(examples[i], target)) {
			points.push_back(examples[i]);
		}
	}

	cout << points;

	kdtree.dot("../../kdtree.dot");

/*
    vector<i32> numbers{ 1, 2, 3, 4, 5, 6 };
    auto results = numbers
		| views::filter([](i32 n) { return n % 2 == 0; })
        | views::transform([](i32 n) { return n * 2; });
	rg::for_each(results, [](i32 const& x) { cout << x << ' '; });
*/

	//system("pause");
	return 0;
}