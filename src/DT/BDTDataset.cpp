#include "DTDataset.h"

namespace yuki::atri::dt {
    auto Dataset::buildExample(vector<string> const& values, bool const& hasLable) -> Example {
        return Example(values, values.back(), hasLable);
    }

    Dataset::Dataset(string const& filename) {
        ifstream inFile(filename);
        if (inFile.fail()) {
            cout << "cannot open file: " << filename << endl;
        }

        string line;
        if (getline(inFile, line)) {
            attributes = readValues(line);
            targetAttribute = attributes.back();
        }
        for (string const& attribute: attributes) {
            if (getline(inFile, line)) {
                attributesOptions[attribute] = readOptions(line);
            }
        }
        while (getline(inFile, line)) {
            vector<string> values = readValues(line);
            rawValues.push_back(values);
            examples.push_back(buildExample(values, values.size() >= targetAttribute.size()));
        }
        attributes.pop_back();
    }

    auto Dataset::getAttributeIndex(string const& attribute) -> i32 {
        for (usize i = 0; i < attributes.size(); ++i) {
            if (attributes[i] == attribute) {
                return (i32)i;
            }
        }
        return -1;
    }

    auto Dataset::getExamples(vector<Example> const& examples, string const& attribute, string const& option) -> vector<Example> {
        vector<Example> result;
        i32 attributeIndex = getAttributeIndex(attribute);
        for (Example const& example: examples) {
            if (example.data[attributeIndex] == option) {
                result.push_back(example);
            }
        }
        return result;
    }

    auto Dataset::readValues(string const& line) -> vector<string> {
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