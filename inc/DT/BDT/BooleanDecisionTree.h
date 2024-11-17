#pragma once
#include "BDTNode.h"
#include "BDTDataset.h"

namespace yuki::atri::dt::bdt {
    class BooleanDecisionTree {
    public:
        Dataset* dataset;

        BooleanDecisionTreeNode* root;

    public:
        BooleanDecisionTree(Dataset* dataset);
        ~BooleanDecisionTree();

        /// @brief 计算布尔随机变量的信息熵
        /// @param p 该变量取 1 的概率（0 也可）
        /// @return 熵
        auto entropyBinary(f32 const& p) -> f32 {
            if (p == 0. || p == 1.) return 0;
            f32 _p = 1. - p;
            return -(p * log(p) + _p * log(_p));
        }

        auto entropyRemain(string const& attribute, vector<Example> const& examples) -> f32 {
            f32 result = 0.;
            for (string const& option: dataset->attributesOptions[attribute]) {
                vector<Example> exs = dataset->getExamples(examples, attribute, option);
                f32 pk = (f32)exs.size() / (f32)examples.size();
                f32 nk = entropyBinary((f32)positiveCount(exs) / (f32)exs.size());
                result += pk + nk;
            }
            return result;
        }

        /// @brief 计算信息增益
        /// @param attribute 
        /// @param examples 
        /// @return 
        auto infoGain(string const& attribute, vector<Example> const& examples) -> f32 {
            return entropyBinary((f32)positiveCount(examples) / (f32)examples.size()) - entropyRemain(attribute, examples);
        }

        auto importance(vector<string> const& attributes, vector<Example> const& examples) -> string {
            usize attributeIndex = 0;
            f32 maxInfoGain = infoGain(attributes[0], examples), curInfoGain;
            for (usize i = 1, end = attributes.size(); i < end; ++i) {
                curInfoGain = infoGain(attributes[i], examples);
                if (curInfoGain > maxInfoGain) {
                    maxInfoGain = curInfoGain;
                    attributeIndex = i;
                }
            }
            return attributes[attributeIndex];
        }

        auto removeAttritude(string const& attribute, vector<string> const& attributes) -> vector<string> {
            vector<string> result;
            for (string const& attr: attributes) {
                if (attr == attribute) {
                    continue;
                }
                result.push_back(attr);
            }
            return result;
        }

        auto pluralityValue(vector<Example> const& examples) -> BooleanDecisionTreeNode* {
            i32 positiveCount = 0;
            for (Example const& example: examples) {
                if (example.label) {
                    ++positiveCount;
                }
            }

            i32 negtiveCount = (i32)examples.size() - positiveCount;
            return new BooleanDecisionTreeNode(positiveCount >= negtiveCount, dataset->labelAttribute);
        }

        auto filterExamples(vector<Example> const& examples, string const& attribute, string const& option) -> vector<Example> {
            vector<Example> result;
            i32 attributeIndex = dataset->getAttributeIndex(attribute);
            for (Example const& example: examples) {
                if (example.data[attributeIndex] == option) {
                    result.push_back(example);
                }
            }
            return result;
        }

        auto learn(vector<Example> const& remainExamples, vector<string> const& remainAttributes, vector<Example> const& parentExamples = {}) -> BooleanDecisionTreeNode* {
            if (remainExamples.empty()) {
                return pluralityValue(parentExamples);
            } else if (isSameClassify(remainExamples)) {
                return new BooleanDecisionTreeNode(remainExamples[0].label, dataset->labelAttribute);
            } else if (remainAttributes.empty()) {
                return pluralityValue(remainExamples);
            } else {
                string A = importance(remainAttributes, remainExamples);
                vector<string> subAttributes = removeAttritude(A, remainAttributes);
                BooleanDecisionTreeNode* root = new BooleanDecisionTreeNode(A);
                for (string const& option: dataset->attributesOptions[A]) {
                    root->options[option] = learn(filterExamples(remainExamples, A, option), subAttributes, remainExamples);
                }
                return root;
            }
        }

        auto build() -> void {
            if (dataset) {
                cout << "Boolean decision tree learning start..." << endl;
                root = learn(dataset->examples, dataset->attributes);
                cout << "Boolean decision tree learning finished." << endl;
            }
        }

        auto load(string const& filename) -> void {
            
        }

        auto save(string const& filename) -> void {
            
        }


        /// @brief 样本中有多少个正例
        /// @param examples 样本
        /// @return 样本中正例个数
        i32 positiveCount(vector<Example> const& examples) {
            i32 count = 0;
            for (Example const& example: examples) {
                if (example.label) {
                    ++count;
                }
            }
            return count;
        }

        /// @brief 判断样本分类是否相同
        /// @param examples 样本
        /// @return 样本分类是否相同
        bool isSameClassify(vector<Example> const& examples) {
            if (examples.empty()) {
                return true;
            }
            bool label = examples[0].label;
            for (Example const& example: examples) {
                if (example.label != label) {
                    return false;
                }
            }
            return true;
        }

        void printTree() {
            _printTree(root, 0);
        }

        void printSpacer(i32 const& number) {
            for (i32 i = 0; i < number; ++i) {
                cout << '\t';
            }
        }

        void _printTree(BooleanDecisionTreeNode*& root, i32 const& depth) {
            printSpacer(depth);
            if (root->options.empty()) {
                cout << root->attritude << ": " << root->value << endl;
            } else {
                cout << "Split on " << root->attritude << endl;
                for (pair<string, BooleanDecisionTreeNode*> p : root->options) {
                    printSpacer(depth);
                    cout << "If " << root->attritude << " == " << p.first << endl;
                    _printTree(p.second, depth + 1);
                }
            }
        }

    };
    
    BooleanDecisionTree::BooleanDecisionTree(Dataset* dataset):
        dataset(dataset), root(nullptr) {}
    
    BooleanDecisionTree::~BooleanDecisionTree() {
        delete root;
    }
    
}