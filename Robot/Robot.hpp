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
   bool activated;

   bool inActivatedState();
   bool commandIsValid(std::string &command);
   void report();

public:
   bool performAction(std::string &command, const TableTop &table_top);
   Point2D getCurrentPosition();  // Currently not used
   Direction getCurrentHeading(); // Currently not used
   bool getActivationStatus();    // Currently not used
};

#endif // _ROBOT_