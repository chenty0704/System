module;

#define MDSPAN_IMPL_STANDARD_NAMESPACE std
#define MDSPAN_IMPL_PROPOSED_NAMESPACE experimental

#include <mdspan/mdarray.hpp>

export module System.MDArray;

using namespace std;
using namespace experimental;

export namespace std {
    using std::dynamic_extent;
    using std::extents;
    using std::full_extent;
    using std::mdspan;
    using std::submdspan;

    namespace experimental {
        using experimental::dims;
        using experimental::mdarray;
    }
}
