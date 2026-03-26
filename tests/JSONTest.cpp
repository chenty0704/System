#include <gtest/gtest.h>

#include "System/Macros.h"

import System.Base;
import System.JSON;
import System.Reflection;

using namespace std;
namespace json = boost::json;

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

struct Shape {
protected:
    Shape() = default;

public:
    virtual ~Shape() = default;
};

DESCRIBE_STRUCT(Shape, (), ())

struct Circle : Shape {
    double Radius;
};

DESCRIBE_STRUCT(Circle, (Shape), (Radius))

struct Rectangle : Shape {
    double Width;
    double Height;
};

DESCRIBE_STRUCT(Rectangle, (Shape), (Width, Height))

JSON_REGISTER_DERIVED_TYPES(Shape, (Circle, Rectangle))

TEST(JSONTest, StructSerialization) {
    EXPECT_EQ(JSON::Serialize(Temperature{10.}), R"({"Value":1E1,"Unit":"Fahrenheit"})");
}

TEST(JSONTest, StructDeserialization) {
    EXPECT_EQ(JSON::Deserialize<Temperature>(R"({"Value":10.0,"Unit":"Celsius"})"),
              (Temperature{10., TemperatureUnit::Celsius}));
    EXPECT_EQ(JSON::Deserialize<Temperature>(R"({"Value":10.0})"), Temperature{10.});
}

TEST(JSONTest, PolymorphicStructDeserialization) {
    const auto shape = JSON::Deserialize<unique_ptr<Shape>>(R"({"$Type":"Circle","Radius":5.0})");
    EXPECT_EQ(dynamic_cast<const Circle &>(*shape), [] {
              Circle circle;
              circle.Radius = 5.;
              return circle;}());
}
