#include <cmath>

#include "TableTop.hpp"

int TableTop::getHeight()
{
   return height;
}

int TableTop::getWidth()
{
   return width;
}

/*
 * Check if a coordinate is inside the limits of the table.
 */
bool TableTop::coordinateIsValid(Point2D &coordinate)
{
   return ((abs(coordinate.x) < width) && (abs(coordinate.y) < height));
}
