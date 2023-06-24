#pragma once

#include <string>
#include <boost/json.hpp>

using namespace std;
namespace json = boost::json;

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
