.. AbstractVM documentation master file, created by
   sphinx-quickstart.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

AbstractVM Documentation
========================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   README.md
   operands
   commands
   execution
   parsing
   exceptions

Welcome to the AbstractVM documentation. AbstractVM is a stack-based virtual
machine that interprets programs written in a simple assembly language.

Key Features
------------

- **Five operand types**: Int8, Int16, Int32, Float, Double
- **Stack-based architecture**: All operations work on a stack
- **Type precision**: Operations preserve the highest precision type
- **Complete error handling**: Overflow, underflow, division by zero, etc.
- **Assembly language**: Simple, readable instruction set
- **Factory pattern**: Operand creation through factory
- **Command pattern**: Instructions as executable objects

Quick Start
-----------

.. code-block:: cpp

   #include "AbstractVM.hpp"

   int main(int argc, char** argv) {
       VirtualMachine vm;

       if (argc == 2) {
           // Run from file
           vm.runFile(argv[1]);
       } else {
           // Run from stdin
           vm.run(std::cin, true);
       }

       return 0;
   }

Example Program
---------------

.. code-block:: text

   push int32(42)
   push int32(33)
   add
   push float(44.55)
   mul
   dump
   exit
