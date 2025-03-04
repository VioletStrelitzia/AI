#include "tools.h"

namespace yuki::random {
random_device GLOBAL_RD;
mt19937 GLOBAL_MT19937(GLOBAL_RD());

auto reflash() -> void {
	GLOBAL_MT19937 = mt19937(GLOBAL_RD());
}
auto chooseByProbability(vector<f64> const& P, f64 const& sum) -> i32 {
    f64 cumulativeProbability = 0.0, randomValue = uniformReal(0., sum);
	i32 i = 0;
	for (f64 const& p: P) {
		cumulativeProbability += p;
        if (cumulativeProbability > randomValue) {
            return i;
        }
		++i;
	}
	return i;
}

auto chooseByWeights(vector<f64> const& weights) -> i32 {
	f64 sum = 0.;
	for (f64 const& w: weights) {
		sum += w;
	}

    f64 cumulativeWeights = 0.0, randomValue = uniformReal(0., sum);
	i32 i = 0;
	for (f64 const& w: weights) {
		cumulativeWeights += w;
        if (cumulativeWeights > randomValue) {
            return i;
        }
		++i;
	}
	return i;
}

auto chooseByWeights(vector<f64> const& weights, f64 const& sum) -> i32 {
    f64 cumulativeWeights = 0.0, randomValue = uniformReal(0., sum);
	
	i32 i = 0;
	for (f64 const& w: weights) {
		cumulativeWeights += w;
        if (cumulativeWeights > randomValue) {
            return i;
        }
		++i;
	}
	return i;
}

auto trigger(f64 const& p) -> bool {
	return uniformReal(0., 1.) < p;
}
}

namespace yuki::statistics {
auto varianceTwoPass(vector<f64> const& data) -> f64 {
	f64 mean = 0.,
			s = 0.,
			n = static_cast<f64>(data.size());
	
	for (f64 const& x: data) {
		mean += x;
	}
	mean /= n;
	for (f64 const& x: data) {
		s += pow(x - mean, 2);
	}
	return s / n;
}

auto varianceOnePass(vector<f64> const& data) -> f64 {
	f64 mean = 0.,
			s = 0.,
			n = static_cast<f64>(data.size());
	
	for (f64 const& x: data) {
		mean += x;
		s += x * x;
	}
	mean /= n;
	return s / n - mean * mean;
}

auto variance(vector<f64> const& data) -> f64 {
	f64 prevMean = 0.,
			curMean = 0.,
				s = 0.;
	usize      n = data.size();

	for (usize i = 0; i < n; ++i) {
		prevMean = curMean;
		curMean += (data[i] - curMean) / (i + 1);
		s += (data[i] - curMean) * (data[i] - prevMean);
	}

	return s / static_cast<f64>(n);
}

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
}

namespace yuki {
auto distanceEuclidean(vector<f64> const& v1, vector<f64> const& v2) -> f64 {
	#ifdef YUKI_DEBUG
	if (v1.size() != v2.size()) {
		throw dflt::DimensionMismatch();
	}
	#endif
	f64 sum = 0.;
	for (i32 i = (i32)v1.size() - 1; i > -1; --i) {
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

auto StringcodeToInt(string const& word) -> int {
	int dst = 0;
	for (int i = 0; i < word.size(); ++i) {
		dst += static_cast<unsigned>(word[i]) << (i << 3);
	}
	return dst;
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
string toString<char>(char const& x) {
	return to_string(x);
}

template <>
string toString<pair<usize, i32>>(pair<usize, i32> const& x) {
	return "<" + to_string(x.first) + ", " + to_string(x.second) + ">";
}

template <>
string toString<pair<i32, i32>>(pair<i32, i32> const& x) {
	return "<" + to_string(x.first) + ", " + to_string(x.second) + ">";
}
}