#pragma once
#include "core.h"

namespace yuki {
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

	template <typename ElemType>
	string toString(ElemType x) {
		return "unknown";
	}

	template <>
	string toString<i32>(i32 x);

	template <>
	string toString<usize>(usize x);

	template <>
	string toString<pair<usize, i32>>(pair<usize, i32> x);

    auto printSpacer(i32 const& number) -> void {
        for (i32 i = 0; i < number; ++i) {
            cout << '\t';
        }
    }
}