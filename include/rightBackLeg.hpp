#ifndef DEF_RIGHTBACKLEG
#define DEF_RIGHTBACKLEG

#include <iostream>
#include "leg.hpp"

class RightBackLeg : public Leg
{

public:
    RightBackLeg();
    int posReadyToWalkWait();
    int posDownToPosReadyToWalk1();
    int posReadyToWalk(double timeCoxa, double timeFemur, double timeTibia);

private:
};

#endif