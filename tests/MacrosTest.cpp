#include <gtest/gtest.h>

#include "System/Macros.h"

using namespace std;
using namespace literals;

TEST(MacrosTest, ForEach) {
    EXPECT_EQ(STRINGIZE(FOR_EACH(INCREMENT, (0, 1, 2, 3))), "1 2 3 4"sv);
    EXPECT_EQ(STRINGIZE(FOR_EACH(CONCAT, (a, b, c), (1, 2, 3))), "a1 a2 a3 b1 b2 b3 c1 c2 c3"sv);
}
