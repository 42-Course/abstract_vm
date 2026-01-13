/**
 * @file Int8.hpp
 * @brief Defines the Int8 type alias for 8-bit signed integer operands.
 */

#ifndef INT8_HPP
#define INT8_HPP

#include <cstdint>
#include "Operand.tpp"

/**
 * @typedef Int8
 * @brief Type alias for 8-bit signed integer operands.
 *
 * Represents signed integers in the range [-128, 127].
 * This is the lowest precision integer type in AbstractVM.
 *
 * ## Usage Example
 * ```cpp
 * // In the factory or VM:
 * Int8 myInt8("127");      // Maximum value
 * Int8 minInt8("-128");    // Minimum value
 * ```
 */
using Int8 = Operand<int8_t, eOperandType::Int8>;

#endif // INT8_HPP
