from CalculatorExceptions import RegisterMissingValueError
from Operators import Operator


class Register():
   name: str
   current_value: float
   stored_operations: list
   has_value: bool

   def __init__(self, name: str) -> None:
      self.name = name
      self.current_value = 0.0
      self.has_value = False
      self.stored_operations = []

   def __str__(self) -> str:
      return self.name


   def AddOperation(self, operation: Operator, value: str):
      self.stored_operations.append({
         "operation": operation,
         "value": value
      })


   def GetStoredOperations(self) -> list:
      return self.stored_operations


   def ClearStoredOperations(self) -> None:
      self.stored_operations = []


   def SetCurrentValue(self, value: float) -> None:
      self.current_value = value


   def InitializeRegister(self) -> None:
      self.has_value = True


   def IsInitialized(self) -> None:
      return self.has_value


   def GetCurrentValue(self) -> float:
      if not self.has_value:
         raise RegisterMissingValueError(f"Register '{self}' has no value.")

      return self.current_value
