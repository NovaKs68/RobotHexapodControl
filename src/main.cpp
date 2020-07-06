// robotHexapod.cpp : Ce fichier contient la fonction 'main'.

#include <iostream>
#include "cmdServo.hpp"
#include "communication.hpp"
#include <fcntl.h>   // Contient O_RDWR
#include <unistd.h>  // write(), read(), close()
#include <termios.h> // Pour paramétrer le port dont le baud rate

// Prototype de la fonction  :

uint8_t checksum(uint8_t *fram, uint8_t buflen);

int main()
{

    std::cout << "Debut du programme !" << std::endl;

    //-------------------------
    //----- SETUP USART 0 -----
    //-------------------------

    //At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
    int device = -1;

    //OPEN THE UART

    device = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY); //Open in non blocking read/write mode
    if (device == -1)
    {

        //ERROR - CAN'T OPEN SERIAL PORT
        std::cout << "Error - Unable to open UART.  Ensure it is not in use by another application\n" << std::endl;
    }

    //CONFIGURE THE UART

    struct termios options;
    tcgetattr(device, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD; // Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(device, TCIFLUSH);
    tcsetattr(device, TCSANOW, &options);

    //-------------------------
    //------ TEST OBJETS ------
    //-------------------------

    auto servo1{Servo(2,device)};
    servo1.READ_id();

    //-------------------------
    //------ DEFINITIONS ------
    //-------------------------

    int const tailleTableau{10};
    uint8_t cks{0};
    unsigned char lsbAngle{0}, msbAngle{0}, lsbTime{0}, msbTime{0};
    float angle{240.0}, time{3.0}; // In degres and angles

    uint8_t cmdPacket[] = {0x55, 0x55, 0x01, 0x07, 0x01, 0x05, 0x09, 0x00, 0x00, 0x00};          // MOVE SERVO NOT FUNCTIONAL
    uint8_t cmdPacketId[6] = {0x55, 0x55, 0x01, 0x03, 0x0E, 0xeb};                               // READ ID FUNCTIONAL
    uint8_t test1[tailleTableau] = {0x55, 0x55, 0x01, 0x07, 0x01, 0x05, 0x09, 0x00, 0x00, 0x00}; // MOVE SERVO FUNCTIONAL
    // Doit retrouner : 0x55, 0x55, 0x01, 0x07, 0x01, 3c, 0x00, 0x00, 0x00, 0x45;
    // Devrait être bon avec un déplacement de 60/1000 en 0 millis le checksum fait donc 69 (à tester)

    //-------------------------
    //--------- VALUE ---------
    //-------------------------

    // ANGLE :

    // Je limite la course à 0 – 240.0

    if (angle > 240.0)
        angle = 240.0;
    else if (angle < 0.0)
        angle = 0.0;

    Communication::openUART(3);
    Communication::openUART(6);
    

    // Je commence par calculer avec des flottants pour garder la précision

    float valueAngleF = angle / 0.24;

    // Je caste dans un entier court non signé

    unsigned short valueAngleUs = (unsigned short)valueAngleF;
    std::cout << "VALUE : " << valueAngleUs << std::endl;

    // Je calcule le poids faible

    lsbAngle = (uint8_t)(valueAngleUs & (uint16_t)0x00FF);

    // Je calcule le poids fort

    msbAngle = (uint8_t)((valueAngleUs & (uint16_t)0xFF00) >> 8);

    // BIG ENDIAN
    cmdPacket[6] = msbAngle;
    cmdPacket[5] = lsbAngle;
    std::cout << "MSBANGLE : " << std::dec << (int)msbAngle << "LSBANGLE : " << std::dec << (int)lsbAngle << std::endl;

    // TIME :

    if (angle > 3.0)
        angle = 3.0;
    else if (angle < 0.0)
        angle = 0.0;

    float valueTimeF = time * 1000;

    unsigned short valueTimeUs = (unsigned short)valueTimeF;

    lsbTime = (uint8_t)(valueTimeUs & (uint16_t)0x00FF);

    //// Je calcule le poids faible de time

    msbTime = (uint8_t)((valueTimeUs & (uint16_t)0xFF00) >> 8);

    // BIG ENDIAN
    cmdPacket[8] = msbTime;
    cmdPacket[7] = lsbTime;

    // CHECKSUM :

    checksum(cmdPacketId, 6);
    checksum(test1, tailleTableau);
    checksum(cmdPacket, tailleTableau);

    //-------------------------
    //------ SEND PACKET ------
    //-------------------------

    // write(device, test1, tailleTableau);
    write(device, cmdPacket, tailleTableau);
    // write( device, cmdPacketId, 6) ;

    close(device); // Fermeture du port

    return 0;
}

uint8_t checksum(uint8_t *buf, uint8_t buflen)
{
    uint16_t cksum = {0};

    for (int i = 2; i < buflen - 1; i++)
        cksum += buf[i];
    buf[buflen - 1] = 0xff - cksum;

    return ~cksum;
}

// uint8_t cmdPacketStart[6] = {0x55,0x55,0x01,0x03,0x0B,0x0F};
// usleep(1000000); // wait 1 seconde