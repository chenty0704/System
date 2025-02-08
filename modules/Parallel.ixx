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
    /// @param fun A function to apply to the range.
    export template<forward_iterator It, indirectly_unary_invocable<It> Fun>
    void ForEach(It begin, It end, Fun fun) {
        vector<exception_ptr> exceptions;
        mutex exceptionsMutex;
        for_each(execution::par, begin, end, [&](iter_reference_t<It> value) {
            try { fun(value); } catch (...) {
                lock_guard guard(exceptionsMutex);
                exceptions.push_back(current_exception());
            }
        });
        ranges::for_each(exceptions, rethrow_exception);
    }

    /// Applies a function to an index range in parallel.
    /// @tparam Fun The type of the function.
    /// @param begin The beginning index.
    /// @param end The ending index.
    /// @param fun A function to apply to the index range.
    export template<invocable<int> Fun>
    void For(int begin, int end, Fun fun) {
        const auto indices = views::iota(begin, end);
        ForEach(indices.cbegin(), indices.cend(), fun);
    }
}
