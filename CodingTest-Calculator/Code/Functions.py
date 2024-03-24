from abc import ABC, abstractmethod

from Register import Register


class Print():
   def __str__(self) -> str:
      return "print"

   def Evaluate(self, register_value: float):
      return print(f"Output: {register_value}")


class Clear():
   def __str__(self) -> str:
      return "clear"

   def Evaluate(self, register: Register):
      register.ClearStoredOperations()