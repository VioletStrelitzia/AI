#pragma once
#include "tools.h"

namespace yuki::atri::dt {
/**
 * @brief 属性类型枚举
 * 
 */
enum AttributeType {
    BASE_ATTRIBUTE = 0,  ///< 基类
    DISCRETE,            ///< 取值为离散的属性
    CONTINUOUS           ///< 取值为连续的连续属性
};

/**
 * @brief 属性类
 * 
 */
class Attribute {
public:
    static f64 const ABSENT;  ///< 缺失属性的填充标记值
    i32 index;  ///< 属性在样本 data 数组里的下标
    string name;  ///< 属性名称
    AttributeType type;  ///< 属性的类型
    set<f64> values;  ///< 属性的值域
    unordered_map<f64, string> valueStr;  ///< 属性的每个值对应的字符串
};
}
