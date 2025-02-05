#include "Ycore.h"

namespace yuki {

using NoTargetType = void;

/**
 * @brief 样本类
 * 
 * @tparam Data data 数据类型 
 * @tparam Target target 数据类型
 */
template <typename Data, typename Target>
struct Example {
    using DataType = Data;
    using TargetType = Target;

    Data data;  ///< 数据
    Target target;  ///< 目标
    
    Example() = default;
    Example(Data const& data, Target const& target):
        data(data), target(target) {}
    ~Example() = default;
};

/**
 * @brief 偏特化的样本类型，不包括 target
 * 
 * @tparam DataType data 数据类型
 */
template <typename Data>
struct Example<Data, NoTargetType> {
    using DataType = Data;

    Data data;  ///< 数据

    Example() = default;
    Example(Data const& data):
        data(data) {}
    ~Example() = default;

    operator Data&() {
        return data;
    }

    operator const Data&() const {
        return data;
    }
};

}