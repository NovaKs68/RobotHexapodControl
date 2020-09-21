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
    int posReadyToWalk(double timeCoxa, double timeFemur, double timeTibia);

private:
};

#endif