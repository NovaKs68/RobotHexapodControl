#ifndef DEF_ROBOTOVERALLMOVE
#define DEF_ROBOTOVERALLMOVE

#include <iostream>
#include "body.hpp"

class RobotOverallMove
{

public:
    RobotOverallMove();
    void moveStepsForward(int nbrSteps);
    void moveStepsBack(int nbrSteps);
    void moveRotateRight(int degres);
    void moveRotateLeft(int degres);


private:
};

#endif