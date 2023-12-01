#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <deque>
#include <execution>
#include <format>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <print>
#include <queue>
#include <random>
#include <ranges>
#include <span>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define MDSPAN_USE_PAREN_OPERATOR true

#include <experimental/mdarray>
#include <experimental/mdspan>

#include <boost/math/statistics/bivariate_statistics.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

#include "System/JSON.h"
#include "System/Reflection.h"

using namespace std;
using namespace std::experimental;
using namespace std::literals;

namespace statistics = boost::math::statistics;
