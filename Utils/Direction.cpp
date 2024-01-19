#include "Direction.hpp"

/*
 * Convert the direction to a numeric representation of how a movement of one square in that direction
 * would affect the current position of the robot.
 */
Point2D convertDirectionToComponents(const Direction &direction)
{
   Point2D components{0, 0};

   switch (direction)
   {
   case North:
      components.x = 1;
      components.y = 0;
      break;
   case East:
      components.x = 0;
      components.y = 1;
      break;
   case South:
      components.x = -1;
      components.y = 0;
      break;
   case West:
      components.x = 0;
      components.y = -1;
      break;
   default:
      break;
   }

   return components;
}

/*
 * Check if provided string is a valid direction.
 * - If yes, convert to corresponding enum value, save in 'direction' and return true
 * - If no, return false
 */
bool convertStringToDirection(const string &stringDirection, Direction &direction)
{
   bool validDirection = false;

   if (stringDirection.compare("NORTH") == 0)
   {
      validDirection = true;
      direction = North;
   }
   else if (stringDirection.compare("EAST") == 0)
   {
      validDirection = true;
      direction = East;
   }
   else if (stringDirection.compare("SOUTH") == 0)
   {
      validDirection = true;
      direction = South;
   }
   else if (stringDirection.compare("WEST") == 0)
   {
      validDirection = true;
      direction = West;
   }

   return validDirection;
}