Execution Engine
================

The VirtualMachine class is the core execution engine of AbstractVM.

VirtualMachine
--------------

.. doxygenclass:: VirtualMachine
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Architecture
------------

The VirtualMachine maintains:

- **Operand Stack**: A stack of ``const IOperand*`` for arithmetic operations
- **Command Queue**: Commands to be executed sequentially

Execution Flow
--------------

1. Input is read from file or stdin
2. Lexer tokenizes the input into tokens
3. Parser validates syntax and creates commands
4. VirtualMachine executes commands sequentially
5. Exit command terminates execution

Memory Management
-----------------

The VirtualMachine owns all operands on the stack and is responsible for
their cleanup. When operands are popped or the VM is destroyed, memory
is properly freed.

Usage Example
-------------

.. code-block:: cpp

   #include "VirtualMachine.hpp"

   int main() {
       VirtualMachine vm;

       // Run from file
       vm.runFile("program.avm");

       // Or run from stream
       vm.run(std::cin, true);  // true = interactive mode

       return 0;
   }
