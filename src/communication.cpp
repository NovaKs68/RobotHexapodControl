#include "communication.hpp"
#include "cmdServo.hpp"

Communication::Communication(int id) : m_id{id}
{
    
}

void Communication::COM(char cmdValue, char parameters[], int parametersLen)
{
    m_cmdValue = {cmdValue};
    uint8_t cmdPacket {fnctCreatePacket(m_id,cmdValue,parameters,parametersLen)};
}


uint8_t fnctCreatePacket(int id, char cmdValue, char parameters[], int parametersLen)
{
    if (parametersLen < 0 || parametersLen > 4) return false;
    int packetLen = 6 + parametersLen;
    uint8_t cmdPacket[packetLen];
    cmdPacket[0] = 0x55;
    cmdPacket[1] = 0x55;
    cmdPacket[2] = id;
    cmdPacket[3] = packetLen-3;
    cmdPacket[4] = cmdValue;
    for (int i=0; i<parametersLen; i++) cmdPacket[5+i] = parameters[i];
    uint16_t cksum = {0};
    for (int i = 2; i < packetLen - 1; i++)
        cksum += cmdPacket[i];
    cmdPacket[packetLen - 1] = 0xff - cksum;

    return *cmdPacket;
}

