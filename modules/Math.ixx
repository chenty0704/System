module;

#include <System/Macros.h>

export module System.Math;

import System.Base;

using namespace std;

#define VECTOR_TYPES (int, double)
#define VECTOR_OPERATORS (+, -, *, /)

#define GENERATE_SCALAR_VECTOR_OPERATOR(T, op) \
    vector<T> CONCAT(operator, op)(T scalar, span<const T> values) { \
        vector<T> out(values.size()); \
        for (auto i = 0; i < values.size(); ++i) out[i] = scalar op values[i]; \
        return out; \
    }

#define GENERATE_VECTOR_SCALAR_OPERATOR(T, op) \
    vector<T> CONCAT(operator, op)(span<const T> values, T scalar) { \
        vector<T> out(values.size()); \
        for (auto i = 0; i < values.size(); ++i) out[i] = values[i] op scalar; \
        return out; \
    }

#define GENERATE_VECTOR_VECTOR_OPERATOR(T, op) \
    vector<T> CONCAT(operator, op)(span<const T> values1, span<const T> values2) { \
        vector<T> out(values1.size()); \
        for (auto i = 0; i < values1.size(); ++i) out[i] = values1[i] op values2[i]; \
        return out; \
    }

#define GENERATE_VECTOR_SCALAR_ASSIGNMNET_OPERATOR(T, op) \
    span<T> CONCAT(operator, op, =)(span<T> values, T scalar) { \
        for (auto &value : values) value CONCAT(op, =) scalar; \
        return values; \
    }

#define GENERATE_VECTOR_VECTOR_ASSIGNMNET_OPERATOR(T, op) \
    span<T> CONCAT(operator, op, =)(span<T> values1, span<const T> values2) { \
        for (auto i = 0; i < values1.size(); ++i) values1[i] CONCAT(op, =) values2[i]; \
        return values1; \
    }

export {
    FOR_EACH(GENERATE_SCALAR_VECTOR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS)
    FOR_EACH(GENERATE_VECTOR_SCALAR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS)
    FOR_EACH(GENERATE_VECTOR_VECTOR_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS)
    FOR_EACH(GENERATE_VECTOR_SCALAR_ASSIGNMNET_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS)
    FOR_EACH(GENERATE_VECTOR_VECTOR_ASSIGNMNET_OPERATOR, VECTOR_TYPES, VECTOR_OPERATORS)
}

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

    /// Returns the mean of a list of values.
    /// @param values A list of values.
    /// @return The mean of the list of values.
    export [[nodiscard]] double Mean(span<const double> values) {
        return reduce(values.begin(), values.end()) / static_cast<double>(values.size());
    }

    /// Returns the variance of a list of values given its mean.
    /// @param values A list of values.
    /// @param mean The mean of the list of values.
    /// @return The variance of list of values.
    export [[nodiscard]] double Variance(span<const double> values, double mean) {
        auto buffer = values - mean;
        buffer *= buffer;
        return reduce(buffer.cbegin(), buffer.cend()) / static_cast<double>(values.size() - 1);
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
        return transform_reduce(buffer1.cbegin(), buffer1.cend(), buffer2.cbegin(), 0.)
            / static_cast<double>(values1.size() - 1);
    }

    /// Returns the covariance between two lists of values.
    /// @param values1 The first list of values.
    /// @param values2 The second list of values.
    /// @return The covariance between the two lists of values.
    export [[nodiscard]] double Covariance(span<const double> values1, span<const double> values2) {
        return Covariance(values1, values2, Mean(values1), Mean(values2));
    }
}
