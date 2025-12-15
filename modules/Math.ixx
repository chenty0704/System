module;

#include <System/Macros.h>

export module System.Math;

import System.Base;

using namespace std;

#define EXPORT_SCALAR_VECTOR_OPERATOR(op) \
    export template<typename T, typename Range> \
        requires is_arithmetic_v<T> && ranges::contiguous_range<Range> && ranges::sized_range<Range> \
    [[nodiscard]] auto CONCAT(operator, op)(T scalar, const Range &values) { \
        using Result = decltype(T() op ranges::range_value_t<Range>()); \
        vector<Result> out(ranges::size(values)); \
        for (auto i = 0; i < ranges::size(values); ++i) out[i] = scalar op values[i]; \
        return out; \
    }

#define EXPORT_VECTOR_SCALAR_OPERATOR(op) \
    export template<typename Range, typename T> \
        requires ranges::contiguous_range<Range> && ranges::sized_range<Range> && is_arithmetic_v<T> \
    [[nodiscard]] auto CONCAT(operator, op)(const Range &values, T scalar) { \
        using Result = decltype(ranges::range_value_t<Range>() op T()); \
        vector<Result> out(ranges::size(values)); \
        for (auto i = 0; i < ranges::size(values); ++i) out[i] = values[i] op scalar; \
        return out; \
    }

#define EXPORT_VECTOR_SCALAR_ASSIGNMENT_OPERATOR(op) \
    export template<typename Range, typename T> \
        requires ranges::contiguous_range<Range> && ranges::sized_range<Range> && is_arithmetic_v<T> \
    Range &CONCAT(operator, op, =)(Range &values, T scalar) { \
        for (auto &value : values) value CONCAT(op, =) scalar; \
        return values; \
    }

#define EXPORT_VECTOR_VECTOR_OPERATOR(op) \
    export template<typename Range1, typename Range2> \
        requires ranges::contiguous_range<Range1> && ranges::sized_range<Range1> \
        && ranges::contiguous_range<Range2> && ranges::sized_range<Range2> \
    [[nodiscard]] auto CONCAT(operator, op)(const Range1 &values1, const Range2 &values2) { \
        using Result = decltype(ranges::range_value_t<Range1>() op ranges::range_value_t<Range2>()); \
        vector<Result> out(ranges::size(values1)); \
        for (auto i = 0; i < ranges::size(values1); ++i) out[i] = values1[i] op values2[i]; \
        return out; \
    }

#define EXPORT_VECTOR_VECTOR_ASSIGNMENT_OPERATOR(op) \
    export template<typename Range1, typename Range2> \
        requires ranges::contiguous_range<Range1> && ranges::sized_range<Range1> \
        && ranges::contiguous_range<Range2> && ranges::sized_range<Range2> \
    Range1 &CONCAT(operator, op, =)(Range1 &values1, const Range2 &values2) { \
        for (auto i = 0; i < ranges::size(values1); ++i) values1[i] CONCAT(op, =) values2[i]; \
        return values1; \
    }

EXPORT_SCALAR_VECTOR_OPERATOR(+)
EXPORT_SCALAR_VECTOR_OPERATOR(-)
EXPORT_SCALAR_VECTOR_OPERATOR(*)
EXPORT_SCALAR_VECTOR_OPERATOR(/)

EXPORT_VECTOR_SCALAR_OPERATOR(+)
EXPORT_VECTOR_SCALAR_OPERATOR(-)
EXPORT_VECTOR_SCALAR_OPERATOR(*)
EXPORT_VECTOR_SCALAR_OPERATOR(/)

EXPORT_VECTOR_SCALAR_ASSIGNMENT_OPERATOR(+)
EXPORT_VECTOR_SCALAR_ASSIGNMENT_OPERATOR(-)
EXPORT_VECTOR_SCALAR_ASSIGNMENT_OPERATOR(*)
EXPORT_VECTOR_SCALAR_ASSIGNMENT_OPERATOR(/)

EXPORT_VECTOR_VECTOR_OPERATOR(+)
EXPORT_VECTOR_VECTOR_OPERATOR(-)
EXPORT_VECTOR_VECTOR_OPERATOR(*)
EXPORT_VECTOR_VECTOR_OPERATOR(/)

EXPORT_VECTOR_VECTOR_ASSIGNMENT_OPERATOR(+)
EXPORT_VECTOR_VECTOR_ASSIGNMENT_OPERATOR(-)
EXPORT_VECTOR_VECTOR_ASSIGNMENT_OPERATOR(*)
EXPORT_VECTOR_VECTOR_ASSIGNMENT_OPERATOR(/)

/// Provides common math functions.
namespace Math {
    /// Returns the integer closest to a value.
    /// @param value A value to round.
    /// @returns The integer closes to the value.
    export [[nodiscard]] int Round(double value) {
        return lround(value);
    }

    /// Rounds a value to the nearest multiple of a base value.
    /// @param value A value to round.
    /// @param base A base value.
    /// @returns The nearest multiple of the base value.
    export [[nodiscard]] double Round(double value, double base) {
        return round(value / base) * base;
    }

    /// Returns the greatest integer less than or equal to a value.
    /// @param value A value to round down.
    /// @returns The greatest integer less than or equal to the value.
    export [[nodiscard]] int Floor(double value) {
        return static_cast<int>(floor(value));
    }

    /// Rounds a value down to the nearest multiple of a base value.
    /// @param value A value to round down.
    /// @param base A base value.
    /// @returns The greatest multiple of the base value less than or equal to the value.
    export [[nodiscard]] double Floor(double value, double base) {
        return floor(value / base) * base;
    }

    /// Returns the least integer greater than or equal to a value.
    /// @param value A value to round up.
    /// @returns The least integer greater than or equal to the value.
    export [[nodiscard]] int Ceiling(double value) {
        return static_cast<int>(ceil(value));
    }

    /// Rounds a value up to the nearest multiple of a base value.
    /// @param value A value to round up.
    /// @param base A base value.
    /// @returns The least multiple of the base value greater than or equal to the value.
    export [[nodiscard]] double Ceiling(double value, double base) {
        return ceil(value / base) * base;
    }

    /// Returns the absolute value.
    /// @tparam T The type of the value.
    /// @param value A value.
    /// @returns The absolute value.
    export template<typename T>
    [[nodiscard]] T Abs(T value) {
        return abs(value);
    }

    /// Returns the absolute values.
    /// @tparam Range The type of the list.
    /// @param values A list of values.
    /// @returns The absolute values.
    export template<typename Range> requires ranges::contiguous_range<Range> && ranges::sized_range<Range>
    [[nodiscard]] vector<ranges::range_value_t<Range>> Abs(const Range &values) {
        return values | views::transform([](auto value) { return Abs(value); }) | ranges::to<vector>();
    }

    /// Returns the square of a value.
    /// @param value A value to square.
    /// @returns The square of the value.
    export [[nodiscard]] double Square(double value) {
        return value * value;
    }

    /// Returns the squares of a list of values.
    /// @param values A list of values.
    /// @returns The squares of the list of values.
    export [[nodiscard]] vector<double> Square(span<const double> values) {
        return values * values;
    }

    /// Returns the power of a value.
    /// @param value A value to be raised.
    /// @param exponent The exponent.
    /// @returns The power of the value.
    export [[nodiscard]] double Pow(double value, double exponent) {
        return pow(value, exponent);
    }

    /// Returns the powers of a list of values.
    /// @param values A list of values.
    /// @param exponent The exponent.
    /// @returns The powers of the list of values.
    export [[nodiscard]] vector<double> Pow(span<const double> values, double exponent) {
        return values | views::transform([&](double value) { return Pow(value, exponent); }) | ranges::to<vector>();
    }

    /// Returns the square root of a value.
    /// @param value A value to find square root of.
    /// @returns The square root of the value.
    export [[nodiscard]] double Sqrt(double value) {
        return sqrt(value);
    }

    /// Returns the square roots of a list of values.
    /// @param values A list of values.
    /// @returns The square roots of the list of values.
    export [[nodiscard]] vector<double> Sqrt(span<const double> values) {
        return values | views::transform([&](double value) { return Sqrt(value); }) | ranges::to<vector>();
    }

    /// Returns the exponential of a value.
    /// @param value A value to find exponential of.
    /// @returns The exponential of the value.
    export [[nodiscard]] double Exp(double value) {
        return exp(value);
    }

    /// Returns the exponentials of a list of values.
    /// @param values A list of values.
    /// @returns The exponentials of the list of values.
    export [[nodiscard]] vector<double> Exp(span<const double> values) {
        return values | views::transform([](double value) { return Exp(value); }) | ranges::to<vector>();
    }

    /// Returns the natural logarithm of a value.
    /// @param value A value to find logarithm of.
    /// @returns The natural logarithm of the value.
    export [[nodiscard]] double Log(double value) {
        return log(value);
    }

    /// Returns the natural logarithms of a list of values.
    /// @param values A list of values.
    /// @returns The natural logarithms of the list of values.
    export [[nodiscard]] vector<double> Log(span<const double> values) {
        return values | views::transform([](double value) { return Log(value); }) | ranges::to<vector>();
    }

    /// Returns the total of a list of values.
    /// @tparam Range The type of the list.
    /// @param values A list of values.
    /// @returns The total of the list of values.
    export template<typename Range> requires ranges::contiguous_range<Range> && ranges::sized_range<Range>
    [[nodiscard]] ranges::range_value_t<Range> Total(const Range &values) {
        return reduce(ranges::cbegin(values), ranges::cend(values));
    }

    /// Returns the dot product between the two lists of values.
    /// @tparam Range The type of the lists.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @returns The dot product between the two lists of values.
    export template<typename Range> requires ranges::contiguous_range<Range> && ranges::sized_range<Range>
    [[nodiscard]] ranges::range_value_t<Range> Dot(const Range &values1, const Range &values2) {
        using T = ranges::range_value_t<Range>;
        return transform_reduce(ranges::cbegin(values1), ranges::cend(values1), ranges::cbegin(values2), T());
    }

    /// Returns the mean of a list of values.
    /// @param values A list of values.
    /// @returns The mean of the list of values.
    export [[nodiscard]] double Mean(span<const double> values) {
        return Total(values) / static_cast<double>(values.size());
    }

    /// Returns the variance of a list of values with known mean.
    /// @param values A list of values.
    /// @param mean The mean of the list of values.
    /// @returns The variance of the list of values.
    export [[nodiscard]] double Variance(span<const double> values, double mean) {
        auto buffer = values - mean;
        buffer *= buffer;
        return Total(buffer) / static_cast<double>(values.size() - 1);
    }

    /// Returns the variance of a list of values.
    /// @param values A list of values.
    /// @returns The variance of the list of values.
    export [[nodiscard]] double Variance(span<const double> values) {
        return Variance(values, Mean(values));
    }

    /// Returns the covariance between two lists of values with known means.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @param mean1 The mean of the first list of values.
    /// @param mean2 The mean of the second list of values.
    /// @returns The covariance between the two lists of values
    export [[nodiscard]] double Covariance(span<const double> values1, span<const double> values2,
                                           double mean1, double mean2) {
        return Dot(values1 - mean1, values2 - mean2) / static_cast<double>(values1.size() - 1);
    }

    /// Returns the covariance between two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @returns The covariance between the two lists of values.
    export [[nodiscard]] double Covariance(span<const double> values1, span<const double> values2) {
        return Covariance(values1, values2, Mean(values1), Mean(values2));
    }
}
