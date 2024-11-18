#include "YukiTools.h"

namespace yuki {
    auto equalsZero(Real const& val) -> bool {
        return abs(val) < ACCURACY;
    }

    auto equalsZero(i32 const& val) -> bool {
        return val == 0;
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