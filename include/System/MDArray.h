#pragma once

#define MDSPAN_USE_PAREN_OPERATOR true

#include <experimental/mdarray>
#include <experimental/mdspan>

using namespace std;

using experimental::dextents;
using experimental::full_extent;
using experimental::mdarray;
using experimental::mdspan;
using experimental::submdspan;

/// \brief Converts a 1D multi-dimensional span to normal span.
/// \tparam T The type of elements.
/// \param arr The 1D multi-dimensional span to convert.
/// \return A normal span of the same elements.
template<typename T>
span<T> ToSpan(mdspan<T, dextents<int, 1>> arr) {
    return {arr.data_handle(), arr.size()};
}
