module;

#include <boost/describe.hpp>

export module System.Reflection;

import System.Base;

using namespace std;
namespace describe = boost::describe;
namespace mp11 = boost::mp11;

/// Represents a described enum.
export template<typename E>
concept DescribedEnum = is_enum_v<E> && describe::has_describe_enumerators<E>::value;

/// Represents a described struct.
export template<typename T>
concept DescribedStruct = is_class_v<T> && describe::has_describe_members<T>::value &&
    mp11::mp_empty<describe::describe_members<T, describe::mod_protected | describe::mod_private>>::value;

export template<DescribedStruct T>
bool operator==(const T &left, const T &right) {
    using Members = describe::describe_members<T, describe::mod_public | describe::mod_inherited>;

    auto result = true;
    mp11::mp_for_each<Members>([&](auto member) {
        result = result && left.*member.pointer == right.*member.pointer;
    });
    return result;
}

export template<DescribedStruct T>
bool operator!=(const T &left, const T &right) {
    return !(left == right);
}

export template<DescribedEnum E>
ostream &operator<<(ostream &stream, E value) {
    return stream << describe::enum_to_string(value, "Unknown");
}

export template<DescribedStruct T>
ostream &operator<<(ostream &stream, const T &object) {
    using Members = describe::describe_members<T, describe::mod_public | describe::mod_inherited>;

    stream << "{";
    auto first = true;
    mp11::mp_for_each<Members>([&](auto member) {
        if (first) first = false;
        else stream << ", ";
        stream << member.name << " = " << object.*member.pointer;
    });
    return stream << "}";
}

export template<DescribedEnum E>
struct formatter<E> : formatter<string_view> {
    format_context::iterator format(E value, format_context &context) const {
        return formatter<string_view>::format(describe::enum_to_string(value, "Unknown"), context);
    }
};

export template<DescribedStruct T>
struct formatter<T> : formatter<string_view> {
    format_context::iterator format(const T &object, format_context &context) const {
        return formatter<string_view>::format((ostringstream() << object).view(), context);
    }
};
