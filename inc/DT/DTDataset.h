#pragma once
#include "DTExample.h"
#include "Attribute.h"

namespace yuki::atri::dt {
/**
 * @brief 决策树数据集
 * 
 */
class Dataset {
public:
    vector<Attribute>   attributes;  ///< 特征列表
    Attribute           target;      ///< 标签的名称
    vector<vector<f64>> rawValues;   ///< 数据列表，每条数据包含所有特征和一个标签（在末尾）
    vector<Example>     examples;    ///< 把数据保存为 Example 的形式

    auto buildExample(vector<f64> const& values, bool const& hasLable = true) -> Example;

public:
    Dataset(string const& path);

    /**
     * @brief Get the Attribute Index object
     * 
     * @param attribute 
     * @return i32 
     */
    auto getAttributeIndex(string const& attribute) -> i32;

    /**
     * @brief Get the Examples object
     * 
     * @param examples 
     * @param attribute 
     * @param option 
     * @return vector<Example> 
     */
    auto getExamples(vector<Example> const& examples, string const& attribute, f64 const& option) -> vector<Example>;

    /**
     * @brief 
     * 
     * @param line 
     * @return vector<f64> 
     */
    auto readValues(string const& line) -> vector<f64>;

    /**
     * @brief 
     * 
     * @param line 
     * @return vector<string> 
     */
    auto readStrValues(string const& line) -> vector<string>;

    /**
     * @brief 
     * 
     * @param line 
     * @return set<string> 
     */
    auto readOptions(string const& line) -> set<string>;
};
}