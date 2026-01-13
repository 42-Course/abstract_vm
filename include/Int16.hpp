/**
 * @file Int16.hpp
 * @brief Defines the Int16 type alias for 16-bit signed integer operands.
 */

#ifndef INT16_HPP
#define INT16_HPP

#include <cstdint>
#include "Operand.tpp"

/**
 * @typedef Int16
 * @brief Type alias for 16-bit signed integer operands.
 *
 * Represents signed integers in the range [-32768, 32767].
 * Has higher precision than Int8 but lower than Int32.
 *
 * ## Usage Example
 * ```cpp
 * // In the factory or VM:
 * Int16 myInt16("32767");   // Maximum value
 * Int16 minInt16("-32768"); // Minimum value
 * ```
 */
using Int16 = Operand<int16_t, eOperandType::Int16>;

#endif // INT16_HPP
