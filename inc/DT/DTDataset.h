#pragma once
#include "DTExample.h"

namespace yuki::atri::dt {
    class Dataset {
    public:
        vector<string>           attributes;       // 特征列表
        string                   targetAttribute;  // 标签的名称
        vector<vector<string>>   rawValues;        // 数据列表，每条数据包含所有特征和一个标签（在末尾）
        vector<Example>          examples;         // 把数据保存为 Example 的形式
        map<string, set<string>> attributesOptions;

        auto buildExample(vector<string> const& values, bool const& hasLable = true) -> Example;

    public:
        Dataset(string const& filename);

        auto getAttributeIndex(string const& attribute) -> i32;

        auto getExamples(vector<Example> const& examples, string const& attribute, string const& option) -> vector<Example>;

        auto readValues(string const& line) -> vector<string>;

        auto readOptions(string const& line) -> set<string>;
    };
}