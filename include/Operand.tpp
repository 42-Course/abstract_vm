/**
 * @file Operand.hpp
 * @brief Defines the template Operand class for typed operand implementation.
 */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include <iomanip>
#include "IOperand.hpp"
#include "AbstractVMException.hpp"
#include "OperandFactory.hpp"

/**
 * @class Operand
 * @brief Template class implementing IOperand for specific numeric types.
 *
 * This template provides a concrete implementation of the IOperand interface
 * for various numeric types (int8_t, int16_t, int32_t, float, double).
 *
 * ## Template Approach
 *
 * Using a template reduces code duplication while maintaining type safety.
 * The template is specialized for each supported type through type aliases
 * (Int8, Int16, Int32, Float, Double).
 *
 * ## Design Considerations
 *
 * - **Value Storage**: Stores the value as both the native type and a string
 * - **Precision Handling**: Automatically determines result type for operations
 * - **Overflow/Underflow Detection**: Checks bounds before creating results
 * - **Memory Management**: All operators return dynamically allocated objects
 *
 * @tparam T The underlying numeric type (int8_t, int16_t, int32_t, float, or double)
 * @tparam Type The eOperandType enumeration value for this type
 */
template <typename T, eOperandType Type>
class Operand : public IOperand {
public:
    /**
     * @brief Constructor that creates an operand from a string value.
     *
     * Parses the string and validates that it fits within the bounds
     * of type T.
     *
     * @param value String representation of the numeric value
     * @throws OverflowException if value exceeds type maximum
     * @throws UnderflowException if value is below type minimum
     * @throws std::invalid_argument if string is malformed
     */
    explicit Operand(const std::string& value) {
        long double tempValue;

        try {
            tempValue = std::stold(value);
        } catch (const std::exception& e) {
            throw LexicalException("Invalid numeric string: " + value);
        }

        validateBounds(tempValue);
        _value = static_cast<T>(tempValue); // Safe after bounds check
        _strValue = valueToString(_value);
    }

    /**
     * @brief Copy constructor.
     * @param other The operand to copy from
     */
    Operand(const Operand& other) {
        _value = other._value;
        _strValue = other._strValue;
    }

    /**
     * @brief Copy assignment operator.
     * @param other The operand to assign from
     * @return Reference to this operand
     */
    Operand& operator=(const Operand& other) {
        if (this != &other) {
            _value = other._value;
            _strValue = other._strValue;
        }
        return *this;
    }

    /**
     * @brief Gets the precision level of this operand.
     * @return int The precision as an integer (0-4)
     */
    int getPrecision(void) const override {
        return static_cast<int>(Type);
    }

    /**
     * @brief Gets the type of this operand.
     * @return eOperandType The type enumeration value
     */
    eOperandType getType(void) const override {
        return Type;
    }

    /**
     * @brief Addition operator.
     * @param rhs Right-hand side operand
     * @return const IOperand* New operand containing the sum
     * @throws OverflowException on overflow
     */
    const IOperand* operator+(const IOperand& rhs) const override {
        eOperandType resultType = (getPrecision() >= rhs.getPrecision()) ? Type : rhs.getType();
        long double leftValue = static_cast<long double>(_value);
        long double rightValue = std::stold(rhs.toString());
        long double resultValue = leftValue + rightValue;

        OperandFactory factory;
        return factory.createOperand(resultType, std::to_string(resultValue));
    }

    /**
     * @brief Subtraction operator.
     * @param rhs Right-hand side operand
     * @return const IOperand* New operand containing the difference
     * @throws UnderflowException on underflow
     */
    const IOperand* operator-(const IOperand& rhs) const override {
        eOperandType resultType = (getPrecision() >= rhs.getPrecision()) ? Type : rhs.getType();
        long double leftValue = static_cast<long double>(_value);
        long double rightValue = std::stold(rhs.toString());
        long double resultValue = leftValue - rightValue;

        OperandFactory factory;
        return factory.createOperand(resultType, std::to_string(resultValue));
    }

    /**
     * @brief Multiplication operator.
     * @param rhs Right-hand side operand
     * @return const IOperand* New operand containing the product
     * @throws OverflowException on overflow
     */
    const IOperand* operator*(const IOperand& rhs) const override {
        eOperandType resultType = (getPrecision() >= rhs.getPrecision()) ? Type : rhs.getType();
        long double leftValue = static_cast<long double>(_value);
        long double rightValue = std::stold(rhs.toString());
        long double resultValue = leftValue * rightValue;

        OperandFactory factory;
        return factory.createOperand(resultType, std::to_string(resultValue));
    }

    /**
     * @brief Division operator.
     * @param rhs Right-hand side operand (divisor)
     * @return const IOperand* New operand containing the quotient
     * @throws DivisionByZeroException if divisor is zero
     */
    const IOperand* operator/(const IOperand& rhs) const override {
        long double rightValue = std::stold(rhs.toString());
        if (rightValue == 0.0) {
            throw DivisionByZeroException("Division by zero error.");
        }

        eOperandType resultType = (getPrecision() >= rhs.getPrecision()) ? Type : rhs.getType();
        long double leftValue = static_cast<long double>(_value);
        long double resultValue = leftValue / rightValue;

        OperandFactory factory;
        return factory.createOperand(resultType, std::to_string(resultValue));
    }

    /**
     * @brief Modulo operator.
     * @param rhs Right-hand side operand (divisor)
     * @return const IOperand* New operand containing the remainder
     * @throws DivisionByZeroException if divisor is zero
     */
    const IOperand* operator%(const IOperand& rhs) const override {
        long double rightValue = std::stold(rhs.toString());
        if (rightValue == 0.0) {
            throw DivisionByZeroException("Division by zero error.");
        }

        eOperandType resultType = (getPrecision() >= rhs.getPrecision()) ? Type : rhs.getType();
        long double leftValue = static_cast<long double>(_value);
        long double resultValue = fmodl(leftValue, rightValue);

        OperandFactory factory;
        return factory.createOperand(resultType, std::to_string(resultValue));
    }

    /**
     * @brief Gets the string representation of this operand's value.
     * @return const std::string& Reference to the value string
     */
    const std::string& toString(void) const override {
        return _strValue;
    }

    /**
     * @brief Destructor.
     */
    ~Operand() override = default;

private:
    T _value;               ///< The numeric value stored in native type
    std::string _strValue;  ///< String representation of the value

    /**
     * @brief Validates that a long double value fits within type T bounds.
     * @param value The value to validate
     * @throws OverflowException if value is too large
     * @throws UnderflowException if value is too small
     */
    void validateBounds(long double value) const {
        long double typeMin = static_cast<long double>(std::numeric_limits<T>::lowest());
        long double typeMax = static_cast<long double>(std::numeric_limits<T>::max());

        if (value < typeMin) {
            throw UnderflowException("Underflow: Value " + std::to_string(value) +
                                     " is below minimum for type.");
        }
        if (value > typeMax) {
            throw OverflowException("Overflow: Value " + std::to_string(value) +
                                    " exceeds maximum for type.");
        }
    }

    /**
     * @brief Converts the value to a properly formatted string.
     * @param value The value to convert
     * @return std::string The formatted string
     */
    std::string valueToString(T value) const {
        std::ostringstream oss;
        if (Type == eOperandType::Float || Type == eOperandType::Double) {
            oss << std::setprecision(std::numeric_limits<T>::digits10 + 1) << value;
        } else {
            oss << static_cast<int64_t>(value);
        }
        return oss.str();   
    }
};

#endif // OPERAND_HPP
