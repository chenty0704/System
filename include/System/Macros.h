#pragma once

#include <boost/describe.hpp>
#include <boost/preprocessor.hpp>

/// Stringizes an argument.
/// @param arg An argument to stringize.
/// @returns The stringized argument.
#define STRINGIZE(arg) BOOST_PP_STRINGIZE(arg)

#define CONCAT_2(arg0, arg1) BOOST_PP_CAT(arg0, arg1)
#define CONCAT_3(arg0, arg1, arg2) CONCAT_2(CONCAT_2(arg0, arg1), arg2)

/// Returns the overload implementation for a variadic macro function with a specific number of variadic arguments.
/// @param FUNCTION A variadic macro function.
/// @param ... A list of variadic arguments.
/// @returns The overload implementation for the variadic macro function with the specific number of variadic arguments.
#define OVERLOAD(FUNCTION, ...) BOOST_PP_OVERLOAD(CONCAT_2(FUNCTION, _), __VA_ARGS__)

/// Returns a value.
/// @param value The value to return.
#define RETURN(value) CONCAT_2(value, )

/// Concatenates a list of arguments.
/// @param ... A list of arguments to concatenate.
/// @returns The concatenated value.
#define CONCAT(...) RETURN(OVERLOAD(CONCAT, __VA_ARGS__)(__VA_ARGS__))

/// Negates a value.
/// @param value A value to negate.
/// @returns The negated value.
#define NOT(value) BOOST_PP_NOT(value)

/// Returns whether the first value is less than the second value.
/// @param left The first value.
/// @param right The second value.
/// @returns Whether the first value is less than the second value.
#define LESS(left, right) BOOST_PP_LESS(left, right)

/// Returns whether the first value is greater than the second value.
/// @param left The first value.
/// @param right The second value.
/// @returns Whether the first value is greater than the second value.
#define GREATER(left, right) BOOST_PP_GREATER(left, right)

/// Returns one of two values based on a condition.
/// @param condition The test condition.
/// @param trueVal The return value if the condition is true.
/// @param falseVal The return value if the condition is false.
/// @returns One of the two values based on the condition.
#define IF(condition, trueVal, falseVal) BOOST_PP_IF(condition, trueVal, falseVal)

#define DECREMENT(value) BOOST_PP_DEC(value)
#define INCREMENT(value) BOOST_PP_INC(value)

#define TUPLE_SIZE(values) BOOST_PP_TUPLE_SIZE(values)
#define TUPLE_AT(values, index) BOOST_PP_TUPLE_ELEM(index, values)

// The implementation for FOR_EACH_1.

#define FOR_EACH_1_STATE(FUNCTION, values) (FUNCTION, values, 0, TUPLE_SIZE(values))
#define FOR_EACH_1_CONDITION_IMPL(i, size) LESS(i, size)
#define FOR_EACH_1_CONDITION(r, state) FOR_EACH_1_CONDITION_IMPL(TUPLE_AT(state, 2), TUPLE_AT(state, 3))
#define FOR_EACH_1_ITERATION_IMPL(FUNCTION, values, i, size) (FUNCTION, values, INCREMENT(i), size)
#define FOR_EACH_1_ITERATION(r, state) \
    FOR_EACH_1_ITERATION_IMPL(TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3))
#define FOR_EACH_1_STATEMENT_IMPL(FUNCTION, values, i) FUNCTION(TUPLE_AT(values, i))
#define FOR_EACH_1_STATEMENT(r, state) \
    FOR_EACH_1_STATEMENT_IMPL(TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2))

#define FOR_EACH_1(FUNCTION, values) \
    BOOST_PP_FOR(FOR_EACH_1_STATE(FUNCTION, values), FOR_EACH_1_CONDITION, FOR_EACH_1_ITERATION, FOR_EACH_1_STATEMENT)

// The implementation for FOR_EACH_2.

#define FOR_EACH_2_STATE_2(FUNCTION, value1, values2) (FUNCTION, value1, values2, 0, TUPLE_SIZE(values2))
#define FOR_EACH_2_CONDITION_2_IMPL(j, size2) LESS(j, size2)
#define FOR_EACH_2_CONDITION_2(r, state) FOR_EACH_2_CONDITION_2_IMPL(TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_ITERATION_2_IMPL(FUNCTION, value1, values2, j, size2) \
    (FUNCTION, value1, values2, INCREMENT(j), size2)
#define FOR_EACH_2_ITERATION_2(r, state) FOR_EACH_2_ITERATION_2_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_STATEMENT_2_IMPL(FUNCTION, value1, values2, j) FUNCTION(value1, TUPLE_AT(values2, j))
#define FOR_EACH_2_STATEMENT_2(r, state) FOR_EACH_2_STATEMENT_2_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3))

#define FOR_EACH_2_STATE_1(FUNCTION, values1, values2) (FUNCTION, values1, values2, 0, TUPLE_SIZE(values1))
#define FOR_EACH_2_CONDITION_1_IMPL(i, size1) LESS(i, size1)
#define FOR_EACH_2_CONDITION_1(r, state) FOR_EACH_2_CONDITION_1_IMPL(TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_ITERATION_1_IMPL(FUNCTION, values1, values2, i, size1) \
    (FUNCTION, values1, values2, INCREMENT(i), size1)
#define FOR_EACH_2_ITERATION_1(r, state) FOR_EACH_2_ITERATION_1_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4))
#define FOR_EACH_2_STATEMENT_1_IMPL(FUNCTION, values1, values2, i) \
    BOOST_PP_FOR(FOR_EACH_2_STATE_2(FUNCTION, TUPLE_AT(values1, i), values2), \
                 FOR_EACH_2_CONDITION_2, FOR_EACH_2_ITERATION_2, FOR_EACH_2_STATEMENT_2)
#define FOR_EACH_2_STATEMENT_1(r, state) \
    FOR_EACH_2_STATEMENT_1_IMPL(TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3))

#define FOR_EACH_2(FUNCTION, values1, values2) \
    BOOST_PP_FOR(FOR_EACH_2_STATE_1(FUNCTION, values1, values2), \
                 FOR_EACH_2_CONDITION_1, FOR_EACH_2_ITERATION_1, FOR_EACH_2_STATEMENT_1)

// The implementation for FOR_EACH_3.

#define FOR_EACH_3_STATE_3(FUNCTION, value1, value2, values3) \
    (FUNCTION, value1, value2, values3, 0, TUPLE_SIZE(values3))
#define FOR_EACH_3_CONDITION_3_IMPL(k, size3) LESS(k, size3)
#define FOR_EACH_3_CONDITION_3(r, state) FOR_EACH_3_CONDITION_3_IMPL(TUPLE_AT(state, 4), TUPLE_AT(state, 5))
#define FOR_EACH_3_ITERATION_3_IMPL(FUNCTION, value1, value2, values3, k, size3) \
    (FUNCTION, value1, value2, values3, INCREMENT(k), size3)
#define FOR_EACH_3_ITERATION_3(r, state) FOR_EACH_3_ITERATION_3_IMPL(TUPLE_AT(state, 0), \
    TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4), TUPLE_AT(state, 5))
#define FOR_EACH_3_STATEMENT_3_IMPL(FUNCTION, value1, value2, values3, k) FUNCTION(value1, value2, TUPLE_AT(values3, k))
#define FOR_EACH_3_STATEMENT_3(r, state) FOR_EACH_3_STATEMENT_3_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4))

#define FOR_EACH_3_STATE_2(FUNCTION, value1, values2, values3) \
    (FUNCTION, value1, values2, values3, 0, TUPLE_SIZE(values2))
#define FOR_EACH_3_CONDITION_2_IMPL(j, size2) LESS(j, size2)
#define FOR_EACH_3_CONDITION_2(r, state) FOR_EACH_3_CONDITION_2_IMPL(TUPLE_AT(state, 4), TUPLE_AT(state, 5))
#define FOR_EACH_3_ITERATION_2_IMPL(FUNCTION, value1, values2, values3, j, size2) \
    (FUNCTION, value1, values2, values3, INCREMENT(j), size2)
#define FOR_EACH_3_ITERATION_2(r, state) FOR_EACH_3_ITERATION_2_IMPL(TUPLE_AT(state, 0), \
    TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4), TUPLE_AT(state, 5))
#define FOR_EACH_3_STATEMENT_2_IMPL(FUNCTION, value1, values2, values3, j) \
    BOOST_PP_FOR(FOR_EACH_3_STATE_3(FUNCTION, value1, TUPLE_AT(values2, j), values3), \
                 FOR_EACH_3_CONDITION_3, FOR_EACH_3_ITERATION_3, FOR_EACH_3_STATEMENT_3)
#define FOR_EACH_3_STATEMENT_2(r, state) FOR_EACH_3_STATEMENT_2_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4))

#define FOR_EACH_3_STATE_1(FUNCTION, values1, values2, values3) \
    (FUNCTION, values1, values2, values3, 0, TUPLE_SIZE(values1))
#define FOR_EACH_3_CONDITION_1_IMPL(i, size1) LESS(i, size1)
#define FOR_EACH_3_CONDITION_1(r, state) FOR_EACH_3_CONDITION_1_IMPL(TUPLE_AT(state, 4), TUPLE_AT(state, 5))
#define FOR_EACH_3_ITERATION_1_IMPL(FUNCTION, values1, values2, values3, i, size1) \
    (FUNCTION, values1, values2, values3, INCREMENT(i), size1)
#define FOR_EACH_3_ITERATION_1(r, state) FOR_EACH_3_ITERATION_1_IMPL(TUPLE_AT(state, 0), \
    TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4), TUPLE_AT(state, 5))
#define FOR_EACH_3_STATEMENT_1_IMPL(FUNCTION, values1, values2, values3, i) \
    BOOST_PP_FOR(FOR_EACH_3_STATE_2(FUNCTION, TUPLE_AT(values1, i), values2, values3), \
                 FOR_EACH_3_CONDITION_2, FOR_EACH_3_ITERATION_2, FOR_EACH_3_STATEMENT_2)
#define FOR_EACH_3_STATEMENT_1(r, state) FOR_EACH_3_STATEMENT_1_IMPL( \
    TUPLE_AT(state, 0), TUPLE_AT(state, 1), TUPLE_AT(state, 2), TUPLE_AT(state, 3), TUPLE_AT(state, 4))

#define FOR_EACH_3(FUNCTION, values1, values2, values3) \
    BOOST_PP_FOR(FOR_EACH_3_STATE_1(FUNCTION, values1, values2, values3), \
                 FOR_EACH_3_CONDITION_1, FOR_EACH_3_ITERATION_1, FOR_EACH_3_STATEMENT_1)

/// Applies a macro function to each tuple in the Cartesian product of the lists of values.
/// @param FUNCTION A macro function.
/// @param ... Lists of values.
#define FOR_EACH(FUNCTION, ...) RETURN(OVERLOAD(FOR_EACH, __VA_ARGS__)(FUNCTION, __VA_ARGS__))

/// Describes a enum.
/// @param E The type of the enum.
/// @param ... The values of the enum.
#define DESCRIBE_ENUM(E, ...) BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)

/// Describes a struct.
/// @param T The type of the struct.
/// @param Bases The bases of the struct.
/// @param Members The members of the struct.
#define DESCRIBE_STRUCT(T, Bases, Members) BOOST_DESCRIBE_STRUCT(T, Bases, Members)
