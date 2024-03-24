import sys
from pathlib import Path

from Operator import Add, Subtract, Multiply, Divide
from Function import Print


class CommandNotFoundError(Exception):
   pass


class Calculator:
   def __init__(self) -> None:
      self.registers = {}
      self.supported_operators = {
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
            line = line.rstrip()
            self.ExecuteCommand(line)


   def RunInteractiveCalculator(self) -> None:
      for line in sys.stdin:
         line = line.rstrip()

         if line == "quit":
            print("Received 'quit', stopping execution.")
            break

         try:
            self.ExecuteCommand(line)
         except CommandNotFoundError as e:
            print(f"Invalid command encountered: {e}")


   def ExecuteCommand(self, command_line: str) -> None:
      if not command_line:
         print("Empty line received.")
         return

      command_parts = self.ParseCommand(command_line)

      if command_parts["operation"] not in self.supported_operators.keys():
         raise CommandNotFoundError(f"command '{command_parts['operation']}' is not supported.")


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

      # 'value' is a list to simplify potential future implementation of operators that require more than one input
      command_parts = {"operation": "", "registry": "", "value": []}
      if len(split_command) == 2:
         command_parts["operation"] = split_command[0]
         command_parts["registry"] = split_command[1]
      elif len(split_command) == 3:
         command_parts["registry"] = split_command[0],
         command_parts["operation"] = split_command[1],
         command_parts["value"] = split_command[2:]

      return command_parts