#include "leg.hpp"


Leg::Leg(int servoIdCoxa, int servoIdFemur, int servoIdTibia) : m_servoIdCoxa(servoIdCoxa), m_servoIdFemur(servoIdFemur), m_servoIdTibia(servoIdTibia), m_servoCoxa(servoIdCoxa), m_servoFemur(servoIdFemur), m_servoTibia(servoIdTibia), m_servos(254)
{

}

int Leg::posDown()
{
    m_servoFemur.WRITE_Servo_Angle(40,1);
    usleep(1000000);
    m_servoCoxa.WRITE_Servo_Angle(120,1);
    m_servoFemur.WRITE_Servo_Angle(40,1);
    m_servoTibia.WRITE_Servo_Angle(60,1);
    return 1; // A changer quand il y aura la verif que le mouvement soit bien fait en place
}

int Leg::posDownWait()
{
    m_servoFemur.WRITE_Servo_Move_Time_Wait(40,1);
    m_servoCoxa.WRITE_Servo_Move_Time_Wait(120,2);
    m_servoTibia.WRITE_Servo_Move_Time_Wait(60,2);
    return 1;
}

int Leg::start()
{
    m_servos.WRITE_Servo_Move_Start();
    return 1;
}

int Leg::currentPos()
{
    // m_servoCoxa.READ_
    return 1;
}