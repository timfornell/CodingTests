# test_calculator.py

import logging

from Calculator import Calculator

# Disable logging to only get output from the 'print' command
logging.getLogger().setLevel(logging.ERROR)


def get_test_cases():
   return [
      {
         "file": "Test/TestFile_1.txt",
         "expected_output": ["Output: 5.0", "Output: 3.0", "Output: 6.0"]
      },
      {
         "file": "Test/TestFile_2.txt",
         "expected_output": ["Output: 11.0"]
      },
      {
         "file": "Test/TestFile_3.txt",
         "expected_output": ["Output: 90.0"]
      },
      {
         "file": "Test/TestFile_4.txt",
         "expected_output": []
      },
      {
         "file": "Test/TestFile_5.txt",
         "expected_output": ["Output: 20.0", "Output: 20.0", "Output: 400.0"]
      },
      {
         "file": "Test/TestFile_6.txt",
         "expected_output": ["Output: 10.0", "Output: 10.0"]
      },
      {
         "file": "Test/TestFile_7.txt",
         "expected_output": ["Output: 8400.0", "Output: 20.0"]
      }
   ]


def test_calculator(capsys):
   test_cases = get_test_cases()
   for test_case in test_cases:

      calculator = Calculator()
      calculator.RunCalculator(test_case["file"])

      # This is not a nice way of testing, but it is a way of having automated tests
      # for a program that only prints to stdout
      captured = capsys.readouterr()
      actual_output = captured.out.split("\n")[0:-1]
      assert actual_output == test_case["expected_output"]