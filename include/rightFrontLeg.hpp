#ifndef DEF_RIGHTFRONTLEG
#define DEF_RIGHTFRONTLEG

#include <iostream>
#include "leg.hpp"

class RightFrontLeg : public Leg
{

public:
    RightFrontLeg();
    int posReadyToWalkWait();
    int posDownToPosReadyToWalk1();
    int posDownToPosReadyToWalk2();
    int posReadyToWalk();

private:
};

#endif