/**
 * @file ICommand.hpp
 * @brief Defines the ICommand interface for command pattern implementation.
 */

#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <stack>
#include <memory>
#include "IOperand.hpp"

/**
 * @interface ICommand
 * @brief Abstract interface for all VM instructions using the Command pattern.
 *
 * This interface implements the Command design pattern, where each instruction
 * is encapsulated as a command object that can be executed on the VM stack.
 *
 * ## Design Pattern: Command
 *
 * The Command pattern is used here to:
 * - Encapsulate each instruction as an object
 * - Provide a uniform interface for all instructions
 * - Enable easy addition of new instructions
 * - Separate instruction parsing from execution
 *
 * ## Usage Example
 * ```cpp
 * std::stack<const IOperand*> stack;
 * std::unique_ptr<ICommand> cmd = std::make_unique<PushCommand>(operand);
 * cmd->execute(stack);
 * ```
 */
class ICommand {
public:
    /**
     * @brief Executes the command on the given stack.
     *
     * Each concrete command implements this method to perform its
     * specific operation (push, pop, add, etc.) on the stack.
     *
     * @param stack Reference to the VM's operand stack
     * @throws AbstractVMException or derived exceptions on error
     */
    virtual void execute(std::stack<const IOperand*>& stack) = 0;

    /**
     * @brief Virtual destructor for proper polymorphic deletion.
     */
    virtual ~ICommand() = default;
};

#endif // ICOMMAND_HPP
