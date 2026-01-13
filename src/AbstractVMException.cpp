/**
 * @file AbstractVMException.cpp
 * @brief Implementation of the AbstractVM exception hierarchy.
 */

#include "AbstractVMException.hpp"

// ============================================================================
// AbstractVMException (Base Class)
// ============================================================================

AbstractVMException::AbstractVMException(const std::string& message)
    : _message(message) {}

const char* AbstractVMException::what() const noexcept {
    return _message.c_str();
}

// ============================================================================
// Derived Exception Classes
// ============================================================================

LexicalException::LexicalException(const std::string& message)
    : AbstractVMException(message) {}

SyntaxException::SyntaxException(const std::string& message)
    : AbstractVMException(message) {}

OverflowException::OverflowException(const std::string& message)
    : AbstractVMException(message) {}

UnderflowException::UnderflowException(const std::string& message)
    : AbstractVMException(message) {}

DivisionByZeroException::DivisionByZeroException(const std::string& message)
    : AbstractVMException(message) {}

EmptyStackException::EmptyStackException(const std::string& message)
    : AbstractVMException(message) {}

InsufficientValuesException::InsufficientValuesException(const std::string& message)
    : AbstractVMException(message) {}

AssertException::AssertException(const std::string& message)
    : AbstractVMException(message) {}

UnknownInstructionException::UnknownInstructionException(const std::string& message)
    : AbstractVMException(message) {}

NoExitException::NoExitException(const std::string& message)
    : AbstractVMException(message) {}
