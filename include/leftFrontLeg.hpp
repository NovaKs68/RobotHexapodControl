#ifndef DEF_LEFTFRONTLEG
#define DEF_LEFTFRONTLEG

#include <iostream>
#include "leg.hpp"

class LeftFrontLeg : public Leg
{

public:
    LeftFrontLeg();
    int posReadyToWalkWait();
    int posDownToPosReadyToWalk1();
    int posDownToPosReadyToWalk2();
    int posReadyToWalk();

private:
};

#endif