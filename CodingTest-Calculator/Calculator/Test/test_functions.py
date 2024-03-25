# test_functions.py

from Register import Register
from Functions import Print, Clear
from Operators import Add


def test_print(capsys):
   name = "TestName"
   register = Register(name)
   register.SetCurrentValue(200)
   register.InitializeRegister()

   print_obj = Print()

   print_obj.Evaluate(register.GetCurrentValue())

   captured = capsys.readouterr()
   captured_output = captured.out.rstrip()

   assert str(print_obj) == "print"
   assert captured_output == "Output: 200"


def test_clear():
   name = "TestName"
   register = Register(name)
   operator = Add()
   value = 200

   clear = Clear()

   register.AddOperation(operator, value)

   operations = register.GetStoredOperations()
   assert len(operations) == 1

   clear.Evaluate(register)

   operations = register.GetStoredOperations()
   assert len(operations) == 0
