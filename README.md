# AbstractVM

A stack-based virtual machine that interprets simple arithmetic programs written in a basic assembly language.

## Project Overview

AbstractVM is a C++20 implementation of a simple virtual machine capable of executing assembly-like programs. It features a stack-based architecture with five operand types and supports basic arithmetic operations with automatic type precision handling.

## Features

- **Five Operand Types**: Int8, Int16, Int32, Float, Double
- **Stack-Based Architecture**: All operations manipulate a stack
- **Type Precision System**: Operations preserve the highest precision type
- **Comprehensive Error Handling**: Overflow, underflow, division by zero, and more
- **Factory Design Pattern**: Operand creation through factory
- **Command Design Pattern**: Instructions as executable objects
- **Lexer/Parser**: Structured lexical and syntactic analysis
- **Doxygen Documentation**: Extensive inline documentation

### Running from standard input

```bash
./avm
push int32(42)
push int32(33)
add
dump
exit
;;
```

The `;;` marker indicates the end of the program when reading from stdin.

## Assembly Language

### Example Program

```assembly
; Example program
push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
dump
pop
assert double(42.42)
exit
```

### Instructions

- `push <value>` - Push a value onto the stack
- `pop` - Remove the top value from the stack
- `dump` - Display all stack values (most recent first)
- `assert <value>` - Assert the top value matches the given value
- `add` - Add the top two values
- `sub` - Subtract the top two values
- `mul` - Multiply the top two values
- `div` - Divide the top two values
- `mod` - Calculate modulo of the top two values
- `print` - Print the top value as an ASCII character (must be Int8)
- `exit` - Terminate the program

### Value Types

- `int8(n)` - 8-bit signed integer
- `int16(n)` - 16-bit signed integer
- `int32(n)` - 32-bit signed integer
- `float(z)` - Single-precision floating-point
- `double(z)` - Double-precision floating-point

## Architecture

### Core Components

1. **IOperand Interface**: Abstract interface for all operand types
2. **Operand<T> Template**: Generic operand implementation
3. **OperandFactory**: Creates operands using the Factory pattern
4. **ICommand Interface**: Abstract interface for all instructions
5. **Command Classes**: Concrete implementations of each instruction
6. **Lexer**: Tokenizes input into tokens
7. **Parser**: Validates syntax and generates commands
8. **VirtualMachine**: Main execution engine

### Design Patterns

- **Factory Pattern**: Used for operand creation
- **Command Pattern**: Used for instruction encapsulation
- **Template Method**: Used in operand implementation
- **Interface Segregation**: Clean separation of concerns

## Documentation

Full documentation is generated using Doxygen and Sphinx:

```bash
make html
```

Then open `doc/_build/html/index.html` in your browser.