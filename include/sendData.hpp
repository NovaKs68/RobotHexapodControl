#ifndef DEF_SENDDATA
#define DEF_COMMUNICATION

#include <iostream>
#include "communication.hpp"

class SendData {

public:

    SendData(uint8_t cmdPacket, uint8_t cmdPacketLen);
    void COM(char cmdValue, char parameters[] = 0, int parametersLen = 0);
    char WRITE_Servo_Angle(float angle, float time);

private:

    int m_device;
    int m_id;
    char m_cmdValue;
    char m_parameters[];
};

#endif