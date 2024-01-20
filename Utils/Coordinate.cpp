#include <stdexcept>

#include "Coordinate.hpp"

bool convert_to_digit(const std::string str, int &coordinate)
{
   try
   {
      coordinate = std::stoi(str);
      return true;
   }
   catch (const std::invalid_argument &ex)
   {
      return false;
   }
   catch (const std::out_of_range &ex)
   {
      return false;
   }
}

bool convertStringToPoint2D(const std::string &x_coordinate,
                            const std::string &y_coordinate,
                            Point2D &coordinate)
{
   const bool valid_x = convert_to_digit(x_coordinate, coordinate.x);
   const bool valid_y = convert_to_digit(y_coordinate, coordinate.y);

   return (valid_x && valid_y);
}