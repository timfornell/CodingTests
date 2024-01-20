#include <vector>

#include "../TestFramework/doctest.hpp"
#include "Direction.hpp"

TEST_SUITE_BEGIN("Direction");

TEST_CASE("Direction test: Test conversion of string to Direction")
{
   struct TestVector
   {
      std::string input_direction;
      Direction expected_direction;
      bool expected_success;
   };

   std::vector<TestVector> test_values = {
       {"NORTH", Direction::North, true},
       {"North", Direction::North, false},
       {"north", Direction::North, false},
       {"EAST", Direction::East, true},
       {"East", Direction::East, false},
       {"east", Direction::East, false},
       {"SOUTH", Direction::South, true},
       {"South", Direction::South, false},
       {"south", Direction::South, false},
       {"WEST", Direction::West, true},
       {"West", Direction::West, false},
       {"west", Direction::West, false},
       {"invalid_direction", Direction::West, false}, // Expected direction does not matter
   };

   for (auto test_vector : test_values)
   {
      Direction new_direction;
      const bool success = convertStringToDirection(test_vector.input_direction, new_direction);

      if (test_vector.expected_success)
      {
         CHECK(success == true);
         CHECK(new_direction == test_vector.expected_direction);
      }
      else
      {
         CHECK(success == false);
         // new_direction should not be set
      }
   }
}

TEST_CASE("Direction test: Test rotation of direction counterclockwise")
{
   struct TestVector
   {
      Direction input_direction;
      Direction expected_direction;
   };

   std::vector<TestVector> test_values = {
       {Direction::North, Direction::West},
       {Direction::East, Direction::North},
       {Direction::South, Direction::East},
       {Direction::West, Direction::South},
   };

   for (auto test_vector : test_values)
   {
      const Direction new_direction = rotateDirectionLeft(test_vector.input_direction);

      CHECK(new_direction == test_vector.expected_direction);
   }
}

TEST_CASE("Direction test: Test rotation of direction clockwise")
{
   struct TestVector
   {
      Direction input_direction;
      Direction expected_direction;
   };

   std::vector<TestVector> test_values = {
       {Direction::North, Direction::East},
       {Direction::East, Direction::South},
       {Direction::South, Direction::West},
       {Direction::West, Direction::North},
   };

   for (auto test_vector : test_values)
   {
      const Direction new_direction = rotateDirectionRight(test_vector.input_direction);

      CHECK(new_direction == test_vector.expected_direction);
   }
}

TEST_CASE("Direction test: Test conversion of direction to movement components")
{
   struct TestVector
   {
      Direction direction;
      Point2D expected_output;
   };

   std::vector<TestVector> test_values = {
       {Direction::North, {1, 0}},
       {Direction::East, {0, 1}},
       {Direction::South, {-1, 0}},
       {Direction::West, {0, -1}},
   };

   for (auto test_vector : test_values)
   {
      const Point2D components = convertDirectionToMovementDirection(test_vector.direction);

      CHECK(components.x == test_vector.expected_output.x);
      CHECK(components.y == test_vector.expected_output.y);
   }
}

TEST_CASE("Direction test: Test conversion of direction to string")
{
   struct TestVector
   {
      Direction direction;
      std::string expected_output;
   };

   std::vector<TestVector> test_values = {
       {Direction::North, "North"},
       {Direction::East, "East"},
       {Direction::South, "South"},
       {Direction::West, "West"},
   };

   for (auto test_vector : test_values)
   {
      const std::string direction_as_string = toString(test_vector.direction);

      CHECK(direction_as_string == test_vector.expected_output);
   }
}

TEST_SUITE_END();