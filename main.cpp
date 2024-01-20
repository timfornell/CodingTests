#include <fstream>
#include <iostream>

#include "Robot/Robot.hpp"
#include "TableTop/TableTop.hpp"

using namespace std;

int main()
{
   // Initialize table
   const int table_width = 5;
   const int table_height = 5;
   TableTop table(table_width, table_height);

   // Initialize robot
   Robot robot;

   // Read input file
   ifstream input_file("valid_commands.txt");

   string line;
   while (getline(input_file, line))
   {
      cout << line << endl;
      robot.performAction(line, table);
   }

   cout << "Finished!" << endl;
}