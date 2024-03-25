from abc import ABC, abstractmethod


class Operator(ABC):
   """
   The Operator class is intended to contain operators that a single value as input. The value can either be a
   number or a register.

   Currently, the class only supports operators that operates on the value of a register and one other value.
   """
   @abstractmethod
   def Evaluate(self, register_value: float, operation_value: float) -> float:
      pass


class Add(Operator):
   def __str__(self) -> str:
      return "add"

   def Evaluate(self, register_value: float, operation_value: float) -> float:
      return register_value + operation_value


class Subtract(Operator):
   def __str__(self) -> str:
      return "subtract"

   def Evaluate(self, register_value: float, operation_value: float) -> float:
      return register_value - operation_value


class Multiply(Operator):
   def __str__(self) -> str:
      return "multiply"

   def Evaluate(self, register_value: float, operation_value: float) -> float:
      return register_value * operation_value


class Divide(Operator):
   def __str__(self) -> str:
      return "divide"

   def Evaluate(self, register_value: float, operation_value: float) -> float:
      return register_value / operation_value
