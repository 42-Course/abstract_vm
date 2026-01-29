Parsing System
==============

The parsing system converts source text into executable commands.

Lexer
-----

.. doxygenclass:: Lexer
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Parser
------

.. doxygenclass:: Parser
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Token
-----

.. doxygenclass:: Token
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Token Types
~~~~~~~~~~~

.. doxygenenum:: TokenType
   :project: AbstractVM

Parsing Flow
------------

1. **Lexical Analysis** (Lexer)

   - Reads source character by character
   - Groups characters into tokens
   - Handles comments (lines starting with ``;``)
   - Recognizes keywords, types, values, and operators

2. **Syntax Analysis** (Parser)

   - Validates token sequences
   - Ensures correct grammar
   - Creates appropriate Command objects
   - Reports syntax errors with line numbers

Grammar
-------

The AbstractVM assembly language follows this grammar:

.. code-block:: text

   program    := instruction* EOF
   instruction := operation EOL
   operation  := push | pop | dump | assert | add | sub | mul | div | mod | print | exit | clear
   push       := "push" value
   assert     := "assert" value
   value      := type "(" number ")"
   type       := "int8" | "int16" | "int32" | "float" | "double"
   number     := [-]?[0-9]+ | [-]?[0-9]+.[0-9]+

Example
-------

.. code-block:: text

   ; This is a comment
   push int32(42)    ; Push 42 as int32
   push int32(33)    ; Push 33 as int32
   add               ; Add top two values
   dump              ; Display stack
   exit              ; End execution
