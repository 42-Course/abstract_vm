/**
 * @file eOperandType.hpp
 * @brief Defines the eOperandType enumeration for operand types in AbstractVM.
 */

#ifndef EOPERANDTYPE_HPP
#define EOPERANDTYPE_HPP

/**
 * @enum eOperandType
 * @brief Enumeration representing the different types of operands supported by AbstractVM.
 *
 * The order of this enumeration represents the precision hierarchy, where:
 * Int8 < Int16 < Int32 < Float < Double
 *
 * This ordering is used to determine the result type when operations are performed
 * between operands of different types. The result takes the type of the more precise operand.
 *
 * ## Usage Example
 * ```cpp
 * eOperandType type = eOperandType::Int32;
 * if (type < eOperandType::Float) {
 *     // Int32 has lower precision than Float
 * }
 * ```
 */
enum class eOperandType {
    Int8 = 0,   ///< 8-bit signed integer type (lowest precision)
    Int16 = 1,  ///< 16-bit signed integer type
    Int32 = 2,  ///< 32-bit signed integer type
    Float = 3,  ///< Single-precision floating-point type
    Double = 4  ///< Double-precision floating-point type (highest precision)
};

#endif // EOPERANDTYPE_HPP
