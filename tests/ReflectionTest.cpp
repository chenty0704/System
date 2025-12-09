#include <gtest/gtest.h>

#include "System/Macros.h"

import System.Base;
import System.Reflection;

using namespace std;

enum class TemperatureUnit {
    Fahrenheit,
    Celsius,
    Kelvin
};

DESCRIBE_ENUM(TemperatureUnit, Fahrenheit, Celsius, Kelvin)

struct Temperature {
    double Value;
    TemperatureUnit Unit = TemperatureUnit::Fahrenheit;
};

DESCRIBE_STRUCT(Temperature, (), (Value, Unit))

TEST(ReflectionTest, Comparison) {
    EXPECT_EQ(Temperature{10.}, Temperature{10.});
    EXPECT_NE(Temperature{10.}, Temperature{20.});
}

TEST(ReflectionTest, Formatting) {
    EXPECT_EQ(format("{}", Temperature{10.}), "{Value = 10, Unit = Fahrenheit}");
}
