#ifndef DEF_CMDSERVO
#define DEF_CMDSERVO

#include <iostream>
#include <cstdint>
#include <array>
#include "communication.hpp"

class Servo {

public:

    Servo(int id);
    int READ_id();
    void WRITE_Servo_Angle(float angle, float time);
    void WRITE_Servo_Move_Time_Wait(float angle, float timeWait);
    void WRITE_Servo_Move_Start();
    void WRITE_Servo_Offset_Adjust(float angle);
    int READ_Servo_Angle();
    //static bool fileAttenteIndex(int,int);

private:

    int a_id;
    static int m_fileAttenteIndex[2]; // La première valeur du tableau est l'index du servo en attente et la deuxième est l'index du servo qui va passer
};

#endif