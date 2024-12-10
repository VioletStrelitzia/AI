#pragma once
#include "core.h"

namespace yuki {
	/// @brief 计算随机变量的信息熵
	/// @param P 该变量所有取值的概率集合
	/// @return 信息熵
	auto entropy(vector<f64> const& P) -> f64;

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

	/// @brief 计算布尔随机变量的信息熵
	/// @param p 该变量取 1 的概率（0 也可）
	/// @return 信息熵
	auto entropyBinary(f64 const& p) -> f64;

	/// @brief 计算基尼指数
	/// @param P 所有取值的概率集合
	/// @return 基尼指数
	auto gini(vector<f64> const& P) -> f64;

	template <typename T>
	auto gini(unordered_map<T, f64> const& PMap, f64 const& n = 1) -> f64 {
		f64 G = 1.;
		f64 n2 = n * n;
		for (pair<T, f64> const& p: PMap) {
			G -= p.second * p.second / n2;
		}
		return G;
	}

	template <typename T>
	auto gini(unordered_map<T, pair<f64, f64>> const& PMap, f64 const& n = 1) -> pair<f64, f64> {
		pair<f64, f64> G = { 1., 1. };
		f64 n2 = n * n;
		for (pair<T, pair<f64, f64>> const& p: PMap) {
			G.first -= p.second.first * p.second.first / n2;
			G.second -= p.second.second * p.second.second / n2;
		}
		return G;
	}

	auto distance(vector<f64> const& v1, vector<f64> const& v2) -> f64;

	template <typename T>
	auto randomChoose(vector<T> const& vec) -> T {
		if (vec.size() == 1) {
			return vec[0];
		}

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<i32> dis(0, (i32)vec.size() - 1);

		return vec[dis(gen)];
	}

	// 比较 是否小于
	template<class ElemType> struct less;

	// 比较 是否大于
	template<class ElemType> struct greater;

    auto equalsZero(Real const& val) -> bool;

    auto equalsZero(i32 const& val) -> bool;

	template<class ElemType>
	struct less {
		bool operator () (const ElemType& x, const ElemType& y) {
			return x < y;
		}
	};

	// 比较 是否大于
	template<class ElemType>
	struct greater {
		bool operator () (const ElemType& x, const ElemType& y) {
			return x > y;
		}
	};

    auto printSpacer(i32 const& number) -> void;

	template <typename ElemType>
	string toString(ElemType const& x) {
		return "unknown";
	}

	template <>
	string toString<i32>(i32 const& x);

	template <>
	string toString<usize>(usize const& x);

	template <>
	string toString<pair<usize, i32>>(pair<usize, i32> const& x);

	template <typename T>
	auto operator<<(ostream& os, vector<T> const& v) -> ostream& {
		os << "{";
		for (T const& t: v) {
			cout << t << ", ";
		}
		os << "\b\b}";
		return os;
	}
}