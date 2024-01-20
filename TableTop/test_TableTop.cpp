#include <vector>

#include "../doctest.hpp"
#include "TableTop.hpp"

TEST_SUITE_BEGIN("TableTop");

TEST_CASE("TableTop: Test TableTop initialization with invalid sizes")
{
   const int table_width = -5;
   const int table_height = -5;
   TableTop table(table_width, table_height);

   struct TestVector
   {
      Point2D input_coordinates;
      bool expected_success;
   };

   std::vector<TestVector> test_input{
       {{0, 0}, false},
       {{1, 1}, false},
   };

   for (auto test_vector : test_input)
   {
      const bool coordinate_is_valid = table.coordinateIsValid(test_vector.input_coordinates);

      CHECK(coordinate_is_valid == test_vector.expected_success);
   }
}

TEST_CASE("TableTop: Test coordinateIsValid")
{
   // Valid coordinates are [0, width - 1], [0, height - 1]
   const int table_width = 5;
   const int table_height = 5;
   TableTop table(table_width, table_height);

   struct TestVector
   {
      Point2D input_coordinates;
      bool expected_success;
   };

   std::vector<TestVector> test_input{
       {{0, 0}, true},
       {{2, 2}, true},
       {{table_width - 1, table_height - 1}, true},
       {{table_width, table_height}, false},
       {{-1, 2}, false},
       {{-1, -2}, false},
       {{2, -2}, false},
   };

   for (auto test_vector : test_input)
   {
      const bool coordinate_is_valid = table.coordinateIsValid(test_vector.input_coordinates);

      CHECK(coordinate_is_valid == test_vector.expected_success);
   }
}

TEST_SUITE_END();