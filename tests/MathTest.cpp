#include <gtest/gtest.h>

import System.Math;

using namespace std;

TEST(MathTest, BasicStatistics) {
    const vector values1 = {1., 2., 3., 4.}, values2 = {8., 7., 6., 5.};
    const auto mean1 = Math::Mean(values1), mean2 = Math::Mean(values2);
    const auto variance1 = Math::Variance(values1, mean1), variance2 = Math::Variance(values2, mean2);
    const auto covariance = Math::Covariance(values1, values2, mean1, mean2);

    EXPECT_EQ(mean1, 2.5);
    EXPECT_EQ(mean2, 6.5);
    EXPECT_EQ(variance1, 5 / 3.);
    EXPECT_EQ(variance2, 5 / 3.);
    EXPECT_EQ(covariance, -5 / 3.);
}
