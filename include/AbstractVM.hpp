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

#endif // ABSTRACTVM_HPP
