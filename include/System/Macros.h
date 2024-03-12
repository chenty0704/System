#pragma once

#include <boost/describe.hpp>
#include <boost/preprocessor.hpp>

/// Stringizes an argument.
/// @param arg An argument to stringize.
#define STRINGIZE(arg) BOOST_PP_STRINGIZE(arg)

#define CONCAT_2(arg0, arg1) BOOST_PP_CAT(arg0, arg1)
#define CONCAT_3(arg0, arg1, arg2) CONCAT_2(CONCAT_2(arg0, arg1), arg2)

/// Returns the overload implementation for a variadic macro function with a specific number of variadic arguments.
/// @param FUN A variadic macro function.
/// @param ... A list of variadic arguments.
#define OVERLOAD(FUN, ...) BOOST_PP_OVERLOAD(CONCAT_2(FUN, _), __VA_ARGS__)

/// Returns a value.
/// @param value The value to return.
#define RETURN(value) CONCAT_2(value, )

/// Concatenates a list of arguments.
/// @param ... A list of arguments to concatenate.
#define CONCAT(...) RETURN(OVERLOAD(CONCAT, __VA_ARGS__)(__VA_ARGS__))

#define LESS(left, right) BOOST_PP_LESS(left, right)
#define GREATER(left, right) BOOST_PP_GREATER(left, right)

#define DECREMENT(value) BOOST_PP_DEC(value)
#define INCREMENT(value) BOOST_PP_INC(value)

#define TUPLE_SIZE(values) BOOST_PP_TUPLE_SIZE(values)
#define TUPLE_AT(values, index) BOOST_PP_TUPLE_ELEM(index, values)

#define FOR_EACH_1_STATE(FUN, values) (FUN, values, 0, TUPLE_SIZE(values))
#define FOR_EACH_1_CONDITION_IMPL(i, size) LESS(i, size)
#define FOR_EACH_1_CONDITION(r, state) FOR_EACH_1_CONDITION_IMPL(TUPLE_AT(state, 2), TUPLE_AT(state, 3))
#define FOR_EACH_1_ITERATION_IMPL(FUN, values, i, size) (FUN, values, INCREMENT(i), size)
#define FOR_EACH_1_ITERATION(r, state) \
    FOR_EACH_1_ITERATION_IMPL(TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3))
#define FOR_EACH_1_STATEMENT_IMPL(FUN, values, i) FUN(TUPLE_AT(values, i))
#define FOR_EACH_1_STATEMENT(r, state) \
    FOR_EACH_1_STATEMENT_IMPL(TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2))

#define FOR_EACH_1(FUN, values) \
    BOOST_PP_FOR(FOR_EACH_1_STATE(FUN, values), FOR_EACH_1_CONDITION, FOR_EACH_1_ITERATION, FOR_EACH_1_STATEMENT)

#define FOR_EACH_2_STATE_2(FUN, value1, values2) (FUN, value1, values2, 0, TUPLE_SIZE(values2))
#define FOR_EACH_2_CONDITION_2_IMPL(j, size2) LESS(j, size2)
#define FOR_EACH_2_CONDITION_2(r, state) FOR_EACH_2_CONDITION_2_IMPL(TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_ITERATION_2_IMPL(FUN, value1, values2, j, size2) (FUN, value1, values2, INCREMENT(j), size2)
#define FOR_EACH_2_ITERATION_2(r, state) FOR_EACH_2_ITERATION_2_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_STATEMENT_2_IMPL(FUN, value1, values2, j) FUN(value1, TUPLE_AT(values2, j))
#define FOR_EACH_2_STATEMENT_2(r, state) FOR_EACH_2_STATEMENT_2_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3))

#define FOR_EACH_2_STATE_1(FUN, values1, values2) (FUN, values1, values2, 0, TUPLE_SIZE(values1))
#define FOR_EACH_2_CONDITION_1_IMPL(i, size1) LESS(i, size1)
#define FOR_EACH_2_CONDITION_1(r, state) FOR_EACH_2_CONDITION_1_IMPL(TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_ITERATION_1_IMPL(FUN, values1, values2, i, size1) (FUN, values1, values2, INCREMENT(i), size1)
#define FOR_EACH_2_ITERATION_1(r, state) FOR_EACH_2_ITERATION_1_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_STATEMENT_1_IMPL(FUN, values1, values2, i) \
    BOOST_PP_FOR(FOR_EACH_2_STATE_2(FUN, TUPLE_AT(values1, i), values2), \
                 FOR_EACH_2_CONDITION_2, FOR_EACH_2_ITERATION_2, FOR_EACH_2_STATEMENT_2)
#define FOR_EACH_2_STATEMENT_1(r, state) \
    FOR_EACH_2_STATEMENT_1_IMPL(TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3))

#define FOR_EACH_2(FUN, values1, values2) BOOST_PP_FOR(FOR_EACH_2_STATE_1(FUN, values1, values2), \
    FOR_EACH_2_CONDITION_1, FOR_EACH_2_ITERATION_1, FOR_EACH_2_STATEMENT_1)

/// Applies a macro function to each tuple in the Cartesian product of the lists of values.
/// @param FUN A macro function.
/// @param ... Lists of values.
#define FOR_EACH(FUN, ...) RETURN(OVERLOAD(FOR_EACH, __VA_ARGS__)(FUN, __VA_ARGS__))

/// Describes a enum.
/// @param E The type of the enum.
/// @param ... The values of the enum.
#define DESCRIBE_ENUM(E, ...) BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)

/// Describes a struct.
/// @param C The type of the struct.
/// @param Bases The bases of the struct.
/// @param Members The members of the struct.
#define DESCRIBE_STRUCT(C, Bases, Members) BOOST_DESCRIBE_STRUCT(C, Bases, Members)
