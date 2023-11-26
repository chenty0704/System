#pragma once

#include <concepts>
#include <type_traits>

#include <boost/describe.hpp>
#include <boost/mp11.hpp>

using namespace std;

namespace describe = boost::describe;
namespace mp11 = boost::mp11;

/// \brief Defines and describes a enum.
/// \param E The type of the enum.
/// \param ... The values of the enum.
#define DEFINE_ENUM(E, ...) BOOST_DEFINE_ENUM_CLASS(E, __VA_ARGS__)

/// \brief Describes a struct.
/// \param C The type of the struct.
/// \param Bases The bases of the struct.
/// \param members The members of the struct.
#define DESCRIBE_STRUCT(C, Bases, members) BOOST_DESCRIBE_STRUCT(C, Bases, members)

/// \brief Represents a described struct.
template<typename T>
concept DescribedStruct = is_class_v<T> && describe::has_describe_members<T>::value &&
    mp11::mp_empty<describe::describe_members<T, describe::mod_protected | describe::mod_private>>::value;
