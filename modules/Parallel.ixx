export module System.Parallel;

import System.Base;

using namespace std;

/// Provides support for parallel loops.
namespace Parallel {
    /// Applies a function to a range in parallel.
    /// @tparam It The type of the iterator.
    /// @tparam Fun The type of the function.
    /// @param begin The beginning iterator.
    /// @param end The ending iterator.
    /// @param function A function to apply to the range.
    export template<forward_iterator It, indirectly_unary_invocable<It> Fun>
    void ForEach(It begin, It end, Fun function) {
        vector<exception_ptr> exceptions;
        mutex exceptionsMutex;
        for_each(execution::par, begin, end, [&](iter_reference_t<It> value) {
            try { function(value); } catch (...) {
                lock_guard guard(exceptionsMutex);
                exceptions.push_back(current_exception());
            }
        });
        ranges::for_each(exceptions, rethrow_exception);
    }

    /// Applies a function to an index range in parallel.
    /// @tparam Fun The type of the function.
    /// @param beginIdx The beginning index.
    /// @param endIdx The ending index.
    /// @param function A function to apply to the index range.
    export template<invocable<int> Fun>
    void For(int beginIdx, int endIdx, Fun function) {
        const auto indices = views::iota(beginIdx, endIdx);
        ForEach(indices.cbegin(), indices.cend(), function);
    }
}
