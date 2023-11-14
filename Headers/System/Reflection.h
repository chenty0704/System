#pragma once

#include <boost/describe.hpp>

/// \brief Describes a enum.
/// \param E The type of the enum.
/// \param ... The values of the enum.
#define DEFINE_ENUM(E, ...) BOOST_DEFINE_ENUM_CLASS(E, __VA_ARGS__)

/// \brief Describes a struct.
/// \param C The type of the struct.
/// \param Bases The bases of the struct.
/// \param members The members of the struct.
#define DESCRIBE_STRUCT(C, Bases, members) BOOST_DESCRIBE_STRUCT(C, Bases, members)
