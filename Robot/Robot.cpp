#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Robot.hpp"
#include "../Utils/Direction.hpp"

bool Robot::inActivatedState()
{
   return activated == true;
}

/*
 * Take the raw string parsed from the action file and try and split it into command_type and optional_command_params
 * Note: this function assumes that any command that consists of more than a command string follows this
 * structure: "<CommandType> <X>,<Y>,<Direction>"
 */
void Robot::getCommandComponents(std::string &command, std::string &command_type, std::string &optional_command_params)
{
   if (command.length() > 0)
   {
      const std::string command_delimiter = " ";
      const size_t pos = command.find(command_delimiter);

      if (pos > 0)
      {
         // If a space exists, assume first part contains a command type and rest is parameters for command
         command_type = command.substr(0, pos);
         optional_command_params = command.substr(pos + 1, command.length());
      }
      else
      {
         // The sent command is either incorrectly formatted or only contains a single word command
         command_type = command;
         optional_command_params = "";
      }
   }
}

void Robot::report()
{
   if (activated)
   {
      std::string position_string = "Current position (x, y): (" +
                                    std::to_string(current_position.x) + ", " +
                                    std::to_string(current_position.y) + ")";
      std::string direction_string = "Current direction: " + toString(current_direction);
      std::cout << position_string << std::endl
                << direction_string << endl;
   }
}

void Robot::performAction(std::string &command, const TableTop &table_top)
{
   std::string command_type;
   std::string optional_command_params;
   getCommandComponents(command, command_type, optional_command_params);

   if (command_type.compare("PLACE") == 0)
   {
      placeRobot(optional_command_params, table_top);
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

void Robot::placeRobot(std::string parameters, const TableTop &table_top)
{
   Point2D starting_coordinates;
   Direction starting_direction;

   if (getPlacementInformation(parameters, starting_coordinates, starting_direction))
   {
      if (table_top.coordinateIsValid(starting_coordinates))
      {
         current_position.x = starting_coordinates.x;
         current_position.y = starting_coordinates.y;
         current_direction = starting_direction;
         activated = true;
      }
   }
}

bool Robot::getPlacementInformation(const std::string parameters,
                                    Point2D &starting_coordinates,
                                    Direction &starting_direction)
{
   bool valid_parameters = false;

   // Make local copy of parameters
   std::string _parameters = parameters;

   std::vector<std::string> parameters_split;

   const std::string delimiter = ",";
   size_t pos = 0;
   while ((pos = _parameters.find(delimiter)) != std::string::npos)
   {
      std::string param = _parameters.substr(0, pos);
      parameters_split.push_back(param);
      _parameters.erase(0, pos + delimiter.length());
   }

   // If the command is correctly formatted, the remainder in _parameters should be the direction
   parameters_split.push_back(_parameters);

   if (parameters_split.size() == 3)
   {
      // Last parameter *should* be a direction
      const std::string direction = parameters_split.back();
      parameters_split.pop_back();
      const bool valid_direction = convertStringToDirection(direction, starting_direction);

      // First two parameters *should* be integers
      const std::string y_coordinate = parameters_split.back();
      parameters_split.pop_back();
      const std::string x_coordinate = parameters_split.back();
      parameters_split.pop_back();
      const bool valid_coordinates = convertStringToPoint2D(x_coordinate, y_coordinate, starting_coordinates);

      valid_parameters = (valid_direction && valid_coordinates);
   }

   return valid_parameters;
}

void Robot::moveInCurrentDirection(const TableTop &table_top)
{
   if (activated)
   {
      Point2D new_position;
      Point2D desired_movement = convertDirectionToComponents(current_direction);
      new_position.x = current_position.x + desired_movement.x;
      new_position.y = current_position.y + desired_movement.y;

      if (table_top.coordinateIsValid(new_position))
      {
         current_position.x = new_position.x;
         current_position.y = new_position.y;
      }
   }
}

void Robot::rotateLeft()
{
   if (activated)
   {
      current_direction = rotateDirectionLeft(current_direction);
   }
}

void Robot::rotateRight()
{
   if (activated)
   {
      current_direction = rotateDirectionRight(current_direction);
   }
}
