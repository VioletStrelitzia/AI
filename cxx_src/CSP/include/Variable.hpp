#pragma once
#include "core.h"

namespace yuki::atri::csp {
/// @brief 变量类
/// @tparam ValueType 变量的值的类型
template <typename ValueType>
class Variable {
public:
    ValueType         value;              ///< 变量当前的取值
    bool              unassigned = true;  ///< 变量是否已赋值
    vector<ValueType> domain;             ///< 变量的值域

public:
    Variable() = default;
    ~Variable() = default;

    /// @brief 给当前变量赋值
    /// @param val 变量的取值
    /// @param clearDomain 是否重置值域
    auto assign(ValueType const& val, bool const& clearDomain = true) -> void;

    /// @brief 将变量标记为未赋值
    auto setUnassigned() -> void;
};

template <typename ValueType>
auto Variable<ValueType>::assign(ValueType const& val, bool const& clearDomain) -> void {
    // 赋值
    value = val;

    // 设置未赋值标记为假
    unassigned = false;
    
    if (clearDomain) {
        // 重置值域
        domain.clear();
        domain.push_back(val);
    }
}

template <typename ValueType>
auto Variable<ValueType>::setUnassigned() -> void {
    unassigned = true;
}
}
