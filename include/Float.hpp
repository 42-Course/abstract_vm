/**
 * @file Float.hpp
 * @brief Defines the Float type alias for single-precision floating-point operands.
 */

#ifndef FLOAT_HPP
#define FLOAT_HPP

#include "Operand.tpp"

/**
 * @typedef Float
 * @brief Type alias for single-precision floating-point operands.
 *
 * Represents IEEE 754 single-precision floating-point numbers.
 * Has higher precision than all integer types but lower than Double.
 *
 * ## Precision Note
 * Float provides approximately 7 decimal digits of precision.
 *
 * ## Usage Example
 * ```cpp
 * // In the factory or VM:
 * Float myFloat("3.14159");
 * Float scientific("1.23e-4");
 * ```
 */
using Float = Operand<float, eOperandType::Float>;

#endif // FLOAT_HPP
