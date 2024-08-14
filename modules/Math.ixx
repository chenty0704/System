module;

#include <System/Macros.h>

export module System.Math;

import System.Base;

using namespace std;

template<typename T>
class ScaledSpan {
    span<const T> _values;
    T _scalar;

public:
    constexpr ScaledSpan(span<const T> values, T scalar) noexcept: _values(values), _scalar(scalar) {
    }

    [[nodiscard]] constexpr int size() const noexcept {
        return static_cast<int>(_values.size());
    }

    [[nodiscard]] constexpr T operator[](int index) const noexcept {
        return _values[index] * _scalar;
    }
};

#define VECTOR_TYPES (int, double)
#define VECTOR_OPERATORS (+, -, *, /)

#define SPAN_TYPE(isScaled, T) IF(NOT(isScaled), span<const T>, ScaledSpan<T>)

#define EXPORT_SCALAR_VECTOR_OPERATOR(T, op, isScaled) \
    export [[nodiscard]] vector<T> CONCAT(operator, op)(T scalar, SPAN_TYPE(isScaled, T) values) { \
        vector<T> out(values.size()); \
        for (auto i = 0; i < values.size(); ++i) out[i] = scalar op values[i]; \
        return out; \
    }

#define EXPORT_VECTOR_SCALAR_OPERATOR(T, op, isScaled) \
    export [[nodiscard]] vector<T> CONCAT(operator, op)(SPAN_TYPE(isScaled, T) values, T scalar) { \
        vector<T> out(values.size()); \
        for (auto i = 0; i < values.size(); ++i) out[i] = values[i] op scalar; \
        return out; \
    }

#define EXPORT_VECTOR_VECTOR_OPERATOR(T, op, isScaled1, isScaled2) \
    export [[nodiscard]] vector<T> CONCAT(operator, op)(SPAN_TYPE(isScaled1, T) values1, \
                                                        SPAN_TYPE(isScaled2, T) values2) { \
        vector<T> out(values1.size()); \
        for (auto i = 0; i < values1.size(); ++i) out[i] = values1[i] op values2[i]; \
        return out; \
    }

#define EXPORT_VECTOR_SCALAR_ASSIGNMENT_OPERATOR(T, op) \
    export span<T> CONCAT(operator, op, =)(span<T> values, T scalar) { \
        for (auto &value : values) value CONCAT(op, =) scalar; \
        return values; \
    }

#define EXPORT_VECTOR_VECTOR_ASSIGNMENT_OPERATOR(T, op, isScaled2) \
    export span<T> CONCAT(operator, op, =)(span<T> values1, SPAN_TYPE(isScaled2, T) values2) { \
        for (auto i = 0; i < values1.size(); ++i) values1[i] CONCAT(op, =) values2[i]; \
        return values1; \
    }

FOR_EACH(EXPORT_SCALAR_VECTOR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1))
FOR_EACH(EXPORT_VECTOR_SCALAR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1))
FOR_EACH(EXPORT_VECTOR_VECTOR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1), (0, 1))
FOR_EACH(EXPORT_VECTOR_SCALAR_ASSIGNMENT_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS)
FOR_EACH(EXPORT_VECTOR_VECTOR_ASSIGNMENT_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1))

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

    /// Returns a view of a scaled list of values.
    /// @param values A list of values.
    /// @param scalar A scalar multiplier.
    /// @returns A view of the scaled list of values.
    export [[nodiscard]] ScaledSpan<int> Scaled(span<const int> values, int scalar) {
        return {values, scalar};
    }

    /// Returns a view of a scaled list of values.
    /// @param values A list of values.
    /// @param scalar A scalar multiplier.
    /// @returns A view of the scaled list of values.
    export [[nodiscard]] ScaledSpan<double> Scaled(span<const double> values, double scalar) {
        return {values, scalar};
    }

    /// Returns the absolute value.
    /// @param value A value.
    /// @returns The absolute value.
    export [[nodiscard]] int Abs(int value) {
        return abs(value);
    }

    /// Returns the absolute value.
    /// @param value A value.
    /// @returns The absolute value.
    export [[nodiscard]] double Abs(double value) {
        return abs(value);
    }

    /// Returns the absolute values.
    /// @param values A list of values.
    /// @returns The absolute values.
    export [[nodiscard]] vector<int> Abs(span<const int> values) {
        return values | views::transform([](int value) { return Abs(value); }) | ranges::to<vector>();
    }

    /// Returns the absolute values.
    /// @param values A list of values.
    /// @returns The absolute values.
    export [[nodiscard]] vector<double> Abs(span<const double> values) {
        return values | views::transform([](double value) { return Abs(value); }) | ranges::to<vector>();
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

    /// Returns the natural logarithm of a value.
    /// @param value A value to find logarithm of.
    /// @returns The natural logarithm of a value.
    export [[nodiscard]] double Log(double value) {
        return log(value);
    }

    /// Returns the natural logarithms of a list of values.
    /// @param values A list of values.
    /// @returns The natural logarithms of a list of values.
    export [[nodiscard]] vector<double> Log(span<const double> values) {
        return values | views::transform([](double value) { return Log(value); }) | ranges::to<vector>();
    }

    /// Returns the total of a list of values.
    /// @param values A list of values.
    /// @returns The total of the list of values.
    export [[nodiscard]] int Total(span<const int> values) {
        return reduce(values.cbegin(), values.cend());
    }

    /// Returns the total of a list of values.
    /// @param values A list of values.
    /// @returns The total of the list of values.
    export [[nodiscard]] double Total(span<const double> values) {
        return reduce(values.cbegin(), values.cend());
    }

    /// Returns the dot product between the two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @returns The dot product between the two lists of values.
    export [[nodiscard]] int Dot(span<const int> values1, span<const int> values2) {
        return transform_reduce(values1.cbegin(), values1.cend(), values2.cbegin(), 0);
    }

    /// Returns the dot product between the two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @returns The dot product between the two lists of values.
    export [[nodiscard]] double Dot(span<const double> values1, span<const double> values2) {
        return transform_reduce(values1.cbegin(), values1.cend(), values2.cbegin(), 0.);
    }

    /// Returns the sum of a function over an index range.
    /// @tparam Fun The type of the function.
    /// @param begin The beginning index.
    /// @param end The ending index.
    /// @param fun A function to sum over.
    /// @returns The sum of the function over the index range.
    export template<invocable<int> Fun>
    [[nodiscard]] invoke_result_t<Fun, int> Sum(int begin, int end, Fun fun) {
        auto sum = invoke_result_t<Fun, int>();
        for (auto i = begin; i < end; ++i) sum += fun(i);
        return sum;
    }

    /// Returns the mean of a list of values.
    /// @param values A list of values.
    /// @returns The mean of the list of values.
    export [[nodiscard]] double Mean(span<const double> values) {
        return Total(values) / static_cast<double>(values.size());
    }

    /// Returns the variance of a list of values given its mean.
    /// @param values A list of values.
    /// @param mean The mean of the list of values.
    /// @returns The variance of list of values.
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

    /// Returns the covariance between two lists of values given their means.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @param mean1 The mean of the first list of values.
    /// @param mean2 The mean of the seconds list of values.
    /// @returns The covariance between the two lists of values
    export [[nodiscard]] double Covariance(span<const double> values1, span<const double> values2,
                                           double mean1, double mean2) {
        const auto buffer1 = values1 - mean1, buffer2 = values2 - mean2;
        return Dot(buffer1, buffer2) / static_cast<double>(values1.size() - 1);
    }

    /// Returns the covariance between two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @returns The covariance between the two lists of values.
    export [[nodiscard]] double Covariance(span<const double> values1, span<const double> values2) {
        return Covariance(values1, values2, Mean(values1), Mean(values2));
    }
}
