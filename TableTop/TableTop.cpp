#include <cmath>

#include "TableTop.hpp"

int TableTop::getHeight()
{
   return table_height;
}

int TableTop::getWidth()
{
   return table_width;
}

/*
 * Check if a coordinate is inside the limits of the table.
 */
bool TableTop::coordinateIsValid(Point2D &coordinate)
{
   return ((abs(coordinate.x) < table_width) && (abs(coordinate.y) < table_height));
}
