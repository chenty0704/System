module;

#include <boost/describe.hpp>
#include <boost/json.hpp>

export module System.JSON;

import System.Base;

using namespace std;
namespace describe = boost::describe;
namespace json = boost::json;
namespace mp11 = boost::mp11;

export namespace boost::system {
    using system::in_place_error;
    using system::in_place_value;
}

export namespace boost::json {
    using json::get;
    using json::make_error_code;
    using json::value;
    using json::value_to_tag;
}

/// Represents a described struct.
export template<typename T>
concept DescribedStruct = is_class_v<T> && describe::has_describe_members<T>::value &&
    mp11::mp_empty<describe::describe_members<T, describe::mod_protected | describe::mod_private>>::value;

export template<DescribedStruct T>
[[nodiscard]] T default_tag_invoke(const json::value_to_tag<T> &, const json::value &value) {
    static const auto Assign = []<typename M>(M &member, const json::value &_value) {
        member = json::value_to<M>(_value);
    };

    T object;
    using members = describe::describe_members<T, describe::mod_public | describe::mod_inherited>;
    for (const auto &pair : value.as_object()) {
        const auto key = pair.key();
        const auto &_value = pair.value();
        auto matched = false;
        mp11::mp_for_each<members>([&](auto member) {
            if (!matched && key == member.name) {
                Assign(object.*member.pointer, _value);
                matched = true;
            }
        });
        if (!matched) throw runtime_error("Invalid key.");
    }
    return object;
}

export template<DescribedStruct T>
[[nodiscard]] T tag_invoke(const json::value_to_tag<T> &tag, const json::value &value) {
    return default_tag_invoke(tag, value);
}

/// Provides utilities for JSON conversion.
namespace JSON {
    /// Returns a JSON representation of an object.
    /// @param object The object to serialize.
    /// @return A JSON representation of the object.
    export [[nodiscard]] string Serialize(const auto &object) {
        return json::serialize(json::value_from(object));
    }

    /// Recovers an object from a JSON representation.
    /// @tparam T The type of the object.
    /// @param value The JSON representation.
    /// @return The recovered object from the JSON representation.
    export template<typename T>
    [[nodiscard]] T Deserialize(string_view value) {
        return json::value_to<T>(json::parse(value));
    }
}
