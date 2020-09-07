#include "leftBackLeg.hpp"
#include "leg.hpp"

LeftBackLeg::LeftBackLeg() : Leg(10, 11, 12)
{
    Board& m_boardServo=Board::Instance();
}

int LeftBackLeg::posReadyToWalk() 
{
    Board& board=Board::Instance();
    for(int i=1; i<=500; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            board.setBoardActive(false); // Désactive le board
            m_servoCoxa.WRITE_Servo_Angle(120,2);
            m_servoFemur.WRITE_Servo_Angle(120,1);
            m_servoTibia.WRITE_Servo_Angle(120,2);
            board.setBoardActive(true); // Réactive le board
            return 1;
        }
        
        usleep(1000);
    }
    board.setBoardActive(true); // Réactive le board
    std::cout << "WARNING : Le mouvement de la patte LeftBackLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    

    return 1;
}

int LeftBackLeg::posReadyToWalkWait() 
{
    Board& board=Board::Instance();
    for(int i=1; i<=500; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            board.setBoardActive(false); // Désactive le board
            m_servoCoxa.WRITE_Servo_Move_Time_Wait(120,1);
            m_servoFemur.WRITE_Servo_Move_Time_Wait(100,2);
            m_servoTibia.WRITE_Servo_Move_Time_Wait(50,1);
            board.setBoardActive(true); // Réactive le board
            return 1;
        }
        
        usleep(1000);
    }
    board.setBoardActive(true); // Réactive le board
    std::cout << "WARNING : Le mouvement de la patte LeftBackLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    
    return 1;
}
