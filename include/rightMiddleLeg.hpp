#ifndef DEF_RIGHTMIDDLELEG
#define DEF_RIGHTMIDDLELEG

#include <iostream>
#include "leg.hpp"

class RightMiddleLeg : public Leg
{

public:
    RightMiddleLeg();
    int posReadyToWalkWait();
    int posDownToPosReadyToWalk1();
    int posDownToPosReadyToWalk2();
    int posReadyToWalk();

private:
};

#endif