/**
 * @file Commands.hpp
 * @brief Defines all concrete command classes for AbstractVM instructions.
 */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <memory>
#include "ICommand.hpp"
#include "IOperand.hpp"
#include "AbstractVMException.hpp"

/**
 * @class PushCommand
 * @brief Command that pushes a value onto the stack.
 *
 * Implements the 'push' instruction which adds a new operand
 * to the top of the stack.
 *
 * ## Assembly Syntax
 * ```
 * push int32(42)
 * push float(3.14)
 * ```
 */
class PushCommand : public ICommand {
public:
    /**
     * @brief Constructor with operand to push.
     * @param operand Pointer to the operand to push (takes ownership)
     */
    explicit PushCommand(const IOperand* operand);

    /**
     * @brief Executes the push operation.
     * @param stack The VM stack
     */
    void execute(std::stack<const IOperand*>& stack) override;

    /**
     * @brief Destructor that cleans up the operand if not pushed.
     */
    ~PushCommand() override;

private:
    const IOperand* _operand; ///< The operand to push
};

/**
 * @class PopCommand
 * @brief Command that removes the top value from the stack.
 *
 * Implements the 'pop' instruction which removes and deletes
 * the operand at the top of the stack.
 *
 * ## Assembly Syntax
 * ```
 * pop
 * ```
 *
 * @throws EmptyStackException if the stack is empty
 */
class PopCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    PopCommand() = default;

    /**
     * @brief Executes the pop operation.
     * @param stack The VM stack
     * @throws EmptyStackException if stack is empty
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class DumpCommand
 * @brief Command that displays all stack values without modifying the stack.
 *
 * Implements the 'dump' instruction which prints each value on the stack
 * from most recent to oldest, separated by newlines.
 *
 * ## Assembly Syntax
 * ```
 * dump
 * ```
 */
class DumpCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    DumpCommand() = default;

    /**
     * @brief Executes the dump operation.
     * @param stack The VM stack
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class AssertCommand
 * @brief Command that verifies the top stack value matches an expected value.
 *
 * Implements the 'assert' instruction which checks that the top of the stack
 * has the same type and value as the provided operand.
 *
 * ## Assembly Syntax
 * ```
 * assert int32(42)
 * assert double(3.14)
 * ```
 *
 * @throws AssertException if the assertion fails
 * @throws EmptyStackException if the stack is empty
 */
class AssertCommand : public ICommand {
public:
    /**
     * @brief Constructor with operand to assert against.
     * @param operand Pointer to the expected operand (takes ownership)
     */
    explicit AssertCommand(const IOperand* operand);

    /**
     * @brief Executes the assert operation.
     * @param stack The VM stack
     * @throws AssertException if values don't match
     * @throws EmptyStackException if stack is empty
     */
    void execute(std::stack<const IOperand*>& stack) override;

    /**
     * @brief Destructor.
     */
    ~AssertCommand() override;

private:
    const IOperand* _expected; ///< The expected operand value
};

/**
 * @class AddCommand
 * @brief Command that adds the top two stack values.
 *
 * Implements the 'add' instruction which pops two values,
 * adds them, and pushes the result.
 *
 * ## Assembly Syntax
 * ```
 * add
 * ```
 *
 * @throws InsufficientValuesException if stack has fewer than 2 values
 * @throws OverflowException if result overflows
 */
class AddCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    AddCommand() = default;

    /**
     * @brief Executes the add operation.
     * @param stack The VM stack
     * @throws InsufficientValuesException if fewer than 2 values on stack
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class SubCommand
 * @brief Command that subtracts the top two stack values.
 *
 * Implements the 'sub' instruction. For stack [v1, v2] where v2 is on top,
 * computes v1 - v2 and pushes the result.
 *
 * ## Assembly Syntax
 * ```
 * sub
 * ```
 *
 * @throws InsufficientValuesException if stack has fewer than 2 values
 * @throws UnderflowException if result underflows
 */
class SubCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    SubCommand() = default;

    /**
     * @brief Executes the sub operation.
     * @param stack The VM stack
     * @throws InsufficientValuesException if fewer than 2 values on stack
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class MulCommand
 * @brief Command that multiplies the top two stack values.
 *
 * Implements the 'mul' instruction which pops two values,
 * multiplies them, and pushes the result.
 *
 * ## Assembly Syntax
 * ```
 * mul
 * ```
 *
 * @throws InsufficientValuesException if stack has fewer than 2 values
 * @throws OverflowException if result overflows
 */
class MulCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    MulCommand() = default;

    /**
     * @brief Executes the mul operation.
     * @param stack The VM stack
     * @throws InsufficientValuesException if fewer than 2 values on stack
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class DivCommand
 * @brief Command that divides the top two stack values.
 *
 * Implements the 'div' instruction. For stack [v1, v2] where v2 is on top,
 * computes v1 / v2 and pushes the result.
 *
 * ## Assembly Syntax
 * ```
 * div
 * ```
 *
 * @throws InsufficientValuesException if stack has fewer than 2 values
 * @throws DivisionByZeroException if divisor is zero
 */
class DivCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    DivCommand() = default;

    /**
     * @brief Executes the div operation.
     * @param stack The VM stack
     * @throws InsufficientValuesException if fewer than 2 values on stack
     * @throws DivisionByZeroException if divisor is zero
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class ModCommand
 * @brief Command that computes modulo of the top two stack values.
 *
 * Implements the 'mod' instruction. For stack [v1, v2] where v2 is on top,
 * computes v1 % v2 and pushes the result.
 *
 * ## Assembly Syntax
 * ```
 * mod
 * ```
 *
 * @throws InsufficientValuesException if stack has fewer than 2 values
 * @throws DivisionByZeroException if divisor is zero
 */
class ModCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    ModCommand() = default;

    /**
     * @brief Executes the mod operation.
     * @param stack The VM stack
     * @throws InsufficientValuesException if fewer than 2 values on stack
     * @throws DivisionByZeroException if divisor is zero
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class PrintCommand
 * @brief Command that prints the top stack value as an ASCII character.
 *
 * Implements the 'print' instruction which asserts that the top value
 * is an Int8, then interprets it as an ASCII character and prints it.
 *
 * ## Assembly Syntax
 * ```
 * print
 * ```
 *
 * @throws AssertException if top value is not Int8
 * @throws EmptyStackException if stack is empty
 */
class PrintCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    PrintCommand() = default;

    /**
     * @brief Executes the print operation.
     * @param stack The VM stack
     * @throws AssertException if top is not Int8
     * @throws EmptyStackException if stack is empty
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

/**
 * @class ExitCommand
 * @brief Command that terminates program execution.
 *
 * Implements the 'exit' instruction which cleanly terminates the VM.
 * This instruction must appear in every valid AbstractVM program.
 *
 * ## Assembly Syntax
 * ```
 * exit
 * ```
 */
class ExitCommand : public ICommand {
public:
    /**
     * @brief Default constructor.
     */
    ExitCommand() = default;

    /**
     * @brief Executes the exit operation.
     * @param stack The VM stack
     */
    void execute(std::stack<const IOperand*>& stack) override;
};

#endif // COMMANDS_HPP
