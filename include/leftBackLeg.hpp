#ifndef DEF_LEFTBACKLEG
#define DEF_LEFTBACKLEG

#include <iostream>
#include "leg.hpp"

class LeftBackLeg : public Leg {

public:

    LeftBackLeg(int servoIdCoxa = 10, int servoIdFemur = 11, int servoIdTibia = 12);
    int posReadyToWalkWait();
    int posReadyToWalk();
 
private:


};

#endif