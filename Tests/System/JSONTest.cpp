#include <gtest/gtest.h>

DEFINE_ENUM(TemperatureUnit, Fahrenheit, Celsius, Kelvin)

struct Temperature {
    double Value;
    TemperatureUnit Unit;

    bool operator==(const Temperature &) const = default;
};

DESCRIBE_STRUCT(Temperature, (), (Value, Unit))

TEST(JSONTest, Serialization) {
    EXPECT_EQ(JSON::Serialize(Temperature{10, TemperatureUnit::Fahrenheit}),
              R"({"Value":1E1,"Unit":"Fahrenheit"})");
}

TEST(JSONTest, Deserialization) {
    EXPECT_EQ(JSON::Deserialize<Temperature>(R"({"Value":10,"Unit":"Celsius"})"),
              (Temperature{10, TemperatureUnit::Celsius}));
}
