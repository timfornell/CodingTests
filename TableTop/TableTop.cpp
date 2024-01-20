#include <cmath>

#include "TableTop.hpp"

/*
 * Constructor for TableTop
 *
 * If the width and height provided are smaller than zero the table size will be set to {0, 0}. Which
 * results in a table that can't really be used.
 *
 * @param width: desired width of table, larger than zero
 * @param height: desired height of table, larger than zero
 */
TableTop::TableTop(const int width, const int height)
{
   if ((width > 0) || (height > 0))
   {
      table_width = width;
      table_height = height;
   }
   else
   {
      // Set size to smallest possible, i.e., {0, 0}
      table_width = 0;
      table_height = 0;
   }
}

/*
 * Check if a coordinate is inside the limits of the table.
 *
 * @param coordinate: reference to a Point2D that should be checked
 *
 * @return a bool representing if the provided coordinate is valid
 */
bool TableTop::coordinateIsValid(const Point2D &coordinate) const
{
   return ((0 <= coordinate.x) && (coordinate.x < table_width) && (0 <= coordinate.y) && (coordinate.y < table_height));
}
