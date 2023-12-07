#pragma once

#include <filesystem>
#include <string>
#include <type_traits>

#include <boost/describe.hpp>
#include <boost/json.hpp>
#include <boost/mp11.hpp>

#include "System/Reflection.h"

using namespace std;

namespace describe = boost::describe;
namespace json = boost::json;
namespace mp11 = boost::mp11;

namespace boost::json {
    inline filesystem::path tag_invoke(const value_to_tag<filesystem::path> &, const value &val) {
        return val.as_string().data();
    }

    template<DescribedStruct T>
    T tag_invoke_default(const value_to_tag<T> &, const value &val) {
        T obj;
        const auto &_obj = val.as_object();
        using members = describe::describe_members<T, describe::mod_public>;
        mp11::mp_for_each<members>([&](auto member) {
            using M = remove_reference_t<decltype(obj.*member.pointer)>;
            if (const auto it = _obj.find(member.name); it != _obj.cend())
                obj.*member.pointer = value_to<M>(it->value());
        });
        return obj;
    }

    template<DescribedStruct T>
    T tag_invoke(const value_to_tag<T> &tag, const value &val) {
        return tag_invoke_default(tag, val);
    }
}

/// \brief Provides utilities for JSON conversion.
namespace JSON {
    /// \brief Returns a JSON representation of an object.
    /// \param obj The object to serialize.
    /// \return A JSON representation of the object.
    string Serialize(const auto &obj) {
        return json::serialize(json::value_from(obj));
    }

    /// \brief Recovers an object from a JSON representation.
    /// \tparam T The type of the object.
    /// \param str The JSON represenation.
    /// \return The recovered object from the JSON represenation.
    template<typename T>
    T Deserialize(string_view str) {
        return json::value_to<T>(json::parse(str));
    }
}
