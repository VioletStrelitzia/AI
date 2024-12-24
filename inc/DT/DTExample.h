#pragma once
#include "Attribute.h"
#include "YUKII/data/Example.h"

namespace yuki::atri::dt {
/**
 * @brief 用于决策树的样本类
 * 
 */
class Example {
public:
    vector<f64> data;  ///< 属性数据
    f64 target;        ///< 目标属性

public:
    Example();
    
    Example(vector<f64> const& data_, f64 const& target_, bool const& isPop = false);
};

auto subExamples(Attribute const* const& attributeIndex, f64 const& value , vector<Example*> const& examples) -> vector<Example*>;

auto countTargetValue(f64 const& targetValue, vector<Example*> const& examples) -> i32;
}