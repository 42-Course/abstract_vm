/**
 * @file OperandFactory.hpp
 * @brief Defines the OperandFactory class implementing the Factory design pattern.
 */

#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include <string>
#include <array>
#include "IOperand.hpp"
#include "eOperandType.hpp"

/**
 * @class OperandFactory
 * @brief Factory class responsible for creating IOperand instances.
 *
 * This class implements the Factory design pattern to create operand objects
 * of different types (Int8, Int16, Int32, Float, Double) from string values.
 *
 * ## Design Pattern: Factory Method
 *
 * The Factory pattern is used here to:
 * - Encapsulate object creation logic
 * - Provide a unified interface for creating different operand types
 * - Separate the creation logic from the usage of operands
 *
 * ## Implementation Details
 *
 * The factory uses an array of member function pointers indexed by eOperandType
 * values to efficiently dispatch to the appropriate creation method. This
 * approach is explicitly required by the project specification.
 *
 * ## Usage Example
 * ```cpp
 * OperandFactory factory;
 *
 * // Create an Int32 operand with value 42
 * const IOperand* op1 = factory.createOperand(eOperandType::Int32, "42");
 *
 * // Create a Float operand with value 3.14
 * const IOperand* op2 = factory.createOperand(eOperandType::Float, "3.14");
 *
 * // Use the operands
 * const IOperand* result = *op1 + *op2;
 *
 * // Clean up (caller is responsible for memory management)
 * delete op1;
 * delete op2;
 * delete result;
 * ```
 */
class OperandFactory {
public:
    /**
     * @brief Type definition for member function pointers.
     *
     * This defines the signature of the private creation methods.
     * Each method takes a string value and returns a pointer to IOperand.
     */
    using CreateFn = const IOperand* (OperandFactory::*)(const std::string&) const;

    /**
     * @brief Default constructor.
     */
    OperandFactory() = default;

    /**
     * @brief Deleted copy constructor (non-copyable).
     */
    OperandFactory(const OperandFactory&) = delete;

    /**
     * @brief Deleted copy assignment operator (non-copyable).
     */
    OperandFactory& operator=(const OperandFactory&) = delete;

    /**
     * @brief Creates a new operand of the specified type with the given value.
     *
     * This is the main factory method that delegates to the appropriate
     * private creation method based on the type parameter.
     *
     * @param type The type of operand to create (Int8, Int16, Int32, Float, or Double)
     * @param value String representation of the value
     * @return const IOperand* Pointer to the newly created operand
     * @throws OverflowException if the value exceeds the maximum for the type
     * @throws UnderflowException if the value is below the minimum for the type
     * @throws std::invalid_argument if the value string is malformed
     *
     * ## Example
     * ```cpp
     * OperandFactory factory;
     * const IOperand* op = factory.createOperand(eOperandType::Int8, "127");
     * ```
     */
    const IOperand* createOperand(eOperandType type, const std::string& value) const;

    /**
     * @brief Destructor.
     */
    ~OperandFactory() = default;

private:
    /**
     * @brief Creates an Int8 operand from a string value.
     *
     * @param value String representation of an 8-bit signed integer
     * @return const IOperand* Pointer to the created Int8 operand
     * @throws OverflowException if value > 127
     * @throws UnderflowException if value < -128
     */
    const IOperand* createInt8(const std::string& value) const;

    /**
     * @brief Creates an Int16 operand from a string value.
     *
     * @param value String representation of a 16-bit signed integer
     * @return const IOperand* Pointer to the created Int16 operand
     * @throws OverflowException if value > 32767
     * @throws UnderflowException if value < -32768
     */
    const IOperand* createInt16(const std::string& value) const;

    /**
     * @brief Creates an Int32 operand from a string value.
     *
     * @param value String representation of a 32-bit signed integer
     * @return const IOperand* Pointer to the created Int32 operand
     * @throws OverflowException if value > 2147483647
     * @throws UnderflowException if value < -2147483648
     */
    const IOperand* createInt32(const std::string& value) const;

    /**
     * @brief Creates a Float operand from a string value.
     *
     * @param value String representation of a single-precision floating-point number
     * @return const IOperand* Pointer to the created Float operand
     * @throws OverflowException if value exceeds float maximum
     * @throws UnderflowException if value is below float minimum
     */
    const IOperand* createFloat(const std::string& value) const;

    /**
     * @brief Creates a Double operand from a string value.
     *
     * @param value String representation of a double-precision floating-point number
     * @return const IOperand* Pointer to the created Double operand
     * @throws OverflowException if value exceeds double maximum
     * @throws UnderflowException if value is below double minimum
     */
    const IOperand* createDouble(const std::string& value) const;

    /**
     * @brief Static array of function pointers for operand creation.
     *
     * This array maps eOperandType enum values to their corresponding
     * creation methods. The index corresponds to the enum value.
     *
     * Being static, this array is shared by all OperandFactory instances
     * and initialized only once at program startup, improving efficiency
     * and following proper OOP design (class property, not instance property).
     *
     * This design is explicitly required by the project specification
     * to enable efficient type-based dispatching.
     */
    static const std::array<CreateFn, 5> _createFunctions;
};

#endif // OPERANDFACTORY_HPP
