#include <gtest/gtest.h>

#include "System/System.h"

DEFINE_ENUM(TemperatureUnit, Fahrenheit, Celsius, Kelvin)

struct Temperature {
    double Value;
    TemperatureUnit Unit = TemperatureUnit::Fahrenheit;

    bool operator==(const Temperature &) const noexcept = default;
};

DESCRIBE_STRUCT(Temperature, (), (Value, Unit))

TEST(JSONTest, StructSerialization) {
    EXPECT_EQ(JSON::Serialize(Temperature{10, TemperatureUnit::Fahrenheit}),
              R"({"Value":1E1,"Unit":"Fahrenheit"})");
}

TEST(JSONTest, StructDeserialization) {
    EXPECT_EQ(JSON::Deserialize<Temperature>(R"({"Value":10,"Unit":"Celsius"})"),
              (Temperature{10, TemperatureUnit::Celsius}));
    EXPECT_EQ(JSON::Deserialize<Temperature>(R"({"Value":10})"),
              (Temperature{10, TemperatureUnit::Fahrenheit}));
}
