#include "Direction.hpp"

/*
 * Check if provided string is a valid direction.
 * - If yes, convert to corresponding enum value, save in 'direction' and return true
 * - If no, return false
 *
 * @param string_direction: string to be converted
 * @param direction: reference to a Direction where result is saved
 *
 * @return bool representing if the conversion was successful
 */
bool convertStringToDirection(const std::string &string_direction, Direction &direction)
{
   bool valid_direction = false;

   if (string_direction.compare("NORTH") == 0)
   {
      valid_direction = true;
      direction = Direction::North;
   }
   else if (string_direction.compare("EAST") == 0)
   {
      valid_direction = true;
      direction = Direction::East;
   }
   else if (string_direction.compare("SOUTH") == 0)
   {
      valid_direction = true;
      direction = Direction::South;
   }
   else if (string_direction.compare("WEST") == 0)
   {
      valid_direction = true;
      direction = Direction::West;
   }

   return valid_direction;
}

/*
 * Rotate provided direction counterclockwise
 *
 * @param direction: reference to a Direction to be rotated
 *
 * @return a Direction representing the rotated Direction
 */
Direction rotateDirectionLeft(const Direction &direction)
{
   Direction new_direction;

   switch (direction)
   {
   case Direction::North:
      new_direction = Direction::West;
      break;
   case Direction::East:
      new_direction = Direction::North;
      break;
   case Direction::South:
      new_direction = Direction::East;
      break;
   case Direction::West:
      new_direction = Direction::South;
      break;

   default:
      // Should not end up here
      break;
   }

   return new_direction;
}

/*
 * Rotate provided direction clockwise
 *
 * @param direction: reference to a Direction to be rotated
 *
 * @return a Direction representing the rotated Direction
 */
Direction rotateDirectionRight(const Direction &direction)
{
   Direction new_direction;

   switch (direction)
   {
   case Direction::North:
      new_direction = Direction::East;
      break;
   case Direction::East:
      new_direction = Direction::South;
      break;
   case Direction::South:
      new_direction = Direction::West;
      break;
   case Direction::West:
      new_direction = Direction::North;
      break;

   default:
      // Should not end up here
      break;
   }

   return new_direction;
}

/*
 * Convert the direction to a numeric representation of how a movement of one square in that direction
 * would affect the current position of the robot.
 *
 * The movement direction is aligned so that any movement in East <-> West is along the x axis and
 * so that any movement in North <-> South is along the y axis.
 *
 * @param direction: reference to a Direction that should be converted
 *
 * @return Point2D that indicates how the robot would move in provided direction
 */
Point2D convertDirectionToMovementDirection(const Direction &direction)
{
   // Default to {0, 0} means that if an unknown direction is provided, the robot won't move
   Point2D components{0, 0};

   switch (direction)
   {
   case Direction::North:
      components.x = 0;
      components.y = 1;
      break;
   case Direction::East:
      components.x = 1;
      components.y = 0;
      break;
   case Direction::South:
      components.x = 0;
      components.y = -1;
      break;
   case Direction::West:
      components.x = -1;
      components.y = 0;
      break;
   default:
      break;
   }

   return components;
}

/*
 * Convert a Direction to its string representation
 *
 * @param direction: reference to a Direction to be converted
 *
 * @return a string representing the converted Direction
 */
std::string toString(Direction &direction)
{
   std::string str;

   switch (direction)
   {
   case Direction::North:
      str = "North";
      break;
   case Direction::East:
      str = "East";
      break;
   case Direction::South:
      str = "South";
      break;
   case Direction::West:
      str = "West";
      break;

   default:
      // Should not end up here
      break;
   }

   return str;
}
