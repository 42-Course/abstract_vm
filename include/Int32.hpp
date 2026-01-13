/**
 * @file Int32.hpp
 * @brief Defines the Int32 type alias for 32-bit signed integer operands.
 */

#ifndef INT32_HPP
#define INT32_HPP

#include <cstdint>
#include "Operand.tpp"

/**
 * @typedef Int32
 * @brief Type alias for 32-bit signed integer operands.
 *
 * Represents signed integers in the range [-2147483648, 2147483647].
 * This is the highest precision integer type in AbstractVM.
 *
 * ## Usage Example
 * ```cpp
 * // In the factory or VM:
 * Int32 myInt32("2147483647");   // Maximum value
 * Int32 minInt32("-2147483648"); // Minimum value
 * ```
 */
using Int32 = Operand<int32_t, eOperandType::Int32>;

#endif // INT32_HPP
