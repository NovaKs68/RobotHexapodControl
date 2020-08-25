#ifndef DEF_CMDSERVO
#define DEF_CMDSERVO

#include <iostream>
#include "communication.hpp"

class Servo {

public:

    Servo(int id);
    int READ_id();
    void WRITE_Servo_Angle(float angle, float time);
    void WRITE_Servo_Move_Time_Wait(float angle, float timeWait);
    void WRITE_Servo_Move_Start();
    int READ_Servo_Angle();

private:

    int m_device;
    int a_id;
    float a_angle;
    float a_time;
};

#endif