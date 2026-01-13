#include "AbstractVM.hpp"
#include <iostream>

// ============================================================================
// PushCommand
// ============================================================================

PushCommand::PushCommand(const IOperand* operand)
    : _operand(operand) {}

void PushCommand::execute(std::stack<const IOperand*>& stack) {
    stack.push(_operand);
    _operand = nullptr; // Transfer ownership to stack
}

PushCommand::~PushCommand() {
    // Clean up if operand wasn't pushed (error occurred)
    delete _operand;
}

// ============================================================================
// PopCommand
// ============================================================================

void PopCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.empty()) {
        throw EmptyStackException("Pop on empty stack");
    }

    const IOperand* top = stack.top();
    stack.pop();
    delete top; // Clean up the operand
}

// ============================================================================
// DumpCommand
// ============================================================================

void DumpCommand::execute(std::stack<const IOperand*>& stack) {
    // Create a temporary stack to preserve order
    std::stack<const IOperand*> temp;

    // Move all elements to temp (reverses order)
    while (!stack.empty()) {
        temp.push(stack.top());
        stack.pop();
    }

    // Print and restore (now in correct order: most recent first)
    while (!temp.empty()) {
        const IOperand* op = temp.top();
        std::cout << op->toString() << std::endl;
        stack.push(op);
        temp.pop();
    }
}

// ============================================================================
// AssertCommand
// ============================================================================

AssertCommand::AssertCommand(const IOperand* operand)
    : _expected(operand) {}

void AssertCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.empty()) {
        throw EmptyStackException("Assert on empty stack");
    }

    const IOperand* top = stack.top();

    // Check type
    if (top->getType() != _expected->getType()) {
        throw AssertException("Assert failed: type mismatch. Expected " +
                             std::to_string(static_cast<int>(_expected->getType())) +
                             " but got " +
                             std::to_string(static_cast<int>(top->getType())));
    }

    // Check value
    if (top->toString() != _expected->toString()) {
        throw AssertException("Assert failed: value mismatch. Expected " +
                             _expected->toString() + " but got " + top->toString());
    }

    // Assert passed - do nothing to the stack
}

AssertCommand::~AssertCommand() {
    delete _expected;
}

// ============================================================================
// AddCommand
// ============================================================================

void AddCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.size() < 2) {
        throw InsufficientValuesException("Add requires at least 2 values on stack");
    }

    // Pop two operands
    const IOperand* v2 = stack.top();
    stack.pop();
    const IOperand* v1 = stack.top();
    stack.pop();

    // Perform addition
    const IOperand* result = *v1 + *v2;

    // Clean up operands
    delete v1;
    delete v2;

    // Push result
    stack.push(result);
}

// ============================================================================
// SubCommand
// ============================================================================

void SubCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.size() < 2) {
        throw InsufficientValuesException("Sub requires at least 2 values on stack");
    }

    // Pop two operands (v2 on top, v1 below)
    const IOperand* v2 = stack.top();
    stack.pop();
    const IOperand* v1 = stack.top();
    stack.pop();

    // Perform subtraction: v1 - v2
    const IOperand* result = *v1 - *v2;

    // Clean up operands
    delete v1;
    delete v2;

    // Push result
    stack.push(result);
}

// ============================================================================
// MulCommand
// ============================================================================

void MulCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.size() < 2) {
        throw InsufficientValuesException("Mul requires at least 2 values on stack");
    }

    // Pop two operands
    const IOperand* v2 = stack.top();
    stack.pop();
    const IOperand* v1 = stack.top();
    stack.pop();

    // Perform multiplication
    const IOperand* result = *v1 * *v2;

    // Clean up operands
    delete v1;
    delete v2;

    // Push result
    stack.push(result);
}

// ============================================================================
// DivCommand
// ============================================================================

void DivCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.size() < 2) {
        throw InsufficientValuesException("Div requires at least 2 values on stack");
    }

    // Pop two operands (v2 on top, v1 below)
    const IOperand* v2 = stack.top();
    stack.pop();
    const IOperand* v1 = stack.top();
    stack.pop();

    // Perform division: v1 / v2
    // Division by zero is checked inside the operator
    const IOperand* result = *v1 / *v2;

    // Clean up operands
    delete v1;
    delete v2;

    // Push result
    stack.push(result);
}

// ============================================================================
// ModCommand
// ============================================================================

void ModCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.size() < 2) {
        throw InsufficientValuesException("Mod requires at least 2 values on stack");
    }

    // Pop two operands (v2 on top, v1 below)
    const IOperand* v2 = stack.top();
    stack.pop();
    const IOperand* v1 = stack.top();
    stack.pop();

    // Perform modulo: v1 % v2
    // Division by zero is checked inside the operator
    const IOperand* result = *v1 % *v2;

    // Clean up operands
    delete v1;
    delete v2;

    // Push result
    stack.push(result);
}

// ============================================================================
// PrintCommand
// ============================================================================

void PrintCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.empty()) {
        throw EmptyStackException("Print on empty stack");
    }

    const IOperand* top = stack.top();

    // Assert that the value is an Int8
    if (top->getType() != eOperandType::Int8) {
        throw AssertException("Print requires Int8 value on top of stack");
    }

    // Get the value and interpret as ASCII
    int value = std::stoi(top->toString());

    // Print as character
    std::cout << static_cast<char>(value) << std::endl;
}

// ============================================================================
// ExitCommand
// ============================================================================

void ExitCommand::execute(std::stack<const IOperand*>& stack) {
    (void)stack; // Unused parameter
    // Exit command doesn't modify the stack
    // The VM will handle actual program termination
}
