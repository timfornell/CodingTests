#include <stdexcept>

#include "Coordinate.hpp"

/*
 * Try to convert a string to a digit
 *
 * Tries to convert the string to an integer with 'std::stoi'. If stoi fails,
 * cath the exception that is thrown and return false.
 *
 * @param str: string to be converted
 * @param coordinate: reference to int where result is saved
 *
 * @return bool representing if the conversion was successful
 */
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

/*
 * Convert x and y coordinates from strings to Point2D
 *
 * @param x_coordinate: string containing an x coordinate
 * @param y_coordinate: string containing an y coordinate
 * @param coordinate: reference to a Point2D where result is saved
 *
 * @return bool representing if the conversion was successful or not
 */
bool convertStringToPoint2D(const std::string &x_coordinate,
                            const std::string &y_coordinate,
                            Point2D &coordinate)
{
   const bool valid_x = convert_to_digit(x_coordinate, coordinate.x);
   const bool valid_y = convert_to_digit(y_coordinate, coordinate.y);

   return (valid_x && valid_y);
}