#ifndef DEF_COMMUNICATION
#define DEF_COMMUNICATION

#include <iostream>
#include "cmdServo.hpp"

class Communication {

public:

    Communication(int id, int device);
    void COM(char cmdValue, char parameters[] = 0, int parametersLen = 0);
    char WRITE_Servo_Angle(float angle, float time);

private:

    int m_device;
    int m_id;
    char m_cmdValue;
    char m_parameters[];
};

#endif