import sys
import logging
from pathlib import Path
from typing import Dict, List

from Register import Register
from Operators import Operator, Add, Subtract, Multiply, Divide
from Functions import Print, Clear
from CalculatorExceptions import *


# Logging config
logging.basicConfig(level=logging.WARNING, format="%(levelname)s%(message)s")


class Calculator:
   """
   Main class for the Calculator program

   Contains the following class parameters:
   -  registers: dict that contains all currently available registers on the form {<register name>: <Register object>}
   -  supported_operators: dict that contains all supported operations on the form: {<operation name>: <Operation object>}
   -  supported_functions: dict that contains all supported functions on the form: {<function name>: <Function object>}

   Any new operators or functions need to be added to the corresponding variable for the calculator to access them.

   Contains two functions for running the calculator:
   -  RunCalculator: reads commands from a file
   -  RunInteractiveCalculator: reads commands from standard input
   """
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
               logging.info("Received 'quit', stopping execution.")
               break

            self.ExecuteCommand(line)


   def RunInteractiveCalculator(self) -> None:
      for line in sys.stdin:
         # Remove line breaks
         line = line.rstrip()

         if line == "quit":
            logging.info("Received 'quit', stopping execution.")
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

      @param command_line: string containing command that should be executed
      """
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
         logging.warning(f"> Invalid command encountered: {e}")
      except RegisterNamingError as e:
         logging.warning(f"> Invalid register name encountered: {e}")
      except CommandComponentsError as e:
         logging.warning(f"> The line does not contain a valid command: {command_line}")
      except CircularDependencyError as e:
         logging.warning(f"> Encountered a circular dependency: {e}")
      except RegisterNotFoundError as e:
         logging.warning(f"> Encountered a missing register: {e}")
      except RegisterMissingValueError as e:
         logging.warning(f"> Encountered a register without value: {e}")


   def AddOperationToRegister(self, register_name: str, operation: str, value: str) -> None:
      """
      Add operation to register

      To enable 'lazy evaluation' all operations are stored in their respective register.

      @param register_name: name of register
      @param operation: name of operation to be performed
      @param value: the value used in the operation
      """
      if register_name not in self.registers.keys():
         self.AddNewRegister(register_name)

      self.registers[register_name].AddOperation(self.supported_operations[operation], value)


   def RunFunctionOnRegister(self, register_name: str, operation: str) -> None:
      """
      Try and run any functions that are defined in the variable 'supported_functions'

      A function is typically something that operates on a registry, or on the value of a registry.

      @param register_name: name of register
      @param operation: name of function to be executed
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
      evaluated before continuing. To avoid circular dependencies, the list 'forbidden_registers' contains registers
      that are currently being evaluated and thus don't have a 'final' value that can be used.

      @param register: Register object that is under evaluation
      @param forbidden_registers: list of registers that are being evaluated
      @return float: evaluated value of register
      """
      for op in register.GetStoredOperations():
         value = op["value"]
         if value in forbidden_registers:
            raise CircularDependencyError(f"Register '{register}' contains a circular reference to register '{value}'")

         operation_value = 0.0
         if value.isnumeric():
            operation_value = float(value)
         elif value in self.registers.keys():
            # Add current register to list of forbidden registers and try to calculate value of referenced register
            operation_value = self.GetValueOfRegister(self.registers[value], forbidden_registers + [value])
         else:
            # If 'value' isn't numeric or an available register, something has gone wrong.
            logging.warning(f"The value/registry '{value}' could not be resolved and can't be used for operation '{op['operation']}'.")
            # No exception is raised since an invalid operation should not prevent further execution.
            continue

         # If this point is reached, the register shall be considered initialized
         register.InitializeRegister()
         new_value = op["operation"].Evaluate(register.GetCurrentValue(), operation_value)
         register.SetCurrentValue(new_value)

      if register.IsInitialized():
         # Value has been calculated and stored, no need to store operations anymore
         register.ClearStoredOperations()

      return register.GetCurrentValue()


   def ParseCommand(self, command: str) -> dict:
      """
      Parse commands

      Commands given to the calculator should follow one of the following structures:
      -  <register> <operator> <value>
      -  print <register>

      Returns a dict with empty values if the command doesn't contain enough components.

      @param command: string that should contain a command
      @return command split into its components
      """
      command_parts = {"operation": "", "register": "", "value": ""}

      if not command:
         logging.warning("Empty line received.")
         return command_parts

      split_command = command.split(" ")
      if len(split_command) == 2:
         command_parts["operation"] = split_command[0]
         command_parts["register"] = split_command[1]
      elif len(split_command) == 3:
         command_parts["register"] = split_command[0]
         command_parts["operation"] = split_command[1]
         command_parts["value"] = split_command[2]

      return command_parts

   def ValidateCommand(self, command_parts: dict) -> None:
      """
      Validate the command that was parsed from the command line

      @param command_parts: dict that contains keys 'register', 'operation' and 'value'
      """
      # A command should always include a register and an operation
      if (not command_parts["register"]) or (not command_parts["operation"]):
         raise CommandComponentsError()

      if ((command_parts["operation"] not in self.supported_operations.keys()) and
          (command_parts["operation"] not in self.supported_functions)):
         raise CommandNotFoundError(f"'{command_parts['operation']}' is not supported.")

      if not command_parts["register"].isalnum():
         raise RegisterNamingError(f"'{command_parts['register']}' consists only of integers.")
