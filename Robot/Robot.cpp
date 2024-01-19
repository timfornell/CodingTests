#include <iostream>
#include <string>
#include <vector>

#include "Robot.hpp"
#include "../Utils/Direction.hpp"

bool Robot::inActivatedState()
{
   return activated == true;
}

/*
 * Take the raw string parsed from the action file and determine if it is a valid command
 * - If yes, return true and put command components into 'command_type' according to following structure:
 *    1. Command type
 *    2. (Optional) X,Y,Direction
 * - If no, return false
 * Note: this function assumes that any command that consists of more than a command string follows this
 * structure: "CommandType X,Y,Direction"
 */
bool Robot::commandIsValid(std::string &command, std::string &command_type, std::string &optional_command_params)
{
   bool command_is_valid = false;

   // Try and split string according to defined structure

   return command_is_valid;
}

void Robot::report()
{
   std::string position_string = "Current position (x, y): (" +
                                 std::to_string(current_position.x) + ", " +
                                 std::to_string(current_position.y) + ")";
   std::string direction_string = "Current direction: " + toString(current_direction);
   std::cout << position_string << std::endl
             << direction_string << endl;
}

bool Robot::performAction(std::string &command, const TableTop &table_top)
{
   bool action_was_performed = false;

   std::string command_type;
   std::string optional_command_params;
   if (commandIsValid(command, command_type, optional_command_params))
   {
      if (command_type.compare("PLACE") == 0)
      {
         placeRobot(optional_command_params);
      }
      else if (command_type.compare("MOVE") == 0)
      {
         moveInCurrentDirection(table_top);
      }
      else if (command_type.compare("LEFT") == 0)
      {
         rotateLeft();
      }
      else if (command_type.compare("RIGHT") == 0)
      {
         rotateRight();
      }
      else if (command_type.compare("REPORT") == 0)
      {
         report();
      }
   }

   return action_was_performed;
}

void Robot::placeRobot(std::string parameters)
{
}

void Robot::moveInCurrentDirection(const TableTop &table_top)
{
   Point2D new_position;
   Point2D desired_movement = convertDirectionToComponents(current_direction);
   new_position.x = current_position.x;
}

void Robot::rotateLeft()
{
}

void Robot::rotateRight()
{
}

Point2D Robot::getCurrentPosition()
{
   return current_position;
}

Direction Robot::getCurrentHeading()
{
   return current_direction;
}

bool Robot::getActivationStatus()
{
   return activated;
}