#ifndef DEF_LEG
#define DEF_LEG

#include <iostream>
#include "cmdServo.hpp"

class Leg {

public:

    Leg(int servoIdCoxa, int servoIdFemur, int servoIdTibia);
    int start(); // Devra retourner 1 quand il aura fini
    int currentPos(); // Devra retourner les positions du coxa, femur, tibia
    int posDownWait(); // Devra retourer 1 quand il sera prêt
    int posDown(); // Devra retourner 1 quand il aura fini

protected:

    int m_servoIdCoxa;
    Servo m_servoCoxa;
    int m_servoIdFemur;
    Servo m_servoFemur;
    int m_servoIdTibia;
    Servo m_servoTibia;
    Servo m_servos; // Rendre cette objet idem pour tous les objets


};

#endif