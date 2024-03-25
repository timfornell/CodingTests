# test_register.py

from Register import Register
from Operators import Add


def test_initialization():
   name = "TestName"
   register = Register(name)

   assert register.name == name
   assert register.current_value == 0.0
   assert not register.has_value
   assert register.stored_operations == []


def test_operation_storage():
   name = "TestName"
   register = Register(name)

   operation = Add()
   value = "200"

   register.AddOperation(operation, value)

   stored_operations = register.GetStoredOperations()

   assert len(stored_operations) == 1
   assert stored_operations[0]["operation"] == operation
   assert stored_operations[0]["value"] == value


def test_operation_clear():
   name = "TestName"
   register = Register(name)

   operation = Add()
   value = "200"

   register.AddOperation(operation, value)

   stored_operations = register.GetStoredOperations()

   assert len(stored_operations) == 1
   assert stored_operations[0]["operation"] == operation
   assert stored_operations[0]["value"] == value

   register.ClearStoredOperations()

   stored_operations = register.GetStoredOperations()

   assert len(stored_operations) == 0


def test_set_and_get_value():
   name = "TestName"
   register = Register(name)

   value = 200.0
   register.SetCurrentValue(value)
   register.InitializeRegister()

   assert register.IsInitialized()
   assert register.GetCurrentValue() == value  # float comparison is a bit risky...
