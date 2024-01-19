#include <iostream>
#include <string>

#include "Robot.hpp"
#include "../Utils/Direction.hpp"

bool Robot::inActivatedState()
{
   return activated == true;
}

bool Robot::commandIsValid(std::string &command)
{
   bool commandIsValid = false;

   // Try and split string according to defined structure

   return commandIsValid;
}

void Robot::report()
{
   std::string positionString = "Current position (x, y): (" +
                                std::to_string(current_position.x) + ", " +
                                std::to_string(current_position.y) + ")";
   std::string directionString = "Current direction: " + toString(current_direction);
   std::cout << positionString << std::endl;
}

bool Robot::performAction(std::string &command, const TableTop &table_top)
{
   bool actionsWasPerformed = false;

   return actionsWasPerformed;
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