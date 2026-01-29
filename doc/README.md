# AbstractVM

AbstractVM is a stack-based virtual machine that interprets programs written in a simple assembly language. It performs arithmetic operations on a stack of typed operands.

## Architecture

The VM consists of several key components:

### Operand System
- **IOperand**: Interface for all operand types
- **Operand<T>**: Template implementation
- **Concrete types**: Int8, Int16, Int32, Float, Double
- **OperandFactory**: Creates operands using Factory pattern

### Command System
- **ICommand**: Interface for all instructions
- **Concrete commands**: Push, Pop, Add, Sub, Mul, Div, Mod, Print, Dump, Assert, Exit

### Parsing System
- **Lexer**: Tokenizes input into tokens
- **Parser**: Validates syntax and creates commands
- **Token**: Represents a lexical unit

### Execution
- **VirtualMachine**: Main execution engine that maintains the operand stack and executes commands sequentially

## Type System

AbstractVM supports five operand types with a precision hierarchy:

| Type | Precision | Range |
|------|-----------|-------|
| Int8 | 0 | -128 to 127 |
| Int16 | 1 | -32768 to 32767 |
| Int32 | 2 | -2147483648 to 2147483647 |
| Float | 3 | IEEE 754 single precision |
| Double | 4 | IEEE 754 double precision |

When performing arithmetic operations, the result takes the type with higher precision.

## Assembly Language

### Stack Operations
- `push TYPE(VALUE)` - Push a value onto the stack
- `pop` - Remove the top value from the stack
- `dump` - Display all stack values
- `clear` - Clear the entire stack

### Arithmetic Operations
- `add` - Add top two values
- `sub` - Subtract top from second
- `mul` - Multiply top two values
- `div` - Divide second by top
- `mod` - Modulo second by top

### Control Operations
- `assert TYPE(VALUE)` - Assert top value equals given value
- `print` - Print top value as ASCII character
- `exit` - Terminate execution

### Comments
- Lines starting with `;` are comments
- Inline comments are supported after instructions

## Building

```bash
make        # Build the project
make clean  # Clean object files
make fclean # Clean everything
make re     # Rebuild
```

## Documentation

```bash
make html   # Generate HTML documentation
```

The documentation will be generated in `doc/_build/html/`.

## Usage

```bash
# Run from file
./avm program.avm

# Run from stdin (end with ;; on a new line)
./avm
push int32(42)
push int32(33)
add
dump
exit
;;
```

## Author

pulgamecanica - 2026

## License

42 School Project - Educational Use
