module;

#pragma warning(disable: 4267)

#include <experimental/mdarray>
#include <experimental/mdspan>

export module System.MDArray;

using namespace std;
using namespace experimental;

export namespace std::experimental {
    using experimental::default_accessor;
    using experimental::dextents;
    using experimental::dynamic_extent;
    using experimental::extents;
    using experimental::full_extent;
    using experimental::layout_right;
    using experimental::mdarray;
    using experimental::mdspan;
    using experimental::submdspan;

    template<size_t rank, typename IndexType = size_t>
    using dims = dextents<IndexType, rank>;
}

/// Flattens a multidimensional span to a normal span.
/// @tparam T The type of elements.
/// @tparam Extents The type of dimensions.
/// @param values A multidimensional span.
/// @return A normal span of the same elements.
export template<typename T, typename Extents>
[[nodiscard]] span<T> ToSpan(mdspan<T, Extents> values) {
    return {values.data_handle(), values.size()};
}
