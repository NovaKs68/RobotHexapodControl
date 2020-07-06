#ifndef DEF_COMMUNICATION
#define DEF_COMMUNICATION

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "cmdServo.hpp"

class Communication {

public:

    Communication(int id, int device);
    void COM(char cmdValue, char parameters[] = 0, int parametersLen = 0);
    char WRITE_Servo_Angle(float angle, float time);
    static void openUART(int test);

private:

    int m_id;
    char m_cmdValue;
    char m_parameters[];
    static int m_device;
};

#endif