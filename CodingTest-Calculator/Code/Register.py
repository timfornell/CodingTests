from CalculatorExceptions import CircularDependencyError
from Operator import Operator


class Register():
   def __init__(self, name: str) -> None:
      self.name = name
      self.current_value = 0.0
      self.stored_operations = []

   def __str__(self) -> str:
      return self.name

   # This function should probably be in the Calculator class
   def GetValue(self, available_registers: dict, forbidden_registries: list) -> float:
      for op in self.stored_operations:
         value = op["value"]
         if value in forbidden_registries:
            raise CircularDependencyError(f"Encountered a circular dependency when evaluating register {self.name}.")

         if value in available_registers.keys():
            value = available_registers[value].GetValue(available_registers, forbidden_registries + [value])
            self.current_value = op["operation"].Evaluate(self.current_value, value)
         elif value.isnumeric():
            value = float(value)
            self.current_value = op["operation"].Evaluate(self.current_value, value)

      # Value has been calculated and stored, no need to store operations anymore
      self.stored_operations = []

      return self.current_value

   def AddOperation(self, operation: Operator, value: str):
      self.stored_operations.append({
         "operation": operation,
         "value": value
      })