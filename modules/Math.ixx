module;

#include <System/Macros.h>

export module System.Math;

import System.Base;

using namespace std;

template<typename T>
class scaled_span {
    span<const T> _values;
    T _scalar;

public:
    constexpr scaled_span(span<const T> values, T scalar) noexcept: _values(values), _scalar(scalar) {
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

#define SPAN_TYPE(isScaled, T) IF(NOT(isScaled), span<const T>, scaled_span<T>)

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

#define EXPORT_VECTOR_SCALAR_ASSIGNMNET_OPERATOR(T, op) \
    export span<T> CONCAT(operator, op, =)(span<T> values, T scalar) { \
        for (auto &value : values) value CONCAT(op, =) scalar; \
        return values; \
    }

#define EXPORT_VECTOR_VECTOR_ASSIGNMNET_OPERATOR(T, op, isScaled2) \
    export span<T> CONCAT(operator, op, =)(span<T> values1, SPAN_TYPE(isScaled2, T) values2) { \
        for (auto i = 0; i < values1.size(); ++i) values1[i] CONCAT(op, =) values2[i]; \
        return values1; \
    }

FOR_EACH(EXPORT_SCALAR_VECTOR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1))
FOR_EACH(EXPORT_VECTOR_SCALAR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1))
FOR_EACH(EXPORT_VECTOR_VECTOR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1), (0, 1))
FOR_EACH(EXPORT_VECTOR_SCALAR_ASSIGNMNET_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS)
FOR_EACH(EXPORT_VECTOR_VECTOR_ASSIGNMNET_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS, (0, 1))

/// Provides common math functions.
namespace Math {
    /// Returns the integer closest to a value.
    /// @param value A value to round.
    /// @return The integer closes to the value.
    export [[nodiscard]] int Round(double value) {
        return lround(value);
    }

    /// Rounds a value to the nearest multiple of a base value.
    /// @param value A value to round.
    /// @param base A base value.
    /// @return The nearest multiple of the base value.
    export [[nodiscard]] double Round(double value, double base) {
        return round(value / base) * base;
    }

    /// Returns the greatest integer less than or equal to a value.
    /// @param value A value to round down.
    /// @return The grestet integer less than or equal to the value.
    export [[nodiscard]] int Floor(double value) {
        return static_cast<int>(floor(value));
    }

    /// Rounds a value down to the nearest multiple of a base value.
    /// @param value A value to round down.
    /// @param base A base value.
    /// @return The greatest multiple of the base value less than or equal to the value.
    export [[nodiscard]] double Floor(double value, double base) {
        return floor(value / base) * base;
    }

    /// Returns the least integer greater than or equal to a value.
    /// @param value A value to round up.
    /// @return The least integer greater than or equal to the value.
    export [[nodiscard]] int Ceiling(double value) {
        return static_cast<int>(ceil(value));
    }

    /// Rounds a value up to the nearest multiple of a base value.
    /// @param value A value to round up.
    /// @param base A base value.
    /// @return The least multiple of the base value greater than or equal to the value.
    export [[nodiscard]] double Ceiling(double value, double base) {
        return ceil(value / base) * base;
    }

    /// Returns a view of a scaled list of values.
    /// @param values A list of values.
    /// @param scalar A scalar multipler.
    /// @return A view of the scaled list of values.
    export [[nodiscard]] scaled_span<int> Scaled(span<const int> values, int scalar) {
        return {values, scalar};
    }

    /// Returns a view of a scaled list of values.
    /// @param values A list of values.
    /// @param scalar A scalar multipler.
    /// @return A view of the scaled list of values.
    export [[nodiscard]] scaled_span<double> Scaled(span<const double> values, double scalar) {
        return {values, scalar};
    }

    /// Returns the power of a list of values.
    /// @param values A list of values.
    /// @param exponent The exponent.
    /// @return The power of the list of values.
    export [[nodiscard]] vector<double> Power(span<const double> values, double exponent) {
        return values | views::transform([&](double value) { return pow(value, exponent); }) | ranges::to<vector>();
    }

    /// Returns the total of a list of values.
    /// @param values A list of values.
    /// @return The total of the list of values.
    export [[nodiscard]] int Total(span<const int> values) {
        return reduce(values.begin(), values.end());
    }

    /// Returns the total of a list of values.
    /// @param values A list of values.
    /// @return The total of the list of values.
    export [[nodiscard]] double Total(span<const double> values) {
        return reduce(values.begin(), values.end());
    }

    /// Returns the dot product between the two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @return The dot product between the two lists of values.
    export [[nodiscard]] int Dot(span<const int> values1, span<const int> values2) {
        return transform_reduce(values1.begin(), values1.end(), values2.begin(), 0);
    }

    /// Returns the dot product between the two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @return The dot product between the two lists of values.
    export [[nodiscard]] double Dot(span<const double> values1, span<const double> values2) {
        return transform_reduce(values1.begin(), values1.end(), values2.begin(), 0.);
    }

    /// Returns the mean of a list of values.
    /// @param values A list of values.
    /// @return The mean of the list of values.
    export [[nodiscard]] double Mean(span<const double> values) {
        return Total(values) / static_cast<double>(values.size());
    }

    /// Returns the variance of a list of values given its mean.
    /// @param values A list of values.
    /// @param mean The mean of the list of values.
    /// @return The variance of list of values.
    export [[nodiscard]] double Variance(span<const double> values, double mean) {
        auto buffer = values - mean;
        buffer *= buffer;
        return Total(buffer) / static_cast<double>(values.size() - 1);
    }

    /// Returns the variance of a list of values.
    /// @param values A list of values.
    /// @return The variance of the list of values.
    export [[nodiscard]] double Variance(span<const double> values) {
        return Variance(values, Mean(values));
    }

    /// Returns the covariance between two lists of values given their means.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @param mean1 The mean of the first list of values.
    /// @param mean2 The mean of the seconds list of values.
    /// @return The covariance between the two lists of values
    export [[nodiscard]] double Covariance(span<const double> values1, span<const double> values2,
                                           double mean1, double mean2) {
        const auto buffer1 = values1 - mean1, buffer2 = values2 - mean2;
        return Dot(buffer1, buffer2) / static_cast<double>(values1.size() - 1);
    }

    /// Returns the covariance between two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @return The covariance between the two lists of values.
    export [[nodiscard]] double Covariance(span<const double> values1, span<const double> values2) {
        return Covariance(values1, values2, Mean(values1), Mean(values2));
    }
}
