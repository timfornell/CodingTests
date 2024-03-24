from CalculatorExceptions import CircularDependencyError, CalculationError
from Operator import Operator


class Register():
   def __init__(self, name: str) -> None:
      self.name = name
      self.current_value = 0.0
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


   def GetCurrentValue(self) -> float:
      return self.current_value
