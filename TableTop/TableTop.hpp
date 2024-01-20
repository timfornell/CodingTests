#ifndef _TABLE_TOP_
#define _TABLE_TOP_

#include <vector>

#include "../Utils/Coordinate.hpp"

class TableTop
{
private:
   int table_width, table_height;

public:
   TableTop(int width, int height) : table_width(width), table_height(height) {}
   bool coordinateIsValid(const Point2D &coordinate) const;
};

#endif // _TABLE_TOP_