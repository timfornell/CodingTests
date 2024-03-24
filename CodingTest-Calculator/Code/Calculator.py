import sys
from pathlib import Path
from typing import Dict

from Register import Register
from Operator import Operator, Add, Subtract, Multiply, Divide
from Function import Function, Print
from CalculatorExceptions import *


class Calculator:
   registers: Dict[str, Register]
   supported_operations: Dict[str, Operator]
   supported_functions: Dict[str, Function]


   def __init__(self) -> None:
      self.registers = {}
      self.supported_operations = {
         str(Add()): Add(),
         str(Subtract()): Subtract(),
         str(Multiply()): Multiply(),
         str(Divide()): Divide(),
      }
      self.supported_functions = {
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
            self.ExecuteCommand(line)


   def RunInteractiveCalculator(self) -> None:
      for line in sys.stdin:
         # Remove line breaks
         line = line.rstrip()

         if line == "quit":
            print("Received 'quit', stopping execution.")
            break

         print(line)
         self.ExecuteCommand(line)


   def ExecuteCommand(self, command_line: str) -> None:
      if not command_line:
         print("Empty line received.")
         return False

      try:
         command_parts = self.ParseCommand(command_line)
         self.ValidateCommand(command_parts)

         register_name = command_parts["register"]
         if register_name not in self.registers.keys():
            self.AddNewRegister(register_name)

         register = self.registers[register_name]
         operation = command_parts["operation"]
         if operation in self.supported_functions.keys():
            register_value = self.GetValueOfRegister(register, [register_name])
            self.supported_functions[operation].Evaluate(register_value)
         elif operation in self.supported_operations.keys():
            value = command_parts["value"]
            register.AddOperation(self.supported_operations[operation], value)

      except CommandNotFoundError as e:
         print(f"Error! invalid command encountered: {e}")
      except RegisterNamingError as e:
         print(f"Error! Invalid register name encountered: {e}")
      except CommandComponentsError as e:
         print(f"Error! The line does not contain a valid command.")
      except CircularDependencyError as e:
         print(f"Encountered a circular dependency: {e}")


   def AddNewRegister(self, register_name: str) -> None:
      self.registers[register_name] = Register(register_name)


   def GetValueOfRegister(self, register: Register, forbidden_registers: list) -> float:
      for op in register.GetStoredOperations():
         value = op["value"]
         if value in forbidden_registers:
            raise CircularDependencyError(f"Register '{value}' contains a circular dependency to register '{register}'.")

         operation_value = 0.0
         if value.isnumeric():
            operation_value = float(value)
         elif value in self.registers.keys():
            operation_value = self.GetValueOfRegister(self.registers[value], forbidden_registers + [value])
         else:
            # If 'value' isn't numeric or an available register, something has gone wrong.
            print(f"The value/registry '{value}' could not be resolved and is skipped.")
            continue

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
      if (not command_parts["register"]) and (not command_parts["operation"]) and (not command_parts["value"]):
         raise CommandComponentsError()

      if ((command_parts["operation"] not in self.supported_operations.keys()) and
          (command_parts["operation"] not in self.supported_functions)):
         raise CommandNotFoundError(f"'{command_parts['operation']}' is not supported.")

      if command_parts["register"].isnumeric():
         raise RegisterNamingError(f"'{command_parts['register']}' consists only of integers.")
