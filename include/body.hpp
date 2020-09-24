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
    int walkRight1(); // Trois pattes se lèvent, dont 2 coté droit
    int walkRight2(); // Les trois pattes levées, avancent
    int walkRight3(); // Les trois pattes se posent
    int walkRight4(); // Les trois pattes opposées se lèvent
    int walkRight5(); // Les trois pattes se remettent dans leur pos initiale (ce qui va faire avancer le robot)
    int walkRight6(); // Les trois pattes opposées se posent

    int walkLeft1(); // Trois pattes se lèvent, dont 2 coté droit
    int walkLeft2(); // Les trois pattes levées, avancent
    int walkLeft3(); // Les trois pattes se posent
    int walkLeft4(); // Les trois pattes opposées se lèvent
    int walkLeft5(); // Les trois pattes se remettent dans leur pos initiale (ce qui va faire avancer le robot)
    int walkLeft6(); // Les trois pattes opposées se posent



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