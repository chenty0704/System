module;

#pragma warning(disable: 4275)

#include <boost/describe.hpp>
#include <boost/json.hpp>

export module System.JSON;

import System.Base;
import System.Reflection;

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

export template<DescribedStruct T>
[[nodiscard]] T tag_invoke(const json::value_to_tag<T> &, const json::value &value) {
    using Members = describe::describe_members<T, describe::mod_public | describe::mod_inherited>;

    static const auto Assign = []<typename M>(M &member, const json::value &value) {
        member = json::value_to<M>(value);
    };

    T object;
    for (const auto &[key, _value] : value.as_object()) {
        auto isMatched = false;
        mp11::mp_for_each<Members>([&](auto member) {
            if (!isMatched && member.name == key) {
                Assign(object.*member.pointer, _value);
                isMatched = true;
            }
        });
        if (!isMatched) throw runtime_error("Invalid key.");
    }
    return object;
}

/// Provides utilities for JSON conversion.
namespace JSON {
    /// Returns a JSON representation of an object.
    /// @param object The object to serialize.
    /// @returns A JSON representation of the object.
    export [[nodiscard]] string Serialize(const auto &object) {
        return json::serialize(json::value_from(object));
    }

    /// Recovers an object from a JSON representation.
    /// @tparam T The type of the object.
    /// @param value The JSON representation.
    /// @returns The recovered object from the JSON representation.
    export template<typename T>
    [[nodiscard]] T Deserialize(string_view value) {
        return json::value_to<T>(json::parse(value));
    }
}
