/**
 * @file VirtualMachine.hpp
 * @brief Defines the VirtualMachine class - the core execution engine.
 */

#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include <stack>
#include <vector>
#include <memory>
#include <istream>
#include <string>
#include "IOperand.hpp"
#include "ICommand.hpp"

/**
 * @class VirtualMachine
 * @brief The main execution engine for AbstractVM programs.
 *
 * VirtualMachine is the core class that:
 * - Maintains the operand stack
 * - Orchestrates the lexing and parsing of input
 * - Executes commands in sequence
 * - Handles program termination
 * - Manages memory for operands on the stack
 *
 * ## Architecture
 *
 * The VM follows a classic stack-based architecture where:
 * - All operands are stored on a stack
 * - Operations pop values from the stack, compute results, and push back
 * - The stack contains pointers to IOperand for polymorphism
 *
 * ## Execution Flow
 *
 * 1. Read input (from file or stdin)
 * 2. Tokenize input using Lexer
 * 3. Parse tokens using Parser to generate commands
 * 4. Execute commands sequentially
 * 5. Verify exit instruction was present
 * 6. Clean up stack and exit
 *
 * ## Usage Example
 * ```cpp
 * VirtualMachine vm;
 * vm.run(std::cin, true);  // Run from stdin
 * ```
 *
 * ## Memory Management
 *
 * The VM is responsible for:
 * - Cleaning up all operands on the stack at termination
 * - Ensuring no memory leaks even when exceptions occur
 */
class VirtualMachine {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes the VM with an empty stack and default settings.
     */
    VirtualMachine();

    /**
     * @brief Destructor.
     *
     * Cleans up the stack and ensures all allocated operands are deleted.
     */
    ~VirtualMachine();

    /**
     * @brief Deleted copy constructor (non-copyable).
     */
    VirtualMachine(const VirtualMachine&) = delete;

    /**
     * @brief Deleted copy assignment operator (non-copyable).
     */
    VirtualMachine& operator=(const VirtualMachine&) = delete;

    /**
     * @brief Runs a program from an input stream.
     *
     * This is the main entry point for executing AbstractVM programs.
     * It handles the entire execution pipeline: lexing, parsing, and execution.
     *
     * @param input The input stream containing the program
     * @param fromStdin Flag indicating if input is from stdin (handles ";;" marker)
     * @throws AbstractVMException or derived exceptions on execution errors
     *
     * ## Example
     * ```cpp
     * std::ifstream file("program.avm");
     * VirtualMachine vm;
     * vm.run(file, false);
     * ```
     */
    void run(std::istream& input, bool fromStdin = false);

    /**
     * @brief Runs a program from a file path.
     *
     * Convenience method that opens a file and runs the program.
     *
     * @param filename Path to the file containing the program
     * @throws std::runtime_error if file cannot be opened
     * @throws AbstractVMException or derived exceptions on execution errors
     */
    void runFile(const std::string& filename);

    /**
     * @brief Gets the current size of the operand stack.
     * @return size_t Number of operands on the stack
     */
    size_t stackSize() const;

    /**
     * @brief Enables or disables verbose mode.
     * @param verbose If true, prints additional execution information
     */
    void setVerbose(bool verbose);

    /**
     * @brief Enables error collection mode (bonus feature).
     *
     * When enabled, the VM will collect all errors instead of stopping
     * at the first error encountered.
     *
     * @param collect If true, enables error collection
     */
    void setCollectErrors(bool collect);

    /**
     * @brief Signals that the exit command has been executed.
     *
     * This method is called by the ExitCommand to notify the VM
     * that program execution should terminate after the current command.
     */
    void setExitCalled();

private:
    std::stack<const IOperand*> _stack;     ///< The operand stack
    bool _exitCalled;                       ///< Flag indicating if exit was executed
    bool _verbose;                          ///< Verbose output flag
    bool _collectErrors;                    ///< Error collection mode flag

    /**
     * @brief Executes a vector of commands.
     *
     * Runs each command in sequence, stopping if exit is encountered.
     *
     * @param commands Vector of commands to execute
     * @throws AbstractVMException or derived exceptions on errors
     */
    void executeCommands(std::vector<std::unique_ptr<ICommand>>& commands);

    /**
     * @brief Cleans up the stack, deleting all operands.
     *
     * Called during destruction or after program completion.
     */
    void cleanupStack();

    /**
     * @brief Validates that the program ended with an exit instruction.
     * @throws NoExitException if exit was not called
     */
    void validateExit() const;
};

#endif // VIRTUALMACHINE_HPP
