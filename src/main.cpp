#include "Ycore.h"
#include "NQueen.h"
#include "NFPAlgorithm.h"
#include "BooleanDecisionTree.h"
#include "DecisionTree.h"
#include "YTreeNodeBase.h"
#include "DecisionTreeBuilder.h"
#include "KDTree.h"
#include "demo.h"
#include "YTensor.h"

#include "NN/nn.h"

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
	
	cout << 4. / 6. * statistics::entropy({1. / 4., 3. / 4.}) + 2. / 6. * statistics::entropy({1.}) << endl;
}



int main() {
	Float* mat1 = (Float*)malloc(2 * 3 * sizeof(Float));
	Float* mat2 = (Float*)malloc(3 * 2 * sizeof(Float));
	Float* mat3 = (Float*)malloc(3 * 3 * sizeof(Float));

	for (int i = 0; i < 2 * 3; ++i) {
		mat1[i] = Float(i + 1);
	}
	for (int i = 0; i < 3 * 2; ++i) {
		mat2[i] = Float(i + 1);
	}

	matmul(mat1, mat2, mat3, 3, 2, 3);
	print_matrix(mat3, 3, 3);
	free(mat1);
	free(mat2);
	free(mat3);
	return 0;
	//yuki::demo::GAFitFunction();
	ArrayRef a1{2, 2, 3}, a2{0, 1, 1};
	cout << a2 << endl;
	a2.selfAdd(a1);
	cout << a2 << endl;
	a2.selfAdd(a1);
	cout << a2 << endl;
	a2.selfSub(a1);
	cout << a2 << endl;
	cout <<  statistics::topK<int>({0, 4, 7, 8, 9, 1, 3, 2, 5}, 3);
	return 0;
	//csp::testBacktrackingSearch();
	//csp::testMinConflict();
    //nfp::test();
	// BDTTrainData
	// watermelon2.0
	// watermelon3.0-lack
	// iris
	string datasetName("watermelon3.0-lack");

	dt::Dataset dataset(format("../../resources/DT/{}.csv", datasetName));
	
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
		/*
		for (auto& attr: dataset.attributes) {
			cout << attr.name << ' ' << dataset.valueStrMap[attr.name][sample[attr.name]] << endl;
		}*/
		//cout << dataset.valueStrMap[dataset.target.name][tree->classify(sample)] << ' ' << dataset.valueStrMap[dataset.target.name][e.target] << endl;
		if (tree->classify(sample) == dataset.rawValues[i].back()) {
			++count;
		}
		++i;
	}
	tree->dot(format("../../resources/DT/trees/{}.dot", datasetName));
	cout << "Accuracy: " << count << '/' << dataset.rawValues.size() << " = " << count / dataset.rawValues.size() << endl;


/*
	nns::KDTree kdtree(2);

	vector<vector<f64>> examples{
		{ 1, 1 }, { 0.9, 0 }, { 0, 1 }, { 2, 2 }, { 1.1, 0.5 }, { 0.7, 0.34 }
	};

	kdtree.build(examples);

	vector<f64> target{ 0.9, 0.5 };

	cout << kdtree.search(target) << endl;

	vector<vector<f64>> points(1, examples.front());

	for (int i = 1; i < examples.size(); ++i) {
		if (distanceEuclidean(points.back(), target) > distanceEuclidean(examples[i], target)) {
			points.clear();
			points.push_back(examples[i]);
		} else if (distanceEuclidean(points.back(), target) == distanceEuclidean(examples[i], target)) {
			points.push_back(examples[i]);
		}
	}

	cout << points;

	kdtree.dot("../../kdtree.dot");
*/
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