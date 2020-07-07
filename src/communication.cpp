#include "communication.hpp"
#include "cmdServo.hpp"

Communication Communication::m_instance=Communication();
int Communication::m_device = -1;

// FONCTIONS :

uint8_t *fnctCreatePacket(int id, uint8_t cmdValue, uint8_t parameters[], int parametersLen)
{

    // LENGTH OF PARAMETERS IS OK

    // if (parametersLen < 0 || parametersLen > 4) return false; A changer le moyen de retourner une erreur
    int packetLen = 6 + parametersLen;

    uint8_t *cmdPacket = new uint8_t[packetLen];
    cmdPacket[0] = (uint8_t)0x55;
    cmdPacket[1] = (uint8_t)0x55;
    cmdPacket[2] = (uint8_t)id;
    cmdPacket[3] = (uint8_t)(packetLen-3);
    cmdPacket[4] = (uint8_t)cmdValue;
    for (int i=0; i<parametersLen; i++) cmdPacket[5+i] = (uint8_t)parameters[i];
    std::cout << "Longueur du tableau " << (uint8_t)id << std::endl;
    // CHECKSUM :

    uint16_t cksum = {0};
    for (int i = 2; i < packetLen - 1; i++)
        cksum += cmdPacket[i];
    cmdPacket[packetLen - 1] = (uint8_t)(0xff - cksum);

    return cmdPacket;
}

// METHODES :

Communication::Communication()
{
    m_device = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY); //Open in non blocking read/write mode
    if (m_device == -1)
    {
        //ERROR - CAN'T OPEN SERIAL PORT
        std::cout << "Error - Unable to open UART.  Ensure it is not in use by another application\n" << std::endl;
    }
    
    //CONFIGURE THE UART

    struct termios options;
    tcgetattr(m_device, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD; // Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(m_device, TCIFLUSH);
    tcsetattr(m_device, TCSANOW, &options); 
}

Communication::~Communication()
{
    std::cout << "Fin de la communication" << std::endl;
}

Communication& Communication::Instance()
{
    return m_instance;
}

void Communication::COM(int id, uint8_t cmdValue, int cmdLen, uint8_t parameters[], int parametersLen)
{
    uint8_t *cmdPacket = fnctCreatePacket(id,cmdValue,parameters,parametersLen);
    write(m_device, cmdPacket, cmdLen);
}

void Communication::openUART()
{
}

