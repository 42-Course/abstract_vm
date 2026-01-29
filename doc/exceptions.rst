Exception Handling
==================

AbstractVM uses a hierarchy of exceptions for error handling.

Base Exception
--------------

.. doxygenclass:: AbstractVMException
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Exception Types
---------------

The following exception types are used throughout AbstractVM:

Lexer Exceptions
~~~~~~~~~~~~~~~~

- **Invalid character**: Unrecognized character in input
- **Unterminated value**: Missing closing parenthesis

Parser Exceptions
~~~~~~~~~~~~~~~~~

- **Syntax error**: Invalid token sequence
- **Unknown instruction**: Unrecognized command
- **Missing operand**: Command requires value but none provided
- **Missing exit**: Program doesn't end with exit instruction

Runtime Exceptions
~~~~~~~~~~~~~~~~~~

- **Stack underflow**: Operation requires more operands than available
- **Division by zero**: Attempted division or modulo by zero
- **Overflow**: Result exceeds type limits
- **Underflow**: Result below type minimum
- **Assert failed**: Assertion mismatch
- **Empty stack on print**: Print called with empty stack
- **Non-int8 on print**: Print called with non-int8 value
- **No exit instruction**: Program terminated without exit

Error Messages
--------------

All exceptions include:

- **Error type**: Category of the error
- **Line number**: Where the error occurred (when applicable)
- **Details**: Specific information about the error

Example
-------

.. code-block:: cpp

   try {
       VirtualMachine vm;
       vm.runFile("program.avm");
   } catch (const AbstractVMException& e) {
       std::cerr << "Error: " << e.what() << std::endl;
       return 1;
   }
