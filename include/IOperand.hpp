/**
 * @file IOperand.hpp
 * @brief Defines the IOperand interface for all operand types in AbstractVM.
 */

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <string>
#include "eOperandType.hpp"

/**
 * @interface IOperand
 * @brief Abstract interface that all operand classes must implement.
 *
 * This interface defines the contract for all operand types in AbstractVM.
 * Each concrete operand class (Int8, Int16, Int32, Float, Double) must
 * implement all the pure virtual methods defined in this interface.
 *
 * ## Key Concepts
 *
 * ### Precision
 * The precision of an operand determines the result type of arithmetic operations.
 * When two operands of different types are used in an operation, the result
 * takes the type of the more precise operand.
 *
 * ### Memory Management
 * All arithmetic operators return dynamically allocated IOperand pointers.
 * The caller is responsible for managing the lifetime of these returned objects.
 *
 * ## Usage Example
 * ```cpp
 * const IOperand* op1 = factory.createOperand(eOperandType::Int32, "42");
 * const IOperand* op2 = factory.createOperand(eOperandType::Float, "3.14");
 * const IOperand* result = *op1 + *op2; // Result is Float type
 *
 * std::cout << result->toString() << std::endl;
 *
 * delete op1;
 * delete op2;
 * delete result;
 * ```
 */
class IOperand {
public:
    /**
     * @brief Gets the precision level of this operand's type.
     *
     * The precision is represented as an integer corresponding to the
     * eOperandType enumeration value. Higher values indicate higher precision.
     *
     * @return int The precision level (0 for Int8, 1 for Int16, ..., 4 for Double)
     */
    virtual int getPrecision(void) const = 0;

    /**
     * @brief Gets the type of this operand.
     *
     * @return eOperandType The enumeration value representing this operand's type
     */
    virtual eOperandType getType(void) const = 0;

    /**
     * @brief Performs addition between this operand and another.
     *
     * Creates a new operand containing the sum of the two operands.
     * The result type is determined by the operand with higher precision.
     *
     * @param rhs The right-hand side operand to add
     * @return const IOperand* Pointer to a new operand containing the result
     * @throws OverflowException if the result exceeds the maximum value for the result type
     */
    virtual const IOperand* operator+(const IOperand& rhs) const = 0;

    /**
     * @brief Performs subtraction between this operand and another.
     *
     * Creates a new operand containing the difference (this - rhs).
     * The result type is determined by the operand with higher precision.
     *
     * @param rhs The right-hand side operand to subtract
     * @return const IOperand* Pointer to a new operand containing the result
     * @throws UnderflowException if the result is below the minimum value for the result type
     */
    virtual const IOperand* operator-(const IOperand& rhs) const = 0;

    /**
     * @brief Performs multiplication between this operand and another.
     *
     * Creates a new operand containing the product of the two operands.
     * The result type is determined by the operand with higher precision.
     *
     * @param rhs The right-hand side operand to multiply
     * @return const IOperand* Pointer to a new operand containing the result
     * @throws OverflowException if the result exceeds the maximum value for the result type
     */
    virtual const IOperand* operator*(const IOperand& rhs) const = 0;

    /**
     * @brief Performs division between this operand and another.
     *
     * Creates a new operand containing the quotient (this / rhs).
     * The result type is determined by the operand with higher precision.
     *
     * @param rhs The right-hand side operand (divisor)
     * @return const IOperand* Pointer to a new operand containing the result
     * @throws DivisionByZeroException if rhs is equal to zero
     * @throws UnderflowException if the result is below the minimum value for the result type
     */
    virtual const IOperand* operator/(const IOperand& rhs) const = 0;

    /**
     * @brief Performs modulo operation between this operand and another.
     *
     * Creates a new operand containing the remainder of the division (this % rhs).
     * The result type is determined by the operand with higher precision.
     *
     * @param rhs The right-hand side operand (divisor)
     * @return const IOperand* Pointer to a new operand containing the result
     * @throws DivisionByZeroException if rhs is equal to zero
     */
    virtual const IOperand* operator%(const IOperand& rhs) const = 0;

    /**
     * @brief Gets the string representation of this operand's value.
     *
     * Returns a string that represents the value stored in this operand.
     * The format depends on the operand type (e.g., "42" for integers, "3.14" for floats).
     *
     * @return const std::string& A reference to the string representation of the value
     */
    virtual const std::string& toString(void) const = 0;

    /**
     * @brief Virtual destructor for proper polymorphic deletion.
     *
     * Ensures that derived class destructors are called when deleting
     * through a pointer to IOperand.
     */
    virtual ~IOperand(void) {}
};

#endif // IOPERAND_HPP
