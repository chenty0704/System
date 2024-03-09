export module System.Math;

import System.Base;

using namespace std;

/// Provides common math functions.
namespace Math {
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
        vector buffer(values.size(), 0.);
        for (auto i = 0; i < values.size(); ++i) buffer[i] = values[i] - mean;
        for (auto &value : buffer) value *= value;
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
        vector buffer1(values1.size(), 0.), buffer2(values2.size(), 0.);
        for (auto i = 0; i < values1.size(); ++i) buffer1[i] = values1[i] - mean1;
        for (auto i = 0; i < values2.size(); ++i) buffer2[i] = values2[i] - mean2;
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
