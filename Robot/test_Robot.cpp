#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "../doctest.hpp"
#include "Robot.hpp"
#include "../TableTop/TableTop.hpp"

TEST_SUITE_BEGIN("Robot");

class RobotTestClass
{
public:
   const int table_width = 5;
   const int table_height = 5;
   const TableTop table = TableTop(table_width, table_height);
   Robot robot;

   struct TestVector
   {
      std::string input_string;
      Point2D expected_position;
      Direction expected_direction;
      bool expected_activation_status;
   };

   void run_and_assert(const std::vector<TestVector> &test_input)
   {
      for (auto test_vector : test_input)
      {
         robot.performAction(test_vector.input_string, table);

         CHECK(test_vector.expected_position.x == robot.getCurrentPosition().x);
         CHECK(test_vector.expected_position.y == robot.getCurrentPosition().y);
         CHECK(test_vector.expected_direction == robot.getCurrentDirection());
         CHECK(test_vector.expected_activation_status == robot.getActivationStatus());
      }
   }
};

TEST_CASE_FIXTURE(RobotTestClass, "Robot: Test PLACE command")
{
   std::vector<TestVector> test_input{
       {"PLACE 1,0,WEST", {1, 0}, Direction::West, true},
       {"PLACE -1,-1,NORTH", {1, 0}, Direction::West, true}, // Invalid position -> should remain
       {"PLACE 1,0,NORTH", {1, 0}, Direction::North, true},
       {"PLACE 5,5,NORTH", {1, 0}, Direction::North, true}, // Invalid position
       {"PLACE 4,4,SOUTH", {4, 4}, Direction::South, true},
       {"PLACE 1,1,4,SOUTH", {4, 4}, Direction::South, true}, // Invalid command -> should remain
   };

   RobotTestClass::run_and_assert(test_input);
}

TEST_CASE_FIXTURE(RobotTestClass, "Robot: Test LEFT and RIGHT commands")
{
   std::vector<TestVector> test_input{
       {"PLACE 1,0,WEST", {1, 0}, Direction::West, true}, // Initialize
       {"LEFT", {1, 0}, Direction::South, true},
       {"LEFT", {1, 0}, Direction::East, true},
       {"LEFT", {1, 0}, Direction::North, true},
       {"LEFT", {1, 0}, Direction::West, true},
       {"RIGHT", {1, 0}, Direction::North, true},
       {"RIGHT", {1, 0}, Direction::East, true},
       {"RIGHT", {1, 0}, Direction::South, true},
       {"RIGHT", {1, 0}, Direction::West, true},
   };

   RobotTestClass::run_and_assert(test_input);
}

TEST_CASE_FIXTURE(RobotTestClass, "Robot: Test MOVE command")
{
   std::vector<TestVector> test_input{
       {"PLACE 2,2,WEST", {2, 2}, Direction::West, true}, // Initialize
       {"MOVE", {1, 2}, Direction::West, true},
       {"MOVE", {0, 2}, Direction::West, true},
       {"RIGHT", {0, 2}, Direction::North, true},
       {"MOVE", {0, 3}, Direction::North, true},
       {"MOVE", {0, 4}, Direction::North, true},
       {"MOVE", {0, 4}, Direction::North, true}, // Invalid movement
       {"RIGHT", {0, 4}, Direction::East, true},
       {"MOVE", {1, 4}, Direction::East, true},
       {"MOVE", {2, 4}, Direction::East, true},
       {"MOVE", {3, 4}, Direction::East, true},
       {"MOVE", {4, 4}, Direction::East, true},
       {"MOVE", {4, 4}, Direction::East, true}, // Invalid command
   };

   RobotTestClass::run_and_assert(test_input);
}

TEST_CASE_FIXTURE(RobotTestClass, "Robot: Test special cases")
{
   std::vector<TestVector> test_input{
       {"PLACE  2,2,WEST", {0, 0}, Direction::West, false},
       {"PLACE 2,2, WEST", {2, 2}, Direction::West, true},
   };

   RobotTestClass::run_and_assert(test_input);
}

TEST_SUITE_END();