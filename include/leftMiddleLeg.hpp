#ifndef DEF_LEFTMIDDLELEG
#define DEF_LEFTMIDDLELEG

#include <iostream>
#include "leg.hpp"

class LeftMiddleLeg : public Leg {

public:

    LeftMiddleLeg();
    int posReadyToWalkWait();
    int posReadyToWalk();

private:


};

#endif