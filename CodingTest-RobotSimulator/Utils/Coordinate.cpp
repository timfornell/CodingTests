#include <stdexcept>
#include <iostream>

#include "Coordinate.hpp"

/*
 * Check if provided string only consists of digits
 */
bool stringOnlyContainsDigits(std::string str)
{
   bool string_only_contains_digits = true;
   for (char c : str)
   {
      if (!isdigit(c))
      {
         string_only_contains_digits = false;
         break;
      }
   }

   return string_only_contains_digits;
}

/*
 * Try to convert a string to a digit
 *
 * Tries to convert the string to an integer with 'std::stoi'. If stoi fails,
 * cath the exception that is thrown and return false.
 *
 * Note: This treats negative numbers as invalid.
 *
 * @param str: string to be converted
 * @param coordinate: reference to int where result is saved
 *
 * @return bool representing if the conversion was successful
 */
bool convertToDigit(const std::string str, int &coordinate)
{
   bool string_was_converted = false;
   try
   {
      if (stringOnlyContainsDigits(str))
      {
         coordinate = std::stoi(str);
         string_was_converted = true;
      }
   }
   catch (const std::invalid_argument &ex)
   {
      /* Return false */
   }
   catch (const std::out_of_range &ex)
   {
      /* Return false */
   }

   return string_was_converted;
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
   const bool valid_x = convertToDigit(x_coordinate, coordinate.x);
   const bool valid_y = convertToDigit(y_coordinate, coordinate.y);

   return (valid_x && valid_y);
}