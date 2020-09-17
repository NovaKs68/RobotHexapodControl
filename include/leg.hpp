#ifndef DEF_LEG
#define DEF_LEG

#include <iostream>
#include "cmdServo.hpp"
#include "board.hpp" 

class Leg {

public:

    Leg(int servoIdCoxa, int servoIdFemur, int servoIdTibia);
    int start(); // Devra retourner 1 quand il aura fini
    int currentPos(); // Devra retourner les positions du coxa, femur, tibia // Pas fonctionnel probleme : return un array
    int posDownWait(); // Devra retourer 1 quand il sera prêt
    int posDown(); // Retourne 1 quand l'action est fini et 0 lorsqu'il y a eu un problème et que le mouvement n'a pas pu être fait
    void angleAdjuste(int angleAdjusteServoCoxa, int angleAdjusteServoFemur, int angleAdjusteServoTibia); // Va permettre d'ajuster temporairement l'angle des servos de la patte
    bool getMoveFinished();

protected:

    int m_servoIdCoxa; 
    Servo m_servoCoxa;
    int m_servoIdFemur;
    Servo m_servoFemur;
    int m_servoIdTibia;
    Servo m_servoTibia;
    Servo m_servos; // Rendre cette objet idem pour tous les objets (faire un attribut static)

    bool m_accessCom; // Va être false lorsqu'il sera utilisé et true quand board pourra faire des requêtes


};

#endif