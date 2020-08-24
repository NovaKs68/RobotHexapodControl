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

    // TEST PATTE

    //  auto servo16{Servo(16)};
    //  auto servo17{Servo(17)};
    //  auto servo18{Servo(18)};

    // servo16.WRITE_Servo_Angle(140,0);
    // servo17.WRITE_Servo_Angle(140,0);
    // servo18.WRITE_Servo_Angle(180,0);



     // int result2 = servo2.READ_id();
     // servo2.WRITE_Servo_Angle(90,0);
     // int result1 = servo1.READ_id();
     //servo1.WRITE_Servo_Angle(0,3);
     //usleep(3000000);
     //servo1.WRITE_Servo_Angle(240,3);
     //usleep(3000000);
     //servo1.WRITE_Servo_Angle(0,3);

    auto servo1{Servo(1)};
    auto servo2{Servo(2)};
    auto servo3{Servo(3)};

    //servo1.WRITE_Servo_Angle(120,0);
    //servo2.WRITE_Servo_Angle(120,0);
    servo3.WRITE_Servo_Angle(120,0);
    //int result3 = servo3.READ_id();
    usleep(100000);
    servo3.WRITE_Servo_Angle(200,0);

     
     // std::cout << "Depuis le main on recois pour le servo 1 " << result1 << " et le servo2 " << result2 << std::endl;
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
