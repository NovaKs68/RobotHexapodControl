#include "leg.hpp"


Leg::Leg(int servoIdCoxa, int servoIdFemur, int servoIdTibia) : m_servoIdCoxa(servoIdCoxa), m_servoIdFemur(servoIdFemur), m_servoIdTibia(servoIdTibia), m_servoCoxa(servoIdCoxa), m_servoFemur(servoIdFemur), m_servoTibia(servoIdTibia), m_servos(254)
{
    
}

int Leg::posDown()
{
    Board& board=Board::Instance();
    for(int i=1; i<=10; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            m_servoCoxa.WRITE_Servo_Angle(120,0);
            m_servoFemur.WRITE_Servo_Angle(40,0);
            m_servoTibia.WRITE_Servo_Angle(60,0);
            return 1;
        }
        
        usleep(100000);
    }

    std::cout << "WARNING : Le mouvement de la patte avec le servo tibia d'id " << m_servoIdTibia << std::endl;
    return 0;
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