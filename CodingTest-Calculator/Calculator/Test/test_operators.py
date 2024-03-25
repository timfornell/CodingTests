# test_operators.py

from Operators import Add, Subtract, Multiply, Divide


def test_add():
   op = Add()

   assert str(op) == "add"
   assert op.Evaluate(10, 5) == 15


def test_subtract():
   op = Subtract()

   assert str(op) == "subtract"
   assert op.Evaluate(10, 5) == 5


def test_multiply():
   op = Multiply()

   assert str(op) == "multiply"
   assert op.Evaluate(10, 5) == 50


def test_divide():
   op = Divide()

   assert str(op) == "divide"
   assert op.Evaluate(10, 5) == 2