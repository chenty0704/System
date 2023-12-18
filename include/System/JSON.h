#pragma once

#include <filesystem>
#include <ranges>
#include <stdexcept>
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
        return std::string_view(val.as_string());
    }

    template<DescribedStruct T>
    T default_tag_invoke(const value_to_tag<T> &, const value &val) {
        T obj;
        using members = describe::describe_members<T, describe::mod_public>;
        for (const auto &[k, v] : val.as_object()) {
            auto matched = false;
            mp11::mp_for_each<members>([&](auto member) {
                if (!matched && k == member.name) {
                    using M = remove_reference_t<decltype(obj.*member.pointer)>;
                    obj.*member.pointer = value_to<M>(v);
                    matched = true;
                }
            });
            if (!matched) throw runtime_error("Invalid key.");
        }
        return obj;
    }

    template<DescribedStruct T>
    T tag_invoke(const value_to_tag<T> &tag, const value &val) {
        return default_tag_invoke(tag, val);
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
