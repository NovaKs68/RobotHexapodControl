#ifndef DEF_BODY
#define DEF_BODY

#include <iostream>
#include <fstream>
#include <string>
#include "leg.hpp"
#include "leftBackLeg.hpp"
#include "leftFrontLeg.hpp"
#include "leftMiddleLeg.hpp"
#include "rightBackLeg.hpp"
#include "rightFrontLeg.hpp"
#include "rightMiddleLeg.hpp"

// Devra prendre en compte quand les pos on pu etre effectués et quand l'envoi d'ordre ne s'est pas fait
class Body
{

public:
    // Constructeur singlton
    static Body &Instance();

    void bodyPosReadyToWalk();
    void bodyPosDownToPosReadyToWalk();
    void bodyPosDown();

private:
    // singleton
    Body &operator=(const Body &);
    Body(const Body &);
    static Body m_instance;
    Body();
    ~Body();

    // Methode/Fonction 
    bool bodyAction(); // true si l'action s'est bien passé et false si la pos n'a pas pu se faire

    std::ofstream m_fluxError;
    std::string m_bodyPosCurrent; // posDown, posReadyToWalk

    RightFrontLeg m_leg1;
    RightMiddleLeg m_leg2;
    RightBackLeg m_leg3;
    LeftBackLeg m_leg4;
    LeftMiddleLeg m_leg5;
    LeftFrontLeg m_leg6;
};

#endif