import sys
from pathlib import Path
from typing import Dict, List

from Register import Register
from Operators import Operator, Add, Subtract, Multiply, Divide
from Functions import Print, Clear
from CalculatorExceptions import *


class Calculator:
   registers: Dict[str, Register]
   supported_operations: Dict[str, Operator]
   supported_functions: List[str]


   def __init__(self) -> None:
      self.registers = {}
      self.supported_operations = {
         str(Add()): Add(),
         str(Subtract()): Subtract(),
         str(Multiply()): Multiply(),
         str(Divide()): Divide(),
      }
      self.supported_functions = [
         str(Print()),
         str(Clear())
      ]


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

            self.ExecuteCommand(line)


   def RunInteractiveCalculator(self) -> None:
      for line in sys.stdin:
         # Remove line breaks
         line = line.rstrip()

         if line == "quit":
            print("Received 'quit', stopping execution.")
            break

         self.ExecuteCommand(line)


   def ExecuteCommand(self, command_line: str) -> None:
      """
      Main function of the calculator

      The following happens here:
      -  Parses the command line and separates it into components
      -  Verifies the command components to check if the command is valid
      -  Makes sure that registers are created, operations stored or functions are executed
      -  Catches any exceptions that are raised
      """
      if not command_line:
         print("Empty line received.")
         return False

      try:
         command_parts = self.ParseCommand(command_line)
         self.ValidateCommand(command_parts)

         register_name = command_parts["register"]
         operation = command_parts["operation"]
         value = command_parts["value"]

         if operation in self.supported_functions:
            self.RunFunctionOnRegister(register_name, operation)
         elif operation in self.supported_operations.keys():
            self.AddOperationToRegister(register_name, operation, value)

      except CommandNotFoundError as e:
         print(f"Error! Invalid command encountered: {e}")
      except RegisterNamingError as e:
         print(f"Error! Invalid register name encountered: {e}")
      except CommandComponentsError as e:
         print(f"Error! The line does not contain a valid command: {e}")
      except CircularDependencyError as e:
         print(f"Error! Encountered a circular dependency: {e}")
      except RegisterNotFoundError as e:
         print(f"Error! Encountered a missing register: {e}")
      except RegisterMissingValueError as e:
         print(f"Error! Encountered a register without value: {e}")


   def AddOperationToRegister(self, register_name: str, operation: str, value: str) -> None:
      if register_name not in self.registers.keys():
         self.AddNewRegister(register_name)

      self.registers[register_name].AddOperation(self.supported_operations[operation], value)


   def RunFunctionOnRegister(self, register_name: str, operation: str) -> None:
      """
      Try and run any functions that are defined in the variable 'supported_functions'

      A function is typically something that operates on a registry, or on the value of a registry.
      """
      if register_name not in self.registers.keys():
         raise RegisterNotFoundError(f"Can't perform '{operation}' on '{register_name}' as it doesn't exist.")

      if operation == str(Print()):
         # Try and evaluate the value of the specified register
         register_value = self.GetValueOfRegister(self.registers[register_name], [register_name])
         Print().Evaluate(register_value)
      elif operation == str(Clear()):
         # Clear the specified register
         Clear().Evaluate(self.registers[register_name])


   def AddNewRegister(self, register_name: str) -> None:
      self.registers[register_name] = Register(register_name)


   def GetValueOfRegister(self, register: Register, forbidden_registers: list) -> float:
      """
      Evaluate the provided register

      Iterate through the stored operations in a register. If another register is encountered, its stored operations are
      evaluated first. To avoid circular dependencies, the list 'forbidden_registers' contains registers that are
      currently being evaluated and thus don't have a 'final' value that can be used.
      """
      for op in register.GetStoredOperations():
         value = op["value"]
         if value in forbidden_registers:
            raise CircularDependencyError(f"Register '{value}' contains a circular dependency to register '{register}'.")

         operation_value = 0.0
         if value.isnumeric():
            operation_value = float(value)
         elif value in self.registers.keys():
            # Add current register to list of forbidden registers and try to calculate value of referenced register
            operation_value = self.GetValueOfRegister(self.registers[value], forbidden_registers + [value])
         else:
            # If 'value' isn't numeric or an available register, something has gone wrong.
            print(f"The value/registry '{value}' could not be resolved and can't be used for operation '{op['operation']}'.")
            continue

         # If this point is reached, the register shall be considered initialized
         register.InitializeRegister()
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
         raise CommandComponentsError(command_parts)

      if ((command_parts["operation"] not in self.supported_operations.keys()) and
          (command_parts["operation"] not in self.supported_functions)):
         raise CommandNotFoundError(f"'{command_parts['operation']}' is not supported.")

      # Registers can't contain ONLY numbers
      if command_parts["register"].isnumeric():
         raise RegisterNamingError(f"'{command_parts['register']}' consists only of integers.")
