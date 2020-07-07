#ifndef DEF_COMMUNICATION
#define DEF_COMMUNICATION

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "cmdServo.hpp"

class Communication {

public:


    // Constructeur singlton
    static Communication& Instance();

    // Objects
    void COM(int id,char cmdValue, char parameters[] = 0, int parametersLen = 0);
    char WRITE_Servo_Angle(float angle, float time);
    static void openUART();

private:

    // singlton
    Communication& operator= (const Communication&);
    Communication (const Communication&);

    static Communication m_instance;
    Communication();
    ~Communication();

    int m_id;
    char m_cmdValue;
    char m_parameters[];
    static int m_device;
};

#endif