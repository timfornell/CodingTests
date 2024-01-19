#ifndef _TABLE_TOP_
#define _TABLE_TOP_

#include "../Utils/Coordinate.hpp"

class TableTop
{
private:
   int width, height;

public:
   int getWidth();
   int getHeight();
   bool coordinateIsValid(Point2D &coordinate);
};

#endif // _TABLE_TOP_