#include "leg.hpp"


Leg::Leg(int servoIdCoxa, int servoIdFemur, int servoIdTibia) : m_servoIdCoxa(servoIdCoxa), m_servoIdFemur(servoIdFemur), m_servoIdTibia(servoIdTibia), m_servoCoxa(servoIdCoxa), m_servoFemur(servoIdFemur), m_servoTibia(servoIdTibia), m_servos(254), m_accessCom(true)
{
    
}

int Leg::posDown()
{
    Board& board=Board::Instance();
    board.setBoardActive(false); // Désactive le board
    for(int i=1; i<=500; i++) // Recommencer 500 fois au final ca donnera 0.5 sec d'attente. Ca équivaut à la durée max d'execution d'un ordre pour le servo (0.48 sec)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            m_servoCoxa.WRITE_Servo_Angle(120,0);
            m_servoFemur.WRITE_Servo_Angle(40,0);
            m_servoTibia.WRITE_Servo_Angle(60,0);
            board.setBoardActive(true); // Réactive le board
            return 1;
        }
        
        usleep(1000); // Retenter toutes les 3 millisec
    }
    board.setBoardActive(true); // Réactive le board
    std::cout << "WARNING : Le mouvement de la patte avec le servo tibia d'id " << m_servoIdTibia << " n'a pas pu s'effectuer !" << std::endl;
    return 0;
}

// Une erreur peut survenir d'ici car le board n'a peut-être pas le temps de s'arreter (il lui faudra max 18 millisec pour s'arreter)
int Leg::posDownWait()
{
    Board& board=Board::Instance();
    board.setBoardActive(false); // Désactive le board
    m_servoCoxa.WRITE_Servo_Move_Time_Wait(120,2);
    m_servoFemur.WRITE_Servo_Move_Time_Wait(40,1);
    m_servoTibia.WRITE_Servo_Move_Time_Wait(60,2);
    board.setBoardActive(true); // Réactive le board
    return 1;
}

int Leg::start()
{ 
    Board& board=Board::Instance();
    board.setBoardActive(false); // Désactive le board
    for(int i=1; i<=500; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            m_servos.WRITE_Servo_Move_Start();
            board.setBoardActive(true); // Réactive le board
            return 1;
        }
        
        usleep(1000);
    }
    board.setBoardActive(true); // Réactive le board
    std::cout << "WARNING : Le mouvement de la patte (en déplacement avec utilisation de wait/start) avec le servo tibia d'id " << m_servoIdTibia << " n'a pas pu s'effectuer !" << std::endl;
    return 0;
}

int Leg::currentPos() // Pas fonctionnel probleme : return un array
{
    int currAngle[3];
    currAngle[0] = m_servoCoxa.READ_Servo_Angle();
    currAngle[1] = m_servoFemur.READ_Servo_Angle();
    currAngle[2] = m_servoTibia.READ_Servo_Angle();

    return *currAngle;
}