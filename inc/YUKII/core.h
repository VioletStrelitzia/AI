/**
 * @file core.h
 * @author your name (you@domain.com)
 * @brief 核心库
 * @version 0.1
 * @date 2024-12-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <initializer_list>
#include <exception>

#include <utility>
#include <complex>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <random>

#include <functional>
#include <concepts>

#include <format>
#include <variant>
#include <ranges>

namespace yuki {
#define YUKI_DEBUG

using std::cin;
using std::cout;
using std::ostream;
using std::istream;
using std::endl;

using std::array;
using std::vector;
using std::list;
using std::set;
using std::map;
using std::unordered_map;
using std::queue;
using std::priority_queue;
using std::stack;
using std::string;
using std::initializer_list;
using std::exception;

using std::remove_if;
using std::move;
using std::next;
using std::pair;
using std::shared_ptr;
using std::unique_ptr;

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;

using std::function;
using std::derived_from;
using std::same_as;
using std::declval;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

using i16 = short;
using i32 = int;
using i64 = long long;

using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;
using f128 = long double;

using isize = long long;
using usize = unsigned long long;

using SizeType = i32;
using Real = f64;
using Complex = std::complex<f64>;
using std::sort;
using std::abs;
using std::max;
using std::min;
using std::swap;

using std::strtol;
using std::strtof;
using std::strtod;
using std::stoi;
using std::stof;
using std::stod;

using std::to_string;

using std::format;

using std::is_same_v;
using std::variant;
using std::get;

using std::less;
using std::greater;

namespace rg = std::ranges;
namespace views = std::views;

const i32 VALID_INDEX = -1;
const f64 ACCURACY = 1.e-7;
const i32 INFINITY_I32 = -1;

}