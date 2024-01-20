#include <fstream>
#include <iostream>

#include "Robot/Robot.hpp"
#include "TableTop/TableTop.hpp"

using namespace std;

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cerr << "Input file with commands is required! Exiting." << endl;
      exit(1);
   }

   // Naive implementation of argument parser that assumes that second argument is a .txt file
   const string file_path = argv[1];

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