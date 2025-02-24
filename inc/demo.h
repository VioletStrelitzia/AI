#pragma once
#include "NQueen.h"
#include "NFPAlgorithm.h"
#include "BooleanDecisionTree.h"
#include "DecisionTree.h"
#include "YTreeNodeBase.h"
#include "DecisionTreeBuilder.h"
#include "KDTree.h"
#include "GA.h"

namespace yuki::demo {
auto decisionTreePostcut() -> void {
    string datasetName("watermelon2.0-train");

    atri::dt::Dataset dataset(format("../../resources/DT/{}.csv", datasetName));
    atri::dt::Dataset testDataset(format("../../resources/DT/watermelon2.0-test.csv"), &dataset.strValueMap);
    
    for (auto const& x1: dataset.valueStrMap) {
        cout << x1.first << " | ";
        for (auto const& p: x1.second) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    for (auto const& x1: testDataset.valueStrMap) {
        cout << x1.first << " | ";
        for (auto const& p: x1.second) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    auto tree = atri::dt::DecisionTreeBuilder::learn<atri::dt::DecisionTreeBuilder::CriterionType::INFO_GAIN, false, false>(&dataset);
    cout << *tree;

    i32 i = 0;
    f64 count = 0.;
    for (auto& e: testDataset.examples) {
        unordered_map<string, f64> sample;
        for (auto& attr: testDataset.attributes) {
            sample[attr.name] = e.data[attr.index];
        }
        /*
        for (auto& attr: testDataset.attributes) {
            cout << attr.name << ' ' << testDataset.valueStrMap[attr.name][sample[attr.name]] << endl;
        }*/
        //cout << testDataset.valueStrMap[testDataset.target.name][tree->classify(sample)] << ' ' << testDataset.valueStrMap[testDataset.target.name][e.target] << endl;
        if (tree->classify(sample) == testDataset.rawValues[i].back()) {
            ++count;
        }
        ++i;
    }
    tree->dot(format("../../resources/DT/trees/{}.dot", datasetName));
    cout << "Accuracy: " << count << '/' << testDataset.rawValues.size() << " = " << count / testDataset.rawValues.size() << endl;

    atri::dt::DecisionTreeBuilder::postCut(tree, &testDataset);
    i = 0;
    count = 0.;
    for (auto& e: testDataset.examples) {
        unordered_map<string, f64> sample;
        for (auto& attr: testDataset.attributes) {
            sample[attr.name] = e.data[attr.index];
            //cout << attr.name << ' ' << testDataset.valueStrMap[attr.name][e.data[attr.index]] << endl;
        }
        //cout << testDataset.valueStrMap[testDataset.target.name][tree->classify(sample)] << ' ' << testDataset.valueStrMap[testDataset.target.name][e.target] << endl;
        if (tree->classify(sample) == testDataset.rawValues[i].back()) {
            ++count;
        }
        ++i;
    }
    tree->dot(format("../../resources/DT/trees/{}_post_cut.dot", datasetName));
    cout << "Accuracy: " << count << '/' << testDataset.rawValues.size() << " = " << count / testDataset.rawValues.size() << endl;

}

auto GAFitFunction() -> void {
    // pow(x, 2.71828182845904523536) - 3. * pow(x, atan(3.14159265358979323846 * x)) + 3 + sin(3.14159265358979323846 * 5. * x)
    // pow(x, 2.71828182845904523536) - 3. * pow(x, atan(3.14159265358979323846 * x)) + 3
    // sin(x)
    
    function<f64(f64 const&)> fitFunc = [](f64 const& x) -> f64 {
        return pow(x, 2.71828182845904523536) - 3. * pow(x, atan(3.14159265358979323846 * x)) + 3 + sin(3.14159265358979323846 * 5. * x);
    };

    atri::ga::GA<bool> g(2, 0, 0.000001, 64, fitFunc);
    g.solution(100);
}

/**
 * @brief kd 树测试函数
 * 
 */
auto KDTreeTest() -> void {
	yuki::atri::nns::KDTree kdtree(2);

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
}

}