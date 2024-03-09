#pragma once

#include <boost/describe.hpp>

/// Describes a enum.
/// @param E The type of the enum.
/// @param ... The values of the enum.
#define DESCRIBE_ENUM(E, ...) BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)

/// Describes a struct.
/// @param C The type of the struct.
/// @param Bases The bases of the struct.
/// @param Members The members of the struct.
#define DESCRIBE_STRUCT(C, Bases, Members) BOOST_DESCRIBE_STRUCT(C, Bases, Members)
