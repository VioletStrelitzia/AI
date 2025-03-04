/**
 * @file tools.h
 * @brief 工具库
 * @details 封装了各种工具类和工具函数
 * @author your name (you@domain.com)
 * @version 0.1
 * @date 2024-12-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include "Default.h"

/**
 * @brief 随机库
 * 
 */
namespace yuki::random {

extern random_device GLOBAL_RD;
extern mt19937 GLOBAL_MT19937;

/**
 * @brief 刷新gen
 * 
 */
auto reflash() -> void;

/**
 * @brief 生成服从均匀分布的浮点数生成器
 * 
 * @tparam ElemType 浮点类型
 * @param left 左端点
 * @param right 右端点
 * @return uniform_real_distribution<ElemType> 
 * @retval 服从均匀分布的浮点数生成器
 */
template <typename ElemType = f64>
auto uniformRealDis(ElemType const& left, ElemType const& right) -> uniform_real_distribution<ElemType>;

/**
 * @brief 生成服从均匀分布的整型数生成器
 * 
 * @tparam ElemType 整型类型
 * @param left 左端点
 * @param right 右端点
 * @return uniform_int_distribution<ElemType> 
 */
template <typename ElemType = i32>
auto uniformIntDis(ElemType const& left, ElemType const& right) -> uniform_int_distribution<ElemType>;

/**
 * @brief 生成一个随机浮点数
 * 
 * @tparam ElemType 浮点类型
 * @param dis 浮点数服从的分布
 * @return ElemType
 */
template <typename ElemType = f64>
auto uniformReal(uniform_real_distribution<ElemType> const& dis) -> ElemType;

/**
 * @brief 生成一个随机整型数
 * 
 * @tparam ElemType 整型类型
 * @param dis 整型数服从的分布
 * @return ElemType 
 */
template <typename ElemType = i32>
auto uniformInt(uniform_int_distribution<ElemType> const& dis) -> ElemType;

/**
 * @brief 生成一个随机浮点数
 * 
 * @tparam ElemType 浮点类型
 * @param left 左端点
 * @param right 右端点
 * @return ElemType 
 */
template <typename ElemType = f64>
auto uniformReal(ElemType const& left, ElemType const& right) -> ElemType;

/**
 * @brief 生成一个随机整型数
 * 
 * @tparam ElemType 整型类型
 * @param left 左端点
 * @param right 右端点
 * @return ElemType 
 */
template <typename ElemType = i32>
auto uniformInt(ElemType const& left, ElemType const& right) -> ElemType;

/**
 * @brief 从数组里随机选择一个元素
 * 
 * @tparam ElemType 数组元素类型
 * @param vec 数组
 * @return ElemType 
 */
template <typename ElemType, FunctionReturnType Type = FunctionReturnType::VALUE>
auto choose(vector<ElemType>& vec) -> FuncRetType<ElemType, Type>;

/**
 * @brief 依概率选择
 * 
 * @param P 概率分布
 * @param sum 概率和
 * @return i32 选择的下标
 */
auto chooseByProbability(vector<f64> const& P, f64 const& sum = 1.) -> i32;

/**
 * @brief 依权重选择
 * 
 * @param weights 权重分布
 * @return i32 选择的下标
 */
auto chooseByWeights(vector<f64> const& weights) -> i32;

/**
 * @brief 依权重选择
 * 
 * @param weights 权重分布
 * @param sum 权重和
 * @return i32 选择的下标
 */
auto chooseByWeights(vector<f64> const& weights, f64 const& sum) -> i32;

/**
 * @brief 依概率 p 随机选择是否触发
 * 
 * @param p 触发概率，范围 [0, 1]
 * @return true 触发
 * @return false 不触发
 */
auto trigger(f64 const& p) -> bool;

};

/**
 * @brief 统计库
 * 
 */
namespace yuki::statistics {

/**
 * @brief 和
 * 
 * @tparam ElemType 数据类型
 * @param data 数据
 * @return ElemType 数据类型
 */
template <typename ElemType>
auto sum(vector<ElemType> const& data) -> ElemType {
	ElemType sum = data.front();
	for (i32 i = 1; i < data.size(); ++i) {
		sum += data[i];
	}
	return sum;
}

/**
 * @brief 连乘积
 * 
 * @tparam ElemType 数据类型
 * @param data 数据
 * @return ElemType 数据类型
 */
template <typename ElemType>
auto product(vector<ElemType> const& data) -> ElemType {
	ElemType sum = data.front();
	for (i32 i = 1; i < data.size(); ++i) {
		sum *= data[i];
	}
	return sum;
}

/// @brief 计算方差（朴素方法）
/// @param data 数据
/// @return 方差
auto varianceTwoPass(vector<f64> const& data) -> f64;

/// @brief 计算方差（一趟法，数值误差大）
/// @param data 数据
/// @return 方差
auto varianceOnePass(vector<f64> const& data) -> f64;

/// @brief 计算方差（Welford迭代法）
/// @param data 数据
/// @return 方差
auto variance(vector<f64> const& data) -> f64;

/// @brief 求中位元素（递归）
/// @tparam ElemType 元素类型
/// @param data 数据
/// @param left 左端点
/// @param right 右端点
/// @param mid 中点下标
/// @param comper 比较器
/// @return 中位元素
template <typename ElemType>
auto median(vector<ElemType>& data, usize const& left, usize const& right, usize const& mid,
	function<bool(ElemType const&, ElemType const&)> const& comper = greater<ElemType>()) -> ElemType;

/// @brief 求中位元素（迭代）
/// @tparam ElemType 元素类型
/// @param data 数据
/// @param left 左端点
/// @param right 右端点
/// @param comper 比较器
/// @return 中位元素
template <typename ElemType>
auto median(vector<ElemType>& data, usize left, usize right,
	function<bool(ElemType const&, ElemType const&)> const& comper = greater<ElemType>()) -> ElemType;

/// @brief 求中位元素
/// @tparam ElemType 元素类型
/// @param data 数据
/// @param comper 比较器
/// @return 中位元素
template <typename ElemType>
auto median(vector<ElemType> data,
	function<bool(ElemType const&, ElemType const&)> const& comper = greater<ElemType>()) -> ElemType;

template <typename ElemType>
auto topK(vector<ElemType>& data, usize left, usize right, usize const& k,
	function<bool(ElemType const&, ElemType const&)> const& comper = greater<ElemType>()) -> ElemType;

template <typename ElemType>
auto topK(vector<ElemType> data, usize const& k,
	function<bool(ElemType const&, ElemType const&)> const& comper = greater<ElemType>()) -> ElemType;

/// @brief 计算随机变量的信息熵
/// @param P 该变量所有取值的概率集合
/// @return 信息熵
auto entropy(vector<f64> const& P) -> f64;

/**
 * @brief 计算随机变量的信息熵
 * 
 * @tparam T map 的键类型
 * @param PMap 该变量所有取值的概率集合
 * @return f64 随机变量的信息熵
 */
template <typename T>
auto entropy(unordered_map<T, f64> const& PMap) -> f64;

/// @brief 计算布尔随机变量的信息熵
/// @param p 该变量取 1 的概率（0 也可）
/// @return 信息熵
auto entropyBinary(f64 const& p) -> f64;

/// @brief 计算基尼指数
/// @param P 所有取值的概率集合
/// @return 基尼指数
auto gini(vector<f64> const& P) -> f64;

/**
 * @brief 计算基尼指数
 * 
 * @tparam T map 的键类型
 * @param PMap 所有取值的概率集合
 * @param n 
 * @return f64 
 */
template <typename T>
auto gini(unordered_map<T, f64> const& PMap, f64 const& n = 1) -> f64;

template <typename T>
auto gini(unordered_map<T, pair<f64, f64>> const& PMap, f64 const& n = 1) -> pair<f64, f64>;
}

namespace yuki {

/**
 * @brief 计算两个向量的欧几里得距离
 * 
 * @param v1 向量1
 * @param v2 向量2
 * @return f64 两个向量的欧几里得距离
 */
auto distanceEuclidean(vector<f64> const& v1, vector<f64> const& v2) -> f64;

/**
 * @brief 检查一个数是否等于 0
 * @details 主要用于应对浮点数精度的问题
 * 
 * @param val 数
 * @return 该数是否等于 0
 * @retval true 该数等于 0
 * @retval false 该数不等于 0
 */
auto equalsZero(Real const& val) -> bool;

/**
 * @brief 检查一个数是否等于 0
 * 
 * @param val 数
 * @return 该数是否等于 0
 * @retval true 该数等于 0
 * @retval false 该数不等于 0
 */
auto equalsZero(i32 const& val) -> bool;

/**
 * @brief 打印制表填充
 * 
 * @param number 制表符个数
 */
auto printSpacer(i32 const& number) -> void;

/**
 * @brief 单个字符转 int
 * 
 * @param word 单个字符
 * @return int 
 */
auto StringcodeToInt(string const& word) -> int;

/**
 * @brief 将一个变量转换成字符串
 * @details 用于输出
 * 
 * @tparam ElemType 变量类型
 * @param x 变量
 * @return string 转换成的字符串
 */
template <typename ElemType>
string toString(ElemType const& x) {
	return "unknown";
}

template <>
string toString<i32>(i32 const& x);

template <>
string toString<usize>(usize const& x);

template <>
string toString<char>(char const& x);

template <>
string toString<pair<usize, i32>>(pair<usize, i32> const& x);

template <>
string toString<pair<i32, i32>>(pair<i32, i32> const& x);

template <typename T>
auto operator << (ostream& os, vector<T> const& v) -> ostream&;
}

namespace yuki::random {
template <typename ElemType>
auto uniformRealDis(ElemType const& left, ElemType const& right) -> uniform_real_distribution<ElemType> {
	return uniform_real_distribution<ElemType>(left, right);
}

template <typename ElemType>
auto uniformIntDis(ElemType const& left, ElemType const& right) -> uniform_int_distribution<ElemType> {
	return uniform_int_distribution<ElemType>(left, right);
}

template <typename ElemType>
auto uniformReal(uniform_real_distribution<ElemType> const& dis) -> ElemType {
	return dis(GLOBAL_MT19937);
}

template <typename ElemType>
auto uniformInt(uniform_int_distribution<ElemType> const& dis) -> ElemType {
	return dis(GLOBAL_MT19937);
}

template <typename ElemType>
auto uniformReal(ElemType const& left, ElemType const& right) -> ElemType {
	uniform_real_distribution<ElemType> dis(left, right);
	return dis(GLOBAL_MT19937);
}

template <typename ElemType>
auto uniformInt(ElemType const& left, ElemType const& right) -> ElemType {
	uniform_int_distribution<ElemType> dis(left, right);
	return dis(GLOBAL_MT19937);
}

template <typename ElemType, FunctionReturnType Type>
auto choose(vector<ElemType>& vec) -> FuncRetType<ElemType, Type> {
	if (vec.size() == 1) {
		return vec[0];
	}
	return vec[uniform_int_distribution<usize>(0, vec.size() - 1)(GLOBAL_MT19937)];
}

}
namespace yuki::statistics {
template <typename ElemType>
auto median(vector<ElemType>& data, usize const& left, usize const& right, usize const& mid,
	function<bool(ElemType const&, ElemType const&)> const& comper) -> ElemType {
	usize i = left + 1, j = right, p = left;
	swap(data[left], data[random::uniformInt<usize>(left, right)]);
	while (true) {
		while (i < right && comper(data[p], data[i])) ++i;
		while (j > left && !comper(data[p], data[j])) --j;
		if (i < j) {
			swap(data[i], data[j]);
		} else {
			break;
		}
	}
	if (j == mid) {
		return data[p];
	}
	swap(data[j], data[p]);
	if (j < mid) {
		return median(data, i, right, mid, comper);
	}
	return median(data, left, j, mid, comper);
}

template <typename ElemType>
auto median(vector<ElemType>& data, usize left, usize right,
	function<bool(ElemType const&, ElemType const&)> const& comper) -> ElemType {
	usize i, j, p, mid = (left + right + 1) >> 1;
	while (true) {
		i = left + 1, j = right, p = left;
		swap(data[left], data[random::uniformInt<usize>(left, right)]);
		while (true) {
			while (i < right && comper(data[p], data[i])) ++i;
			while (j > left && !comper(data[p], data[j])) --j;
			if (i < j) {
				swap(data[i], data[j]);
			} else {
				break;
			}
		}
		if (j == mid) {
			swap(data[j], data[p]);
			cout << data<< endl;
			return data[j];                
		}
		swap(data[j], data[p]);
		if (j < mid) {
			left = i;
		} else {
			right = j;
		}
	}
}

template <typename ElemType>
auto median(vector<ElemType> data, function<bool(ElemType const&, ElemType const&)> const& comper) -> ElemType {
	return median(data, 0, data.size() - 1, comper);
}

template <typename ElemType>
auto topK(vector<ElemType>& data, usize left, usize right, usize const& k,
	function<bool(ElemType const&, ElemType const&)> const& comper) -> ElemType {
		cout << k << endl;
	usize i, j, p;
	while (true) {
		i = left + 1, j = right, p = left;
		swap(data[left], data[random::uniformInt<usize>(left, right)]);
		while (true) {
			while (i < right && comper(data[p], data[i])) ++i;
			while (j > left && !comper(data[p], data[j])) --j;
			if (i < j) {
				swap(data[i], data[j]);
			} else {
				break;
			}
		}
		if (j == k) {
			return data[p];                
		}
		swap(data[j], data[p]);
		if (j < k) {
			left = i;
		} else {
			right = j;
		}
	}
}

template <typename ElemType>
auto topK(vector<ElemType> data, usize const& k, function<bool(ElemType const&, ElemType const&)> const& comper) -> ElemType {
	return topK(data, 0, data.size() - 1, data.size() - k, comper);
}

template <typename T>
auto entropy(unordered_map<T, f64> const& PMap) -> f64 {
	f64 H = 0.;
	for (pair<T, f64> const& p: PMap) {
		if (p.second == 0.) {
			continue;
		}
		H -= p.second * log2(p.second);
	}
	return H;
}

template <typename T>
auto gini(unordered_map<T, f64> const& PMap, f64 const& n) -> f64 {
	f64 G = 1.;
	f64 n2 = n * n;
	for (pair<T, f64> const& p: PMap) {
		G -= p.second * p.second / n2;
	}
	return G;
}

template <typename T>
auto gini(unordered_map<T, pair<f64, f64>> const& PMap, f64 const& n) -> pair<f64, f64> {
	pair<f64, f64> G = { 1., 1. };
	f64 n2 = n * n;
	for (pair<T, pair<f64, f64>> const& p: PMap) {
		G.first -= p.second.first * p.second.first / n2;
		G.second -= p.second.second * p.second.second / n2;
	}
	return G;
}
};

namespace yuki {
template <typename T>
auto operator << (ostream& os, vector<T> const& v) -> ostream& {
	os << "{";
	for (T const& t: v) {
		cout << t << ", ";
	}
	os << "\b\b}";
	return os;
}
}