import argparse

from Calculator import Calculator


def main(args: list):
   calculator = Calculator()

   if args.file_with_commands:
      # Read from provided text file
      calculator.RunCalculator(args.file_with_commands)
   else:
      # Read from standard input
      calculator.RunInteractiveCalculator()


if __name__ == "__main__":
   p = argparse.ArgumentParser()

   p.add_argument(
      "--file-with-commands",
      "-f",
      required=False,
      help="Text file containing commands to execute"
   )

   args = p.parse_args()
   main(args)
