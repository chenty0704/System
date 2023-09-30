#pragma once

#include <string>

#include <boost/describe.hpp>
#include <boost/json.hpp>
#include <boost/mp11.hpp>

using namespace std;

namespace describe = boost::describe;
namespace json = boost::json;
namespace mp11 = boost::mp11;

template<typename T>
requires is_class_v<T>
T tag_invoke(const json::value_to_tag<T> &, const json::value &value) {
    T obj;
    const auto &jsonObj = value.as_object();
    using members = describe::describe_members<T, describe::mod_public>;
    mp11::mp_for_each<members>([&](auto member) {
        using M = remove_reference_t<decltype(obj.*member.pointer)>;
        if (const auto it = jsonObj.find(member.name); it != jsonObj.cend())
            obj.*member.pointer = json::value_to<M>(it->value());
    });
    return obj;
}

namespace JSON {
    template<typename T>
    inline string Serialize(const T &obj) {
        return json::serialize(json::value_from(obj));
    }

    template<typename T>
    inline T Deserialize(string_view str) {
        return json::value_to<T>(json::parse(str));
    }
}
