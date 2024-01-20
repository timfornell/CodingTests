#ifndef _COORDINATE_
#define _COORDINATE_

#include <string>

/*
 * Struct defined to simplify passing around (x, y) coordinates between functions
 */
typedef struct Point2D_
{
   int x;
   int y;
} Point2D;

bool stringOnlyContainsDigits(std::string str);
bool convertStringToPoint2D(const std::string &x_coordinate,
                            const std::string &y_coordinate,
                            Point2D &coordinate);

#endif // _COORDINATE_