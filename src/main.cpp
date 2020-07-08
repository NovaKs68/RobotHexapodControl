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
    //------ TEST OBJETS ------
    //-------------------------
 
     auto servo1{Servo(1)};
     servo1.READ_id();
     // servo1.WRITE_Servo_Angle(25,1); // Place le servo à 25 degrés en 1 seconde

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

    return 0;
}

// uint8_t cmdPacketStart[6] = {0x55,0x55,0x01,0x03,0x0B,0x0F};
