#include "YukiTools.h"

namespace yuki {
	auto entropy(vector<f64> const& P) -> f64 {
		f64 H = 0.;
		for (f64 const& p: P) {
			if (p == 0.) {
				continue;
			}
			H -= p * log2(p);
		}
		return H;
	}

	auto entropyBinary(f64 const& p) -> f64 {
		if (p == 0. || p == 1.) return 0;
		f64 _p = 1. - p;
		return -(p * log2(p) + _p * log2(_p));
	}

	auto gini(vector<f64> const& P) -> f64 {
		f64 G = 1.;
		for (f64 const& p: P) {
			G -= p * p;
		}
		return G;
	}

	auto distance(vector<f64> const& v1, vector<f64> const& v2) -> f64 {
		f64 sum = 0.;
		for (i32 i = 0, end = (i32)v1.size(); i < end; ++i) {
			sum += pow(v1[i] - v2[i], 2);
		}
		return sqrt(sum);
	}

    auto equalsZero(Real const& val) -> bool {
        return abs(val) < ACCURACY;
    }

    auto equalsZero(i32 const& val) -> bool {
        return val == 0;
    }

    auto printSpacer(i32 const& number) -> void {
        for (i32 i = 0; i < number - 1; ++i) {
            cout << "|   ";
        }
		if (number) {
			cout << "|--- ";
		}
    }

	template <>
	string toString<i32>(i32 const& x) {
		return to_string(x);
	}

	template <>
	string toString<usize>(usize const& x) {
		return to_string(x);
	}

	template <>
	string toString<pair<usize, i32>>(pair<usize, i32> const& x) {
		return "<" + to_string(x.first) + ", " + to_string(x.second) + ">";
	}
}