#include "AbstractVM.hpp"
#include <iostream>
#include <functional>

namespace {
    /**
     * @brief Helper function to perform binary operations on the stack.
     *
     * This function encapsulates the common logic for all binary arithmetic operations:
     * - Validates that at least 2 values are on the stack
     * - Pops the two top values
     * - Performs the operation
     * - Cleans up operands
     * - Pushes the result back onto the stack
     *
     * @param stack The VM stack
     * @param operation The binary operation to perform (as a function)
     * @param opName The name of the operation (for error messages)
     * @throws InsufficientValuesException if stack has fewer than 2 values
     */
    void performBinaryOperation(
        std::stack<const IOperand*>& stack,
        std::function<const IOperand*(const IOperand&, const IOperand&)> operation,
        const std::string& opName)
    {
        if (stack.size() < 2) {
            throw InsufficientValuesException(opName + " requires at least 2 values on stack");
        }

        // Pop two operands (v2 on top, v1 below)
        const IOperand* v2 = stack.top();
        stack.pop();
        const IOperand* v1 = stack.top();
        stack.pop();

        // Perform operation
        const IOperand* result = operation(*v1, *v2);

        // Clean up operands
        delete v1;
        delete v2;

        // Push result
        stack.push(result);
    }
}

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

void PopCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.empty()) {
        throw EmptyStackException("Pop on empty stack");
    }

    const IOperand* top = stack.top();
    stack.pop();
    delete top; // Clean up the operand
}

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
                             std::string(operandTypeToString(_expected->getType())) +
                             " but got " +
                             std::string(operandTypeToString(top->getType())));
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

void AddCommand::execute(std::stack<const IOperand*>& stack) {
    performBinaryOperation(stack, [](const IOperand& v1, const IOperand& v2) {
        return v1 + v2;
    }, "Add");
}

void SubCommand::execute(std::stack<const IOperand*>& stack) {
    performBinaryOperation(stack, [](const IOperand& v1, const IOperand& v2) {
        return v1 - v2;
    }, "Sub");
}

void MulCommand::execute(std::stack<const IOperand*>& stack) {
    performBinaryOperation(stack, [](const IOperand& v1, const IOperand& v2) {
        return v1 * v2;
    }, "Mul");
}

void DivCommand::execute(std::stack<const IOperand*>& stack) {
    performBinaryOperation(stack, [](const IOperand& v1, const IOperand& v2) {
        return v1 / v2;
    }, "Div");
}

void ModCommand::execute(std::stack<const IOperand*>& stack) {
    performBinaryOperation(stack, [](const IOperand& v1, const IOperand& v2) {
        return v1 % v2;
    }, "Mod");
}

void PrintCommand::execute(std::stack<const IOperand*>& stack) {
    if (stack.empty()) {
        throw EmptyStackException("Print on empty stack");
    }

    const IOperand* top = stack.top();

    // Assert that the value is an Int8
    if (top->getType() != eOperandType::Int8) {
        throw AssertException("Print requires int8 value on top of stack, but got " +
                             std::string(operandTypeToString(top->getType())));
    }

    // Get the value and interpret as ASCII
    int value = std::stoi(top->toString());

    // Print as character
    std::cout << static_cast<char>(value);// << std::endl;
}

ExitCommand::ExitCommand(VirtualMachine* vm)
    : _vm(vm) {}

void ExitCommand::execute(std::stack<const IOperand*>& stack) {
    (void)stack; // Unused parameter
    // Signal the VM that exit has been called
    if (_vm) {
        _vm->setExitCalled();
    }
}
