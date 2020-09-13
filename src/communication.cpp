#include "communication.hpp"

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

int Communication::COM(int id, uint8_t cmdValue, int responseLen, int cmdPacketLen, uint8_t parameters[], int parametersLen)
{
    uint8_t *cmdPacket = fnctCreatePacket(id,cmdValue,parameters,parametersLen);
    write(m_device, cmdPacket, cmdPacketLen);
    // Ajouter par la suite l'écoute de la réponse qui va essayer de lire toutes les millisecondes

    uint8_t result[cmdPacketLen + responseLen];
    result[0] = 0;
    size_t nbBytes{(size_t)cmdPacketLen + responseLen};
    int readBytes{-1};
    for (int i{0}; (readBytes == -1) && i < 10; i++)
    {
        readBytes = read(m_device, result, nbBytes);
        usleep(1000); // wait 1 millisec
    }

    // readBytes = read(m_device, result, nbBytes);
    
    if (readBytes == nbBytes && result[2] == cmdPacket[2] && result[4] == cmdPacket[4]) // Test afin d'être sur que ce soit la réponse de la bonne cmd
    {
        switch (responseLen) // la valeur retournée ne dépasse jamais soit 4 ou soit 2 a tester avec servo angle read
        {
            case 1:
                std::cout << "La réponse est " << (int)result[5] << std::endl;
                return (int)result[5];
            case 2:
                //uint16_t res =(uint8_t)result[5], (uint8_t)result[6];
                return ((uint16_t)result[6]) << 8 | ((uint16_t) result[5]); // Récupération de l'octet qui combine le higher et lower bits
        }
    } else 
    {
        std::cout << "Erreur aucun packet n'a été reçus en retour ! id : " << id << std::endl;
    }
    return -1;
}

void Communication::WRITE(int id, uint8_t cmdValue, int cmdPacketLen, uint8_t parameters[], int parametersLen)
{
    std::cout << "write " << cmdValue << std::endl;
    uint8_t *cmdPacket = fnctCreatePacket(id,cmdValue,parameters,parametersLen); // write ne fonctionne plus
    write(m_device, cmdPacket, cmdPacketLen);
}

void Communication::READ(uint8_t result[], int nbBytes)
{
    read(m_device, result, nbBytes);
}

