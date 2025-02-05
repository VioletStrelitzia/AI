/**
 * @file YDefault.h
 * @author your name (you@domain.com)
 * @brief 错误库
 * @version 0.1
 * @date 2024-12-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include "Ycore.h"

namespace yuki::dflt {
/**
 * @brief 错误基类
 */
struct DefaultBase: exception {
	/**
	 * @brief 输出一个说明错误信息的字符串
	 * 
	 * @return string 错误信息
	 */
	virtual auto defaultInfo(string const& add = "") const -> string = 0;
};

/**
 * @brief 越界错误类
 */
struct OutOfRange: public DefaultBase {
	auto defaultInfo(string const& add = "") const -> string override;
};

/**
 * @brief 申请内存失败错误类
 */
struct BadAlloc: public DefaultBase {
	auto defaultInfo(string const& add = "") const -> string override;
};

/**
 * @brief 除0错误类
 */
struct DivideByZero: public DefaultBase {
	auto defaultInfo(string const& add = "") const -> string override;
};

/**
 * @brief 无效的枚举类型错误类
 */
struct UnexpectedEnumParameter: public DefaultBase {
	auto defaultInfo(string const& add = "") const -> string override;
};

/**
 * @brief 加载（资源等）错误类
 */
struct LoadFailed: public DefaultBase {
	auto defaultInfo(string const& add = "") const -> string override;
};

/**
 * @brief 加载（资源等）错误类
 */
struct SaveFailed: public DefaultBase {
	auto defaultInfo(string const& add = "") const -> string override;
};

/**
* @brief 矩阵计算中行列不对应错误类
*/
struct DimensionMismatch: public DefaultBase {
	auto defaultInfo(string const& add = "") const -> string override;
};
}
