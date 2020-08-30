#include "leftBackLeg.hpp"
#include "leg.hpp"

LeftBackLeg::LeftBackLeg(int servoIdCoxa, int servoIdFemur, int servoIdTibia) : Leg(servoIdCoxa, servoIdFemur,servoIdTibia)
{

}

int LeftBackLeg::posReadyToWalkWait() 
{
    m_servoFemur.WRITE_Servo_Move_Time_Wait(80,1);
    m_servoCoxa.WRITE_Servo_Move_Time_Wait(120,2);
    m_servoTibia.WRITE_Servo_Move_Time_Wait(60,2);

    return 1;
}
