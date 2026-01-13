/**
 * @file AbstractVMException.hpp
 * @brief Defines the exception hierarchy for AbstractVM.
 */

#ifndef ABSTRACTVMEXCEPTION_HPP
#define ABSTRACTVMEXCEPTION_HPP

#include <exception>
#include <string>

/**
 * @class AbstractVMException
 * @brief Base exception class for all AbstractVM exceptions.
 *
 * All exception classes in AbstractVM must inherit from this base class,
 * which itself inherits from std::exception. This ensures proper exception
 * handling and follows the project requirements.
 *
 * ## Design Pattern
 * This class implements a hierarchy of exceptions following the standard
 * C++ exception handling mechanisms. Each derived exception provides
 * specific error information through the what() method.
 */
class AbstractVMException : public std::exception {
public:
    /**
     * @brief Constructor with error message.
     * @param message Description of the error that occurred
     */
    explicit AbstractVMException(const std::string& message);

    /**
     * @brief Gets the error message.
     * @return const char* C-string containing the error description
     */
    virtual const char* what() const noexcept override;

    /**
     * @brief Virtual destructor for proper polymorphic deletion.
     */
    virtual ~AbstractVMException() noexcept = default;

protected:
    std::string _message; ///< The error message string
};

/**
 * @class LexicalException
 * @brief Exception thrown when a lexical error is encountered during tokenization.
 *
 * This exception is thrown when the lexer encounters an invalid token or
 * character sequence that doesn't match any valid assembly language token.
 */
class LexicalException : public AbstractVMException {
public:
    explicit LexicalException(const std::string& message);
};

/**
 * @class SyntaxException
 * @brief Exception thrown when a syntax error is encountered during parsing.
 *
 * This exception is thrown when the parser encounters a sequence of tokens
 * that doesn't match the AbstractVM grammar rules.
 */
class SyntaxException : public AbstractVMException {
public:
    explicit SyntaxException(const std::string& message);
};

/**
 * @class OverflowException
 * @brief Exception thrown when an arithmetic operation results in overflow.
 *
 * This exception is thrown when the result of an arithmetic operation exceeds
 * the maximum representable value for the operand type.
 *
 * ## Example
 * ```cpp
 * // Int8 max value is 127
 * push int8(100)
 * push int8(50)
 * add  // Would throw OverflowException (150 > 127)
 * ```
 */
class OverflowException : public AbstractVMException {
public:
    explicit OverflowException(const std::string& message);
};

/**
 * @class UnderflowException
 * @brief Exception thrown when an arithmetic operation results in underflow.
 *
 * This exception is thrown when the result of an arithmetic operation is below
 * the minimum representable value for the operand type.
 *
 * ## Example
 * ```cpp
 * // Int8 min value is -128
 * push int8(-100)
 * push int8(50)
 * sub  // Would throw UnderflowException (-150 < -128)
 * ```
 */
class UnderflowException : public AbstractVMException {
public:
    explicit UnderflowException(const std::string& message);
};

/**
 * @class DivisionByZeroException
 * @brief Exception thrown when attempting to divide or modulo by zero.
 *
 * This exception is thrown when a division or modulo operation is attempted
 * with a divisor equal to zero.
 */
class DivisionByZeroException : public AbstractVMException {
public:
    explicit DivisionByZeroException(const std::string& message);
};

/**
 * @class EmptyStackException
 * @brief Exception thrown when attempting to pop from an empty stack.
 *
 * This exception is thrown when a pop operation or any operation requiring
 * values on the stack is executed while the stack is empty.
 */
class EmptyStackException : public AbstractVMException {
public:
    explicit EmptyStackException(const std::string& message);
};

/**
 * @class InsufficientValuesException
 * @brief Exception thrown when an operation requires more values than available.
 *
 * This exception is thrown when an arithmetic operation requires at least
 * two values on the stack, but fewer are available.
 */
class InsufficientValuesException : public AbstractVMException {
public:
    explicit InsufficientValuesException(const std::string& message);
};

/**
 * @class AssertException
 * @brief Exception thrown when an assert instruction fails.
 *
 * This exception is thrown when an assert instruction finds that the value
 * at the top of the stack doesn't match the expected value or type.
 */
class AssertException : public AbstractVMException {
public:
    explicit AssertException(const std::string& message);
};

/**
 * @class UnknownInstructionException
 * @brief Exception thrown when an unknown instruction is encountered.
 *
 * This exception is thrown when the parser encounters an instruction name
 * that is not recognized as a valid AbstractVM instruction.
 */
class UnknownInstructionException : public AbstractVMException {
public:
    explicit UnknownInstructionException(const std::string& message);
};

/**
 * @class NoExitException
 * @brief Exception thrown when the program terminates without an exit instruction.
 *
 * This exception is thrown when all instructions have been processed but
 * no exit instruction was encountered.
 */
class NoExitException : public AbstractVMException {
public:
    explicit NoExitException(const std::string& message);
};

#endif // ABSTRACTVMEXCEPTION_HPP
