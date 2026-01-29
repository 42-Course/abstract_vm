Command System
==============

The command system implements the instruction set using the Command pattern.

Interface
---------

.. doxygeninterface:: ICommand
   :project: AbstractVM
   :members:
   :protected-members:
   :undoc-members:

Stack Operations
----------------

PushCommand
~~~~~~~~~~~

.. doxygenclass:: PushCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

PopCommand
~~~~~~~~~~

.. doxygenclass:: PopCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

DumpCommand
~~~~~~~~~~~

.. doxygenclass:: DumpCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Arithmetic Operations
---------------------

AddCommand
~~~~~~~~~~

.. doxygenclass:: AddCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

SubCommand
~~~~~~~~~~

.. doxygenclass:: SubCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

MulCommand
~~~~~~~~~~

.. doxygenclass:: MulCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

DivCommand
~~~~~~~~~~

.. doxygenclass:: DivCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

ModCommand
~~~~~~~~~~

.. doxygenclass:: ModCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

Control Operations
------------------

AssertCommand
~~~~~~~~~~~~~

.. doxygenclass:: AssertCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

PrintCommand
~~~~~~~~~~~~

.. doxygenclass:: PrintCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:

ExitCommand
~~~~~~~~~~~

.. doxygenclass:: ExitCommand
   :project: AbstractVM
   :members:
   :private-members:
   :protected-members:
   :undoc-members:
