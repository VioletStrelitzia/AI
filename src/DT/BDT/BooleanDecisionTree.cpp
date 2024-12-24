#include "BooleanDecisionTree.h"

namespace yuki::atri::dt::bdt {
    BooleanDecisionTree::BooleanDecisionTree(Dataset& dataset):
        attributes(dataset.attributes),
        targetAttribute(dataset.target),
        root(nullptr) {
        i32 i = 0;
        for (Attribute const& attribute: dataset.attributes) {
            attributeIndexMap[attribute.name] = i++;
        }
    }
    
    BooleanDecisionTree::~BooleanDecisionTree() {
        delete root;
    }

    auto BooleanDecisionTree::getExamples(vector<Example*> const& examples, i32 const& attributeIndex, f64 const& value) -> vector<Example*> {
        vector<Example*> result;
        for (Example* const& example: examples) {
            if (example->data[attributeIndex] == value) {
                result.push_back(example);
            }
        }
        return result;
    }

    auto BooleanDecisionTree::entropyRemain(i32 const& attributeIndex, vector<Example*> const& examples) -> f64 {
        f64 result = 0.;
        for (f64 const& value: attributes[attributeIndex].values) {
            vector<Example*> exs = getExamples(examples, attributeIndex, value);
            if (!exs.empty()) {
                f64 pk = (f64)exs.size() / (f64)examples.size();
                f64 nk = statistics::entropyBinary((f64)positiveCount(exs) / (f64)exs.size());
                result += pk * nk;
            }
        }
        return result;
    }

    auto BooleanDecisionTree::infoGain(i32 const& attributeIndex, vector<Example*> const& examples) -> f64 {
        return statistics::entropyBinary((f64)positiveCount(examples) / (f64)examples.size()) - entropyRemain(attributeIndex, examples);
    }

    auto BooleanDecisionTree::importance(vector<i32> const& attributeIndexs, vector<Example*> const& examples) -> i32 {
        usize attributeIndex = 0;
        f64 maxInfoGain = infoGain(attributeIndexs[0], examples);
        f64 curInfoGain;
        for (usize i = 1, end = attributeIndexs.size(); i < end; ++i) {
            curInfoGain = infoGain(attributeIndexs[i], examples);
            if (curInfoGain > maxInfoGain) {
                maxInfoGain = curInfoGain;
                attributeIndex = i;
            }
        }
        return attributeIndexs[attributeIndex];
    }

    auto BooleanDecisionTree::removeAttritude(i32 const& attributeIndex, vector<i32> const& attributeIndexs) -> vector<i32> {
        vector<i32> result;
        for (i32 const& i: attributeIndexs) {
            if (i != attributeIndex) {
                result.push_back(i);
            }
        }
        return result;
    }

    auto BooleanDecisionTree::pluralityValue(vector<Example*> const& examples) -> BooleanDecisionTreeNode* {
        i32 positiveCount = 0;
        for (Example* const& example: examples) {
            if (example->target == 1) {
                ++positiveCount;
            }
        }
        i32 negtiveCount = (i32)examples.size() - positiveCount;
        // 根据多数表决值创建决策树节点并返回
        return new BooleanDecisionTreeNode(positiveCount >= negtiveCount, targetAttribute.name);
    }

    auto BooleanDecisionTree::filterExamples(vector<Example*> const& examples, i32 const& attributeIndex, f64 const& value) -> vector<Example*> {
        vector<Example*> result;
        for (Example* const& example: examples) {
            if (example->data[attributeIndex] == value) {
                result.push_back(example);
            }
        }
        return result;
    }

    auto BooleanDecisionTree::learn(vector<Example*> const& remainExamples, vector<i32> const& remainAttributes, vector<Example*> const& parentExamples) -> BooleanDecisionTreeNode* {
        if (remainExamples.empty()) {
            return pluralityValue(parentExamples);
        } else if (isSameClassify(remainExamples)) {
            return new BooleanDecisionTreeNode(remainExamples[0]->target == 1, targetAttribute.name);
        } else if (remainAttributes.empty()) {
            return pluralityValue(remainExamples);
        } else {
            i32 AIndex = importance(remainAttributes, remainExamples);
            vector<i32> subAttributes = removeAttritude(AIndex, remainAttributes);
            BooleanDecisionTreeNode* root = new BooleanDecisionTreeNode(attributes[AIndex].name);
            for (f64 const& value: attributes[AIndex].values) {
                root->options[value] = learn(filterExamples(remainExamples, AIndex, value), subAttributes, remainExamples);
            }
            return root;
        }
    }

    auto BooleanDecisionTree::train(void* dataset_) -> void {
        Dataset& dataset = *(Dataset*)dataset_;
        attributes = dataset.attributes;
        targetAttribute = dataset.target;

        // 存指针和序号，减少拷贝开销
        vector<i32> attributeIndexs;
        i32 i = 0;
        for (Attribute const& attribute: attributes) {
            attributeIndexs.push_back(i);
            attributeIndexMap[attribute.name] = i++;
        }
        vector<Example*> examples;
        for (Example& example: dataset.examples) {
            examples.push_back(&example);
        }
        
        delete root;
        root = nullptr;

        cout << "Boolean decision tree learning start..." << endl;
        root = learn(examples, attributeIndexs);
        cout << "Boolean decision tree learning finished." << endl;
    }

    auto BooleanDecisionTree::load(string const& filename) -> void {
        
    }

    auto BooleanDecisionTree::save(string const& filename) -> void {
        
    }

    i32 BooleanDecisionTree::positiveCount(vector<Example*> const& examples) {
        i32 count = 0;
        for (Example* const& example: examples) {
            if (example->target == 1) {
                ++count;
            }
        }
        return count;
    }

    bool BooleanDecisionTree::isSameClassify(vector<Example*> const& examples) {
        if (examples.empty()) {
            return true;
        }
        f64 target = examples[0]->target;
        for (Example* const& example: examples) {
            if (example->target != target) {
                return false;
            }
        }
        return true;
    }

    void BooleanDecisionTree::printTree() {
        _printTree(root, 0);
    }

    void BooleanDecisionTree::_printTree(BooleanDecisionTreeNode*& root, i32 const& depth) {
        printSpacer(depth);
        if (root->options.empty()) {
            cout << root->attribute << ": " << root->value << endl;
        } else {
            cout << "Split on " << root->attribute << endl;
            for (pair<f64, BooleanDecisionTreeNode*> p : root->options) {
                printSpacer(depth);
                cout << "If " << root->attribute << " == " << p.first << endl;
                _printTree(p.second, depth + 1);
            }
        }
    }
}