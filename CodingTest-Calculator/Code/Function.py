from abc import ABC, abstractmethod


class Function(ABC):
   @abstractmethod
   def Evaluate(self, register: str):
      pass


class Print(Function):
   def __str__(self) -> str:
      return "print"

   def Evaluate(self):
      return super().Evaluate()