#include <gtest/gtest.h>

#include "System/System.h"

TEST(MDArrayTest, SpanConversion) {
    const vector vec = {1, 2, 3, 4};
    const mdspan<const int, dextents<int, 1>> span(vec.data(), vec.size());
    EXPECT_EQ(ToSpan(span).size(), vec.size());
}
