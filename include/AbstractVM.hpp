/**
 * @file AbstractVM.hpp
 * @brief Main header file that includes all AbstractVM components.
 *
 * This convenience header can be included to get access to all
 * AbstractVM classes and interfaces.
 */

#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

// Core interfaces
#include "IOperand.hpp"
#include "ICommand.hpp"

// Type system
#include "eOperandType.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"

// Factory
#include "OperandFactory.hpp"

// Commands
#include "Commands.hpp"

// Execution engine
#include "VirtualMachine.hpp"

// Parsing
#include "Token.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

// Exceptions
#include "AbstractVMException.hpp"

/**
 * @mainpage AbstractVM Documentation
 *
 * @section intro_sec Introduction
 *
 * AbstractVM is a stack-based virtual machine that interprets programs written
 * in a simple assembly language. It performs arithmetic operations on a stack
 * of typed operands.
 *
 * @section features_sec Key Features
 *
 * - **Five operand types**: Int8, Int16, Int32, Float, Double
 * - **Stack-based architecture**: All operations work on a stack
 * - **Type precision**: Operations preserve the highest precision type
 * - **Complete error handling**: Overflow, underflow, division by zero, etc.
 * - **Assembly language**: Simple, readable instruction set
 * - **Factory pattern**: Operand creation through factory
 * - **Command pattern**: Instructions as executable objects
 *
 * @section arch_sec Architecture
 *
 * The VM consists of several key components:
 *
 * ### Operand System
 * - IOperand: Interface for all operand types
 * - Operand<T>: Template implementation
 * - Concrete types: Int8, Int16, Int32, Float, Double
 * - OperandFactory: Creates operands using Factory pattern
 *
 * ### Command System
 * - ICommand: Interface for all instructions
 * - Concrete commands: Push, Pop, Add, Sub, Mul, Div, Mod, etc.
 *
 * ### Parsing System
 * - Lexer: Tokenizes input into tokens
 * - Parser: Validates syntax and creates commands
 * - Token: Represents a lexical unit
 *
 * ### Execution
 * - VirtualMachine: Main execution engine
 * - Maintains the operand stack
 * - Executes commands sequentially
 *
 * @section usage_sec Usage Example
 *
 * ```cpp
 * #include "AbstractVM.hpp"
 *
 * int main(int argc, char** argv) {
 *     VirtualMachine vm;
 *
 *     if (argc == 2) {
 *         // Run from file
 *         vm.runFile(argv[1]);
 *     } else {
 *         // Run from stdin
 *         vm.run(std::cin, true);
 *     }
 *
 *     return 0;
 * }
 * ```
 *
 * @section assembly_sec Assembly Language
 *
 * Example program:
 * ```
 * push int32(42)
 * push int32(33)
 * add
 * push float(44.55)
 * mul
 * dump
 * exit
 * ```
 *
 * @section author_sec Author
 * pulgamecanica - 2026
 *
 * @section license_sec License
 * 42 School Project - Educational Use
 */

#endif // ABSTRACTVM_HPP
