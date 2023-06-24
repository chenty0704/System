#pragma once

#include <boost/describe.hpp>

#define DEFINE_ENUM(E, ...) BOOST_DEFINE_ENUM_CLASS(E, __VA_ARGS__)
#define DESCRIBE_STRUCT(C, Bases, members) BOOST_DESCRIBE_STRUCT(C, Bases, members)
