#ifndef DEF_LEFTMIDDLELEG
#define DEF_LEFTMIDDLELEG

#include <iostream>
#include "leg.hpp"

class LeftMiddleLeg : public Leg
{

public:
    LeftMiddleLeg();
    int posReadyToWalkWait();
    int posDownToPosReadyToWalk1();
    int posDownToPosReadyToWalk2();
    int posReadyToWalk();

private:
};

#endif