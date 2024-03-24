from abc import ABC, abstractmethod


class Operator(ABC):
   @abstractmethod
   def Evaluate(self, register: str, value: str):
      pass


class Add(Operator):
   def __str__(self) -> str:
      return "add"

   def Evaluate(self):
      return super().Evaluate()


class Subtract(Operator):
   def __str__(self) -> str:
      return "subtract"

   def Evaluate(self):
      return super().Evaluate()


class Multiply(Operator):
   def __str__(self) -> str:
      return "multiply"

   def Evaluate(self):
      return super().Evaluate()


class Divide(Operator):
   def __str__(self) -> str:
      return "divide"

   def Evaluate(self):
      return super().Evaluate()
