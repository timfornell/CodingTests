import sys
from pathlib import Path
from typing import Dict

from Register import Register
from Operator import Operator, Add, Subtract, Multiply, Divide
from Function import Print
from CalculatorExceptions import *


class Calculator:
   registers: Dict[str, Register]
   supported_operations: Dict[str, Operator]

   def __init__(self) -> None:
      self.registers = {}
      self.supported_operations = {
         str(Add()): Add(),
         str(Subtract()): Subtract(),
         str(Multiply()): Multiply(),
         str(Divide()): Divide(),
         str(Print()): Print()
      }


   def RunCalculator(self, file_with_commands: str) -> None:
      file_with_commands = Path(file_with_commands)

      if not file_with_commands.exists():
         raise FileNotFoundError(f"Could not find {file_with_commands}!")

      with file_with_commands.open("r") as f:
         for line in f.readlines():
            # Remove line breaks
            line = line.rstrip()

            if line == "quit":
               print("Received 'quit', stopping execution.")
               break

            print(line)
            if not self.ExecuteCommand(line):
               print(f"Something wen't wrong during execution.")


   def RunInteractiveCalculator(self) -> None:
      for line in sys.stdin:
         # Remove line breaks
         line = line.rstrip()

         if line == "quit":
            print("Received 'quit', stopping execution.")
            break

         print(line)
         if not self.ExecuteCommand(line):
            print(f"Something wen't wrong during execution.")


   def ExecuteCommand(self, command_line: str) -> bool:
      if not command_line:
         print("Empty line received.")
         return

      command_parts = self.ParseCommand(command_line)

      try:
         self.ValidateCommand(command_parts)
      except CommandNotFoundError as e:
         print(f"Error! invalid command encountered: {e}")
         return False
      except RegisterNamingError as e:
         print(f"Error! Invalid register name encountered: {e}")
         return False
      except CommandComponentsError as e:
         print(f"Error! The line does not contain a valid command.")
         return False

      register_name = command_parts["register"]
      if register_name not in self.registers.keys():
         self.registers[register_name] = Register(register_name)

      operation = self.supported_operations[command_parts["operation"]]
      if str(operation) == str(Print()):
         register_value = self.GetValueOfRegister(register_name, [register_name])
         operation.Evaluate(register_value)
      else:
         self.registers[register_name].AddOperation(operation, command_parts["value"])

      return True


   def GetValueOfRegister(self, register_name: str, forbidden_registers: list) -> float:
      register = self.registers[register_name]
      for op in register.GetStoredOperations():
         value = op["value"]
         if value in forbidden_registers:
            raise CircularDependencyError(f"Encountered a circular dependency to register '{value}' when evaluating register '{self.name}'.")

         operation_value = 0.0
         if value.isnumeric():
            operation_value = float(value)
         elif value in self.registers.keys():
            operation_value = self.GetValueOfRegister(value, forbidden_registers + [value])
         else:
            # If 'value' isn't numeric or an available register, something has gone wrong.
            raise CalculationError(f"The value/registry '{value}' could not be evaluated.")

         new_value = op["operation"].Evaluate(register.GetCurrentValue(), operation_value)
         register.SetCurrentValue(new_value)

      # Value has been calculated and stored, no need to store operations anymore
      register.ClearStoredOperations()

      return register.GetCurrentValue()


   def ParseCommand(self, command: str) -> dict:
      """
      Parse commands

      Commands given to the calculator should follow one of the following structures:
      -  <register> <operator> <value>
      -  print <register>

      @param command: string that should contain a command
      @return command split into its components
      """
      split_command = command.split(" ")

      command_parts = {"operation": "", "register": "", "value": ""}
      if len(split_command) == 2:
         command_parts["operation"] = split_command[0]
         command_parts["register"] = split_command[1]
      elif len(split_command) == 3:
         command_parts["register"] = split_command[0]
         command_parts["operation"] = split_command[1]
         command_parts["value"] = split_command[2]

      return command_parts

   def ValidateCommand(self, command_parts: dict) -> None:
      if command_parts["operation"] not in self.supported_operations.keys():
         raise CommandNotFoundError(f"'{command_parts['operation']}' is not supported.")

      if command_parts["register"].isnumeric():
         raise RegisterNamingError(f"'{command_parts['register']}' consists only of integers.")

      if (not command_parts["register"]) and (not command_parts["operation"]) and (not command_parts["value"]):
         raise CommandComponentsError()