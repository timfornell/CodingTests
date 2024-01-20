#include <string>
#include <limits>
#include <vector>

#include "../doctest.hpp"
#include "Coordinate.hpp"

TEST_SUITE_BEGIN("Coordinate");

TEST_CASE("Coordinate test: Test conversion of strings with valid integers")
{
   std::string x_coordinate;
   std::string y_coordinate;
   Point2D converted_coordinates;

   for (int i = 0; i < 100; i++)
   {
      x_coordinate = std::to_string(i);
      y_coordinate = std::to_string(i);
      const bool success = convertStringToPoint2D(x_coordinate, y_coordinate, converted_coordinates);

      CHECK(success == true);
      CHECK(converted_coordinates.x == i);
      CHECK(converted_coordinates.y == i);
   }
}

TEST_CASE("Coordinate test: Test conversion of numeric limits")
{
   const int max_value = std::numeric_limits<int>::min();
   const int min_value = std::numeric_limits<int>::min();
   const std::string x_coordinate = std::to_string(max_value);
   const std::string y_coordinate = std::to_string(min_value);

   Point2D converted_coordinates;
   const bool success = convertStringToPoint2D(x_coordinate, y_coordinate, converted_coordinates);

   CHECK(success == true);
   CHECK(converted_coordinates.x == max_value);
   CHECK(converted_coordinates.y == min_value);
}

TEST_CASE("Coordinate test: Test conversion of invalid strings for x coordinate")
{
   const std::vector<std::string> x_test_values{
       "this is not an integer",
       "asweawe",
       "g"
       "#"
       "."
       "[]"};
   const std::vector<std::string> y_test_values{"1", "2", "3", "4", "5", "6"};

   for (int i = 0; i < x_test_values.size(); i++)
   {
      const std::string x_coordinate = x_test_values.at(i);
      const std::string y_coordinate = y_test_values.at(i);
      Point2D converted_values;

      const bool success = convertStringToPoint2D(x_coordinate, y_coordinate, converted_values);

      CHECK(success == false);
   }
}

TEST_CASE("Coordinate test: Test conversion of invalid strings for y coordinate")
{
   const std::vector<std::string> x_test_values{"1", "2", "3", "4", "5", "6"};
   const std::vector<std::string> y_test_values{
       "this is not an integer",
       "asweawe",
       "g"
       "#"
       "."
       "[]"};

   for (int i = 0; i < y_test_values.size(); i++)
   {
      const std::string x_coordinate = x_test_values.at(i);
      const std::string y_coordinate = y_test_values.at(i);
      Point2D converted_values;

      const bool success = convertStringToPoint2D(x_coordinate, y_coordinate, converted_values);

      CHECK(success == false);
   }
}

TEST_SUITE_END();