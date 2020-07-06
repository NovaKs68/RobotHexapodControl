#ifndef DEF_CMDSERVO
#define DEF_CMDSERVO

#include <iostream>
#include "communication.hpp"

class Servo {

public:

    Servo(int id, int device);
    void READ_id();
    char WRITE_Servo_Angle(float angle, float time);

private:

    int m_device;
    int a_id;
    float a_angle;
    float a_time;
};

#endif