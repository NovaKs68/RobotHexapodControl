#ifndef DEF_RIGHTFRONTLEG
#define DEF_RIGHTFRONTLEG

#include <iostream>
#include "leg.hpp"

class RightFrontLeg : public Leg {

public:

    RightFrontLeg();
    int posReadyToWalkWait();
    int posReadyToWalk();

private:


};

#endif