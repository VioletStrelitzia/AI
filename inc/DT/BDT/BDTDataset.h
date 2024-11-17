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

        auto addValues(string const& line) -> void;

    public:
        Dataset();

        Dataset(vector<string> const& data, bool const& label);

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
    };
}