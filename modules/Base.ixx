export module System.Base;

#define _BUILD_STD_MODULE // NOLINT(bugprone-reserved-identifier)

#pragma warning(disable: 5244)

// ReSharper disable CppUnusedIncludeDirective
#include <algorithm>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <cmath>
#include <codecvt>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <coroutine>
#include <deque>
#include <exception>
#include <execution>
#include <expected>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <print>
#include <queue>
#include <random>
#include <ranges>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <spanstream>
#include <sstream>
#include <stack>
#include <stacktrace>
#include <stdexcept>
#include <stdfloat>
#include <stop_token>
#include <streambuf>
#include <string>
#include <string_view>
#include <strstream>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

using namespace std;
using namespace literals;

export {
    using ::int8_t;
    using ::int16_t;
    using ::int32_t;
    using ::int64_t;
}

/// Measures the execution time of a function.
/// @tparam Fun The type of the function.
/// @param fun A function to measure the execution time of.
/// @returns The execution time of the function.
export template<invocable Fun>
chrono::duration<double> MeasureTime(Fun fun) {
    const auto beginTime = chrono::high_resolution_clock::now();
    fun();
    const auto endTime = chrono::high_resolution_clock::now();
    return endTime - beginTime;
}

/// Measures the execution time of a function and returns its value.
/// @tparam Fun The type of the function.
/// @param fun A function to measure the execution time of.
/// @returns The return value of the function with the execution time.
export template<invocable Fun>
pair<invoke_result_t<Fun>, chrono::duration<double>> MeasureTimedValue(Fun fun) {
    const auto beginTime = chrono::high_resolution_clock::now();
    const auto value = fun();
    const auto endTime = chrono::high_resolution_clock::now();
    return {value, endTime - beginTime};
}
