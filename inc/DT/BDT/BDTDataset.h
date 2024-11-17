#pragma once
#include "BDTExample.h"

namespace yuki::atri::dt::bdt {
    class Dataset {
    public:
        vector<string>           attributes;      // 特征列表
        string                   labelAttribute;  // 标签的名称
        vector<vector<string>>   rawValues;       // 数据列表，每条数据包含所有特征和一个标签（在末尾）
        vector<Example>          examples;        // 把数据保存为 Example 的形式
        map<string, set<string>> attributesOptions;

        auto buildExample(vector<string> const& values, bool const& hasLable = true) -> Example {
            bool lable = false;
            if (hasLable) {
                lable = getLabel(values.back());
            }
            return Example(values, lable, hasLable);
        }

    public:
        Dataset(string const& filename) {
            ifstream inFile(filename);
            if (inFile.fail()) {
                cout << "cannot open file: " << filename << endl;
            }

            string line;
            if (getline(inFile, line)) {
                attributes = readValues(line);
                labelAttribute = attributes.back();
            }
            for (string const& attribute: attributes) {
                if (getline(inFile, line)) {
                    attributesOptions[attribute] = readOptions(line);
                }
            }
            while (getline(inFile, line)) {
                vector<string> values = readValues(line);
                rawValues.push_back(values);
                examples.push_back(buildExample(values, values.size() >= labelAttribute.size()));
            }
            attributes.pop_back();
        }

        auto getLabel(string const& value) -> bool {
            return value == "1"; 
        }

        auto getAttributeIndex(string const& attribute) -> i32 {
            for (usize i = 0; i < attributes.size(); ++i) {
                if (attributes[i] == attribute) {
                    return (i32)i;
                }
            }
            return -1;
        }

        auto getExamples(vector<Example> const& examples, string const& attribute, string const& option) -> vector<Example> {
            vector<Example> result;
            i32 attributeIndex = getAttributeIndex(attribute);
            for (Example const& example: examples) {
                if (example.data[attributeIndex] == option) {
                    result.push_back(example);
                }
            }
            return result;
        }

        auto readValues(string const& line) -> vector<string> {
            stringstream ss(line);
            string value;
            vector<string> values;
            while (getline(ss, value, ',')) {
                values.push_back(value);
            }
            return values;
        }

        auto readOptions(string const& line) -> set<string> {
            stringstream ss(line);
            string option;
            set<string> options;
            while (getline(ss, option, ',')) {
                options.insert(option);
            }
            return options;
        }
    };
}