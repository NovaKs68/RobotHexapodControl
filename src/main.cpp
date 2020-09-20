// robotHexapod.cpp : Ce fichier contient la fonction 'main'.

#include <iostream>
#include "cmdServo.hpp"
#include "body.hpp"
#include "board.hpp"
#include <pthread.h>
#include <fcntl.h>   // Contient O_RDWR
#include <unistd.h>  // write(), read(), close()
#include <termios.h> // Pour paramétrer le port dont le baud rate
#include <thread>    // A mettre dans le body par la suite
// #include <chrono>

int main()
{
    std::cout << "Debut du programme !" << std::endl;
    Body &body = Body::Instance();
    while (1)
    {
        body.bodyPosDown();
        body.bodyPosReadyToWalk();
        usleep(80000);
    }

    //-------------------------
    //------- TEST BODY -------
    //-------------------------

    // auto leg1{RightFrontLeg()};
    // auto leg2{RightMiddleLeg()};
    // auto leg3{RightBackLeg()};
    // auto leg4{LeftBackLeg()};
    // auto leg5{LeftMiddleLeg()};
    // auto leg6{LeftFrontLeg()};

    // leg1.posDown();
    // leg2.posDown();
    // leg3.posDown();
    // leg4.posDown();
    // leg5.posDown();
    // leg6.posDown();
    // usleep(1000000);

    // leg1.posReadyToWalk();
    // leg2.posReadyToWalk();
    // leg3.posReadyToWalk();
    // leg4.posReadyToWalk();
    // leg5.posReadyToWalk();
    // leg6.posReadyToWalk();
    // usleep(300000);

    // leg1.posDown();
    // leg2.posDown();
    // leg3.posDown();
    // leg4.posDown();
    // leg5.posDown();
    // leg6.posDown();
    // usleep(300000);

    // leg1.posReadyToWalk();
    // leg2.posReadyToWalk();
    // leg3.posReadyToWalk();
    // leg4.posReadyToWalk();
    // leg5.posReadyToWalk();
    // leg6.posReadyToWalk();
    // usleep(10000000);

    //-------------------------
    //------- TEST LEGS -------
    //-------------------------

    //  auto servo16{Servo(16)};
    //  auto servo17{Servo(17)};
    //  auto servo18{Servo(18)};

    // servo16.WRITE_Servo_Angle(140,0);
    // servo17.WRITE_Servo_Angle(140,0);
    // servo18.WRITE_Servo_Angle(180,0);

    // auto leg1{Leg(1,2,3)};
    // auto leg2{Leg(4,5,6)};
    // auto leg3{Leg(7,8,9)};
    // usleep(80000);
    // auto leg4{LeftBackLeg()};
    // auto leg5{Leg(13,14,15)};
    // auto leg6{Leg(16,17,18)};
    // leg1.posDownWait();
    // leg2.posDownWait();
    // leg3.posDownWait();
    // leg4.posReadyToWalk();
    // leg5.posDownWait();
    // leg6.posDownWait();
    // leg1.start();

    // int result2 = servo2.READ_id();
    // servo2.WRITE_Servo_Angle(90,0);
    // int result1 = servo1.READ_id();
    //servo1.WRITE_Servo_Angle(0,3);
    //usleep(3000000);
    //servo1.WRITE_Servo_Angle(240,3);
    //usleep(3000000);
    //servo1.WRITE_Servo_Angle(0,3);

    //-------------------------
    //------ TEST SERVOS ------
    //-------------------------

    // auto servo1{Servo(1)};
    // auto servo2{Servo(2)};
    // auto servo3{Servo(3)};
    // auto servo4{Servo(4)};
    // auto servo5{Servo(5)};
    // auto servo6{Servo(6)};
    // auto servo7{Servo(7)};
    // auto servo8{Servo(8)};
    // auto servo9{Servo(9)};
    // auto servo10{Servo(10)};
    // auto servo11{Servo(11)};
    // auto servo12{Servo(12)};
    // auto servo13{Servo(13)};
    // auto servo14{Servo(14)};
    // auto servo15{Servo(15)};
    // auto servo16{Servo(16)};
    // auto servo17{Servo(17)};
    // auto servo18{Servo(18)};
    // auto servo254{Servo(254)};

    // Pour connaitre le temps que prends un COM d'un servo :

    // std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    // int a = servo1.READ_Servo_Angle();
    // std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    // int elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    // std::cout << "Result: " << a << ", elapsed time: " << elapsed_seconds << "microsec" << std::endl;

    // while(1)
    // {

    // int a = servo1.READ_Servo_Angle();
    // int b = servo2.READ_Servo_Angle();
    // int c = servo3.READ_Servo_Angle();
    // int d = servo4.READ_Servo_Angle();
    // int e = servo5.READ_Servo_Angle();
    // int f = servo6.READ_Servo_Angle();
    // int g = servo7.READ_Servo_Angle();
    // int h = servo8.READ_Servo_Angle();
    // int i = servo9.READ_Servo_Angle();
    // int j = servo10.READ_Servo_Angle();
    // int k = servo11.READ_Servo_Angle();
    // int l = servo12.READ_Servo_Angle();
    // int m = servo13.READ_Servo_Angle();
    // int n = servo14.READ_Servo_Angle();
    // int o = servo15.READ_Servo_Angle();
    // int p = servo16.READ_Servo_Angle();
    // int q = servo17.READ_Servo_Angle();
    // int r = servo18.READ_Servo_Angle();

    // std::cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << " " << h << " " << i << " " << j << " " << k << " " << l << " " << m << " " << n << " " << o << " " << p << " " << q << " " << r << std::endl;
    // }

    // POS ADJUST TIBIA

    // servo1.WRITE_Servo_Angle(120,0);
    // servo2.WRITE_Servo_Angle(30,0);
    // servo3.WRITE_Servo_Angle(90,0);
    // servo4.WRITE_Servo_Angle(120,0);
    // servo5.WRITE_Servo_Angle(30,0);
    // servo6.WRITE_Servo_Angle(90,0);
    // servo7.WRITE_Servo_Angle(120,0);
    // servo8.WRITE_Servo_Angle(30,0);
    // servo9.WRITE_Servo_Angle(90,0);
    // servo10.WRITE_Servo_Angle(120,0);
    // servo11.WRITE_Servo_Angle(30,0);
    // servo12.WRITE_Servo_Angle(90,0);
    // servo13.WRITE_Servo_Angle(120,0);
    // servo14.WRITE_Servo_Angle(30,0);
    // servo15.WRITE_Servo_Angle(90,0);
    // servo16.WRITE_Servo_Angle(120,0);
    // servo17.WRITE_Servo_Angle(30,0);
    // servo18.WRITE_Servo_Angle(90,0);

    // POS ADJUST FEMUR

    // servo1.WRITE_Servo_Angle(120,0);
    // servo2.WRITE_Servo_Angle(120,0);
    // servo3.WRITE_Servo_Angle(90,0);
    // servo4.WRITE_Servo_Angle(120,0);
    // servo5.WRITE_Servo_Angle(120,0);
    // servo6.WRITE_Servo_Angle(90,0);
    // servo7.WRITE_Servo_Angle(120,0);
    // servo8.WRITE_Servo_Angle(120,0);
    // servo9.WRITE_Servo_Angle(90,0);
    // servo10.WRITE_Servo_Angle(120,0);
    // servo11.WRITE_Servo_Angle(120,0);
    // servo12.WRITE_Servo_Angle(90,0);
    // servo13.WRITE_Servo_Angle(120,0);
    // servo14.WRITE_Servo_Angle(120,0);
    // servo15.WRITE_Servo_Angle(90,0);
    // servo16.WRITE_Servo_Angle(120,0);
    // servo17.WRITE_Servo_Angle(120,0);
    // servo18.WRITE_Servo_Angle(90,0);

    // servo1.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo2.WRITE_Servo_Move_Time_Wait(80,0);
    // usleep(10000);
    // servo3.WRITE_Servo_Move_Time_Wait(60,0);
    // usleep(10000);
    // servo4.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo5.WRITE_Servo_Move_Time_Wait(80,0);
    // usleep(10000);
    // servo6.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);
    // servo7.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo8.WRITE_Servo_Move_Time_Wait(80,0);
    // usleep(10000);
    // servo9.WRITE_Servo_Move_Time_Wait(60,0);
    // usleep(10000);
    // servo10.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo11.WRITE_Servo_Move_Time_Wait(80,0);
    // usleep(10000);
    // servo12.WRITE_Servo_Move_Time_Wait(60,0);
    // usleep(10000);
    // servo13.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo14.WRITE_Servo_Move_Time_Wait(80,0);
    // usleep(10000);
    // servo15.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);
    // servo16.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo17.WRITE_Servo_Move_Time_Wait(80,0);
    // usleep(10000);
    // servo18.WRITE_Servo_Move_Time_Wait(60,0);
    // usleep(10000);

    // servo254.WRITE_Servo_Move_Start();

    // servo1.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo2.WRITE_Servo_Move_Time_Wait(100,0);
    // usleep(10000);
    // servo3.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);
    // servo4.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo5.WRITE_Servo_Move_Time_Wait(100,0);
    // usleep(10000);
    // servo6.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);
    // servo7.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo8.WRITE_Servo_Move_Time_Wait(100,0);
    // usleep(10000);
    // servo9.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);
    // servo10.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo11.WRITE_Servo_Move_Time_Wait(100,0);
    // usleep(10000);
    // servo12.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);
    // servo13.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo14.WRITE_Servo_Move_Time_Wait(100,0);
    // usleep(10000);
    // servo15.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);
    // servo16.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(10000);
    // servo17.WRITE_Servo_Move_Time_Wait(100,0);
    // usleep(10000);
    // servo18.WRITE_Servo_Move_Time_Wait(40,0);
    // usleep(10000);

    // servo254.WRITE_Servo_Move_Start();

    // auto servo254{Servo(254)};
    // auto servo4{Servo(4)};
    // auto servo5{Servo(5)};
    // auto servo6{Servo(6)};

    // servo4.WRITE_Servo_Move_Time_Wait(120,0);
    // servo5.WRITE_Servo_Move_Time_Wait(120,0);
    // servo6.WRITE_Servo_Move_Time_Wait(120,0);
    // usleep(3000000);
    // servo254.WRITE_Servo_Move_Start();

    return 0;
}

// uint8_t cmdPacketStart[6] = {0x55,0x55,0x01,0x03,0x0B,0x0F};
