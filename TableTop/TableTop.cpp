#include <cmath>

#include "TableTop.hpp"

/*
 * Check if a coordinate is inside the limits of the table.
 */
bool TableTop::coordinateIsValid(const Point2D &coordinate) const
{
   return ((0 <= coordinate.x) && (coordinate.x < table_width) && (0 <= coordinate.y) && (coordinate.y < table_height));
}
