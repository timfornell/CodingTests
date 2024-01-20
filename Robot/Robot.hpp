#ifndef _ROBOT_
#define _ROBOT_

#include <string>

#include "../TableTop/TableTop.hpp"
#include "../Utils/Coordinate.hpp"
#include "../Utils/Direction.hpp"

class Robot
{
private:
   Point2D current_position;
   Direction current_direction;
   bool activated = false;

   bool inActivatedState();
   void getCommandComponents(std::string &command, std::string &command_type, std::string &optional_command_params);
   void placeRobot(std::string parameters, const TableTop &table_top);
   bool getPlacementInformation(const std::string parameters,
                                Point2D &starting_coordinates,
                                Direction &starting_direction);
   void moveInCurrentDirection(const TableTop &table_top);
   void rotateLeft();
   void rotateRight();
   void report();

public:
   void performAction(std::string &command, const TableTop &table_top);
   Point2D getCurrentPosition();  // Currently not used
   Direction getCurrentHeading(); // Currently not used
   bool getActivationStatus();    // Currently not used
};

#endif // _ROBOT_