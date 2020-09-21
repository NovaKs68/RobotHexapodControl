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
    int posReadyToWalk(double timeCoxa, double timeFemur, double timeTibia);

private:
};

#endif