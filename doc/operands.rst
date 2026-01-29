Operand System
==============

The operand system defines the type hierarchy and arithmetic capabilities of AbstractVM.

Interface
---------

.. doxygeninterface:: IOperand
   :project: AbstractVM
   :members:
   :protected-members:
   :undoc-members:

Factory
-------

.. doxygenclass:: OperandFactory
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Type Enumeration
----------------

.. doxygenenum:: eOperandType
   :project: AbstractVM

Template Implementation
-----------------------

The ``Operand<T, Type>`` template class provides the concrete implementation
of the IOperand interface for all numeric types. Each concrete type is a
type alias to a specific template instantiation.

.. doxygenfile:: Operand.tpp
   :project: AbstractVM

Type Aliases
------------

Int8
~~~~

.. doxygentypedef:: Int8
   :project: AbstractVM

Int16
~~~~~

.. doxygentypedef:: Int16
   :project: AbstractVM

Int32
~~~~~

.. doxygentypedef:: Int32
   :project: AbstractVM

Float
~~~~~

.. doxygentypedef:: Float
   :project: AbstractVM

Double
~~~~~~

.. doxygentypedef:: Double
   :project: AbstractVM
