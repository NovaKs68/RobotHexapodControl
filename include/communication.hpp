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
    int COM(int id,uint8_t cmdValue, int cmdLen, int responseLen, uint8_t parameters[] = 0, int parametersLen = 0);
    void WRITE(int id, uint8_t cmdValue, int cmdLen, uint8_t parameters[] = 0, int parametersLen = 0);
    void READ(uint8_t result[], int nbBytes);

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