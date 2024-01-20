#ifndef _DIRECTION_
#define _DIRECTION_

#include <string>

#include "Coordinate.hpp"

/*
 * Enum to be used to represent the direction of the robot
 */
enum class Direction
{
   North,
   East,
   South,
   West,
};

bool convertStringToDirection(const std::string &stringDirection, Direction &direction);
Direction rotateDirectionLeft(const Direction &direction);
Direction rotateDirectionRight(const Direction &direction);
Point2D convertDirectionToMovementDirection(const Direction &direction);
std::string toString(Direction &direction);

#endif // _DIRECTION_