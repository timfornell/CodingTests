from abc import ABC, abstractmethod


class Function(ABC):
   """
   The Function class is supposed to contain functions that take a single register as input.
   """
   @abstractmethod
   def Evaluate(self):
      pass


class Print(Function):
   def __str__(self) -> str:
      return "print"

   def Evaluate(self, register_value: float):
      return print(f"Output: {register_value}")