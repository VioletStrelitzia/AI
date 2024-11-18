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
#include <fstream>
#include <sstream>

#include <iomanip>

#include <random>

#include <initializer_list>
#include <functional>
#include <concepts>

namespace yuki {
	using std::cin;
	using std::cout;
	using std::ostream;
	using std::istream;
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

	using std::shared_ptr;
	using std::unique_ptr;

	using std::ifstream;
	using std::ofstream;
	using std::stringstream;
	using std::getline;

	using std::initializer_list;
	using std::function;
	using std::remove_if;
	using std::move;
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
}