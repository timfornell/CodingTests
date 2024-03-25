# test_register.py

from Register import Register
from Operators import Add


def test_initialization():
   name = "TestName"
   register = Register()

   assert register.name == name
   assert register.current_value == 0.0
   assert register.has_value == False
   assert register.stored_operations == []


def test_operation_storage():
   name = "TestName"
   register = Register()

   register.Add