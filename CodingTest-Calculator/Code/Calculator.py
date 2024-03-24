import sys
from pathlib import Path
from typing import Dict

from Register import Register
from Operator import Operator, Add, Subtract, Multiply, Divide
from Function import Print
from CalculatorExceptions import CommandNotFoundError, registerNamingError


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
      except registerNamingError as e:
         print(f"Error! Invalid register name encountered: {e}")
         return False

      register_name = command_parts["register"]
      if register_name not in self.registers.keys():
         self.registers[register_name] = Register(register_name)

      operation = self.supported_operations[command_parts["operation"]]
      if str(operation) == str(Print()):
         register = self.registers[register_name]
         operation.Evaluate(register.GetValue(self.registers, [register_name]))
      else:
         self.registers[register_name].AddOperation(operation, command_parts["value"])

      return True


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
         raise registerNamingError(f"'{command_parts['register']}' consists only of integers.")