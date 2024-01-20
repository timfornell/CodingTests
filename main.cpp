#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.hpp"

#include <fstream>
#include <iostream>

#include "Robot/Robot.hpp"
#include "TableTop/TableTop.hpp"

using namespace std;

void program(int argc, char **argv)
{
   if (argc != 3)
   {
      cerr << "Input file with commands is required! Exiting." << endl;
      exit(1);
   }

   // Naive implementation of argument parser that assumes that second argument is a .txt file
   const string file_path = argv[2];

   // Initialize table
   const int table_width = 5;
   const int table_height = 5;
   TableTop table(table_width, table_height);

   // Initialize robot
   Robot robot;

   // Read input file
   ifstream input_file(file_path);
   if (!input_file.good())
   {
      cerr << "Provided file does not exist: " << file_path << endl;
      exit(1);
   }

   string line;
   while (getline(input_file, line))
   {
      if (line.rfind("#", 0) == 0)
      {
         // This allows for comments in the txt file. Allows for easier comparison of expected output
         continue;
      }

      cout << "\n>> Command received: " << line << endl;
      robot.performAction(line, table);
   }

   cout << "\nFinished!" << endl;
}

int main(int argc, char **argv)
{
   doctest::Context context;

   context.setOption("abort-after", 5);   // stop test execution after 5 failed assertions
   context.setOption("order-by", "name"); // sort the test cases by their name

   context.applyCommandLine(argc, argv);

   int res = context.run(); // run

   if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
      return res;            // propagate the result of the tests

   // This is only run if the flag '--no-run' is provided
   program(argc, argv);

   return res;
}