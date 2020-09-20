#ifndef DEF_LEFTBACKLEG
#define DEF_LEFTBACKLEG

#include <iostream>
#include "leg.hpp"

class LeftBackLeg : public Leg
{

public:
    LeftBackLeg();
    int posReadyToWalkWait();
    int posDownToPosReadyToWalk1();
    int posDownToPosReadyToWalk2();
    int posReadyToWalk();

private:
};

#endif