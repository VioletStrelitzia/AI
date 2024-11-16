#pragma once
#include <iostream>

#include <array>
#include <vector>
#include <list>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <complex>

#include <random>

#include <initializer_list>
#include <functional>
#include <concepts>

namespace yuki {
	using std::cin;
	using std::cout;
	using std::endl;

	using std::array;
	using std::vector;
	using std::list;
	using std::next;
	using std::pair;
	using std::set;
	using std::map;
	using std::unordered_map;
	using std::queue;
	using std::priority_queue;
	using std::stack;
	using std::string;

	using std::initializer_list;
	using std::function;
	using std::remove_if;
	using std::derived_from;

	using std::random_device;
	using std::mt19937;
	using std::uniform_int_distribution;

	using i16 = short;
	using i32 = int;
	using i64 = long long;

	using u16 = unsigned short;
	using u32 = unsigned int;
	using u64 = unsigned long long;

	using f16 = float;
	using f32 = double;
	using f64 = long double;

	using isize = long long;
	using usize = unsigned long long;

    using SizeType = i32;
    using Real = f32;
    using Complex = std::complex<f32>;
    using std::sort;
    using std::abs;
	using std::max;

    #define ACCURACY 1.e-7

	// 比较 是否小于
	template<class ElemType> struct less;

	// 比较 是否大于
	template<class ElemType> struct greater;

    auto equalsZero(Real const& val) -> bool {
        return abs(val) < ACCURACY;
    }

    auto equalsZero(int const& val) -> bool {
        return val == 0;
    }

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

	template <typename ElemType>
	string toString(ElemType x) {
		return "unknown";
	}

	template <>
	string toString<i32>(i32 x) {
		if (x == 0) {
			return "0";
		}
		vector<i32> nums;
		string dst;
		while (x) {
			nums.push_back(x % 10);
			x /= 10;
		}
		for (i32 i = (i32)nums.size() - 1; i > -1; --i) {
			dst.push_back('0' + nums[i]);
		}
		return dst;
	}

	template <>
	string toString<usize>(usize x) {
		if (x == 0) {
			return "0";
		}
		vector<usize> nums;
		string dst;
		while (x) {
			nums.push_back(x % 10);
			x /= 10;
		}
		for (i32 i = (i32)nums.size() - 1; i > -1; --i) {
			dst.push_back('0' + (i32)nums[i]);
		}
		return dst;
	}

	template <>
	string toString<pair<usize, i32>>(pair<usize, i32> x) {
		return "<" + toString(x.first) + ", " + toString(x.second) + ">";
	}
}