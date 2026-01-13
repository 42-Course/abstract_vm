/**
 * @file Double.hpp
 * @brief Defines the Double type alias for double-precision floating-point operands.
 */

#ifndef DOUBLE_HPP
#define DOUBLE_HPP

#include "Operand.tpp"

/**
 * @typedef Double
 * @brief Type alias for double-precision floating-point operands.
 *
 * Represents IEEE 754 double-precision floating-point numbers.
 * This is the highest precision type available in AbstractVM.
 *
 * ## Precision Note
 * Double provides approximately 15-17 decimal digits of precision.
 *
 * ## Usage Example
 * ```cpp
 * // In the factory or VM:
 * Double myDouble("3.141592653589793");
 * Double scientific("1.23456789e-100");
 * ```
 */
using Double = Operand<double, eOperandType::Double>;

#endif // DOUBLE_HPP
