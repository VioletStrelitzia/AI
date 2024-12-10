#include "DTDataset.h"

namespace yuki::atri::dt {
    auto Dataset::buildExample(vector<f64> const& values, bool const& hasLable) -> Example {
        return Example(values, values.back(), hasLable);
    }

    Dataset::Dataset(string const& filename) {
        ifstream inFile(filename);
        if (inFile.fail()) {
            cout << "cannot open file: " << filename << endl;
            return;
        }
        string line, valueStr;
        f64 value;

        // 读取属性名称
        if (getline(inFile, line)) {
            vector<string> names = readStrValues(line);
            attributes = vector<Attribute>(names.size());
            for (i32 i = 0; i < attributes.size(); ++i) {
                attributes[i].index = i;
                attributes[i].name = names[i];
            }
        }

        // 读取属性为离散值还是连续值
        if (getline(inFile, line)) {
            vector<string> names = readStrValues(line);
            for (i32 i = 0; i < attributes.size(); ++i) {
                attributes[i].type = (stoi(names[i]) ? AttributeType::DISCRETE : AttributeType::CONTINUOUS);
            }
        }

        vector<bool> canRead(attributes.size(), true);
        vector<pair<f64, map<string, f64>>> countType(attributes.size(), { 0, map<string, f64>() });

        // 读取属性是否可以直接读取，还是需要转换成数值
        if (getline(inFile, line)) {
            vector<string> reads = readStrValues(line);
            for (i32 i = 0; i < attributes.size(); ++i) {
                canRead[i] = stoi(reads[i]);
            }
        }

        // 连续读取每行数据
        while (getline(inFile, line)) {
            stringstream ss(line);
            i32 i = 0;

            rawValues.push_back(vector<f64>());
            while (getline(ss, valueStr, ',')) {
                // 处理缺省属性
                if (valueStr.empty()) {
                    value = Attribute::ABSENT;
                } else {
                    if (canRead[i]) {
                        value = stod(valueStr);
                    } else {
                        if (countType[i].second.find(valueStr) == countType[i].second.end()) {
                            countType[i].second[valueStr] = countType[i].first++;
                        }
                        value = countType[i].second[valueStr];
                    }
                    if (attributes[i].type == AttributeType::DISCRETE) {
                        attributes[i].values.insert(value);                    
                    }
                }
                rawValues.back().push_back(value);
                ++i;
            }
            // 检查最后目标属性是否缺失，缺失则抛弃
            if (line.back() == ',') {
                rawValues.pop_back();
            } else {
                examples.push_back(buildExample(rawValues.back(), 1));
            }
        }

        // 最后一个属性为目标
        target = attributes.back();
        attributes.pop_back();
    }

    auto Dataset::getAttributeIndex(string const& attribute) -> i32 {
        for (usize i = 0; i < attributes.size(); ++i) {
            if (attributes[i].name == attribute) {
                return (i32)i;
            }
        }
        return -1;
    }

    auto Dataset::getExamples(vector<Example> const& examples, string const& attribute, f64 const& option) -> vector<Example> {
        vector<Example> result;
        i32 attributeIndex = getAttributeIndex(attribute);
        for (Example const& example: examples) {
            if (example.data[attributeIndex] == option) {
                result.push_back(example);
            }
        }
        return result;
    }

    auto Dataset::readValues(string const& line) -> vector<f64> {
        stringstream ss(line);
        string value;
        vector<f64> values;
        while (getline(ss, value, ',')) {
            values.push_back(stod(value));
        }
        return values;
    }

    auto Dataset::readStrValues(string const& line) -> vector<string> {
        stringstream ss(line);
        string value;
        vector<string> values;
        while (getline(ss, value, ',')) {
            values.push_back(value);
        }
        return values;
    }

    auto Dataset::readOptions(string const& line) -> set<string> {
        stringstream ss(line);
        string option;
        set<string> options;
        while (getline(ss, option, ',')) {
            options.insert(option);
        }
        return options;
    }
}