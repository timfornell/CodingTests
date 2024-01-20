#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Robot.hpp"
#include "../Utils/Direction.hpp"

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

/*
 * Extract placement information from string 'parameters'.
 *
 * Splits 'parameters' by the delimiter ',' and verifies that it contains exactly three components. If true,
 * tries to convert the three components from string to a Point2D (X and Y) and Direction.
 *
 * @param parameters: string that should contain parameters for placement
 * @param starting_coordinates: reference to a Point2D, where parsed X and Y is saved
 * @param starting_direction: reference to a Direction, where parsed direction is saved
 *
 * @return bool that represent if 'parameters' contains valid placement parameters
 */
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

   // If the command is correctly formatted, the remainder in _parameters should be the direction.
   if (_parameters.length() > 0)
   {
      parameters_split.push_back(_parameters);
   }

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

/*
 * Attempt to place robot on the table
 *
 * Takes a string, 'parameters', and checks if it contains x, y and direction according to "X,Y,Direction". If
 * true, try and place robot at these coordinates on the table. Also, activates the robot.
 *
 * @param parameters: string that should contain parameters for placement
 * @param table_top: reference to the table
 */
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

/*
 * If robot is activated, try and move in the current direction
 */
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

/*
 * If robot is activated, rotate direction counterclockwise.
 */
void Robot::rotateLeft()
{
   if (activated)
   {
      current_direction = rotateDirectionLeft(current_direction);
   }
}

/*
 * If robot is activated, rotate direction clockwise.
 */
void Robot::rotateRight()
{
   if (activated)
   {
      current_direction = rotateDirectionRight(current_direction);
   }
}

/*
 * If robot is activated, report current position and direction of robot.
 */
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

/*
 * If robot is activated, try and perform an action provided in 'command'.
 *
 * Entry point for making the robot perform an action. If the command string can be converted to a valid command, call
 * the respective command handling function.
 *
 * @param command: string to be checked for a valid command
 * @param table_top: reference to the table
 */
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