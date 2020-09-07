#ifndef DEF_RIGHTMIDDLELEG
#define DEF_RIGHTMIDDLELEG

#include <iostream>
#include "leg.hpp"

class RightMiddleLeg : public Leg {

public:

    RightMiddleLeg();
    int posReadyToWalkWait();
    int posReadyToWalk();

private:


};

#endif