#pragma once

#include <concepts>
#include <string>

#include <boost/describe.hpp>
#include <boost/json.hpp>
#include <boost/mp11.hpp>

using namespace std;

namespace describe = boost::describe;
namespace json = boost::json;
namespace mp11 = boost::mp11;

template<semiregular T> requires is_class_v<T>
T tag_invoke(const json::value_to_tag<T> &, const json::value &value) {
    T obj;
    const auto &_obj = value.as_object();
    using members = describe::describe_members<T, describe::mod_public>;
    mp11::mp_for_each<members>([&](auto member) {
        using M = remove_reference_t<decltype(obj.*member.pointer)>;
        if (const auto it = _obj.find(member.name); it != _obj.cend())
            obj.*member.pointer = json::value_to<M>(it->value());
    });
    return obj;
}

/// \brief Provides utilities for JSON conversion.
namespace JSON {
    /// \brief Returns a JSON representation of an object.
    /// \tparam T The type of the object.
    /// \param obj The object to serialize.
    /// \return A JSON representation of the object.
    template<semiregular T>
    string Serialize(const T &obj) {
        return json::serialize(json::value_from(obj));
    }

    /// \brief Recovers an object from a JSON representation.
    /// \tparam T The type of the object.
    /// \param str The JSON represenation.
    /// \return The recovered object from the JSON represenation.
    template<semiregular T>
    T Deserialize(string_view str) {
        return json::value_to<T>(json::parse(str));
    }
}
