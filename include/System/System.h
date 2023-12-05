#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <deque>
#include <execution>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <print>
#include <queue>
#include <random>
#include <ranges>
#include <span>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define MDSPAN_USE_PAREN_OPERATOR true

#include <experimental/mdarray>
#include <experimental/mdspan>

#include <boost/preprocessor.hpp>
#include <boost/math/statistics/bivariate_statistics.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

#include "System/JSON.h"
#include "System/Reflection.h"

using namespace std;
using namespace std::literals;

namespace statistics = boost::math::statistics;

using experimental::dextents;
using experimental::full_extent;
using experimental::mdarray;
using experimental::mdspan;
using experimental::submdspan;
