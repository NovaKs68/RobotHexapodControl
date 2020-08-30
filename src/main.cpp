// robotHexapod.cpp : Ce fichier contient la fonction 'main'.

#include <iostream>
#include "cmdServo.hpp"
#include "leg.hpp"
#include <fcntl.h>   // Contient O_RDWR
#include <unistd.h>  // write(), read(), close()
#include <termios.h> // Pour paramétrer le port dont le baud rate


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


    auto leg1{Leg(1,2,3)};
    auto leg2{Leg(4,5,6)}; 
    auto leg3{Leg(7,8,9)};
    auto leg4{Leg(10,11,12)};
    auto leg5{Leg(13,14,15)};
    auto leg6{Leg(16,17,18)};
    leg1.posDown();
    leg2.posDown();
    leg3.posDown();
    leg4.posDown();
    leg5.posDown();
    leg6.posDown();


     // int result2 = servo2.READ_id();
     // servo2.WRITE_Servo_Angle(90,0);
     // int result1 = servo1.READ_id();
     //servo1.WRITE_Servo_Angle(0,3);
     //usleep(3000000);
     //servo1.WRITE_Servo_Angle(240,3);
     //usleep(3000000);
     //servo1.WRITE_Servo_Angle(0,3);

//     auto servo1{Servo(1)};
//     auto servo2{Servo(2)};
//     auto servo3{Servo(3)};
//     auto servo4{Servo(4)};
//     auto servo5{Servo(5)};
//     auto servo6{Servo(6)};
//     auto servo7{Servo(7)};
//     auto servo8{Servo(8)};
//     auto servo9{Servo(9)};
//     auto servo10{Servo(10)};
//     auto servo11{Servo(11)};
//     auto servo12{Servo(12)};
//     auto servo13{Servo(13)};
//     auto servo14{Servo(14)};
//     auto servo15{Servo(15)};
//     auto servo16{Servo(16)};
//     auto servo17{Servo(17)};
//     auto servo18{Servo(18)};

   
// usleep(3000000);
//     servo1.WRITE_Servo_Angle(120,0);
//     servo2.WRITE_Servo_Angle(80,0);
//     servo3.WRITE_Servo_Angle(60,0);
//     servo4.WRITE_Servo_Angle(120,0);
//     servo5.WRITE_Servo_Angle(80,0);
//     servo6.WRITE_Servo_Angle(40,0);
//     servo7.WRITE_Servo_Angle(120,0);
//     servo8.WRITE_Servo_Angle(80,0);
//     servo9.WRITE_Servo_Angle(60,0);
//     servo10.WRITE_Servo_Angle(120,0);
//     servo11.WRITE_Servo_Angle(80,0);
//     servo12.WRITE_Servo_Angle(60,0);
//     servo13.WRITE_Servo_Angle(120,0);
//     servo14.WRITE_Servo_Angle(80,0);
//     servo15.WRITE_Servo_Angle(40,0);
//     servo16.WRITE_Servo_Angle(120,0);
//     servo17.WRITE_Servo_Angle(80,0);
//     servo18.WRITE_Servo_Angle(60,0);

    // auto servo254{Servo(254)};
    // auto servo4{Servo(4)};
    // auto servo5{Servo(5)};
    // auto servo6{Servo(6)};

    // servo4.WRITE_Servo_Move_Time_Wait(120,0);
    // servo5.WRITE_Servo_Move_Time_Wait(120,0);
    // servo6.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(3000000);
    // servo254.WRITE_Servo_Move_Start();

     
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
