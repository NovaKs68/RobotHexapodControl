#include "communication.hpp"
#include "cmdServo.hpp"

int Communication::m_device = -1;

Communication::Communication(int id, int device) : m_id{id}
{
    
}

void Communication::COM(char cmdValue, char parameters[], int parametersLen)
{
    // uint8_t cmdPacket {fnctCreatePacket(m_id,cmdValue,parameters,parametersLen)};
    
}

void Communication::openUART(int test)
{
    if (m_device == -1) // Permet d'ouvrir le port qu'une seule fois 
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
}


uint8_t fnctCreatePacket(int id, char cmdValue, char parameters[], int parametersLen)
{

    // LENGTH OF PARAMETERS IS OK

    if (parametersLen < 0 || parametersLen > 4) return false;
    int packetLen = 6 + parametersLen;

    uint8_t cmdPacket[packetLen];
    cmdPacket[0] = 0x55;
    cmdPacket[1] = 0x55;
    cmdPacket[2] = id;
    cmdPacket[3] = packetLen-3;
    cmdPacket[4] = cmdValue;
    for (int i=0; i<parametersLen; i++) cmdPacket[5+i] = parameters[i];

    // CHECKSUM :

    uint16_t cksum = {0};
    for (int i = 2; i < packetLen - 1; i++)
        cksum += cmdPacket[i];
    cmdPacket[packetLen - 1] = 0xff - cksum;

    return *cmdPacket;
}

