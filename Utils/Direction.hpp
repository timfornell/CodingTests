#ifndef _DIRECTION_
#define _DIRECTION_

#include <string>

#include "Coordinate.hpp"

using namespace std;

/*
 * Enum to be used to represent the direction of the robot
 */
enum Direction
{
   North,
   East,
   South,
   West,
};

Point2D convertDirectionToComponents(const Direction &direction);
bool convertStringToDirection(const string &stringDirection, Direction &direction);

#endif // _DIRECTION_