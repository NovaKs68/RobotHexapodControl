#include "rightBackLeg.hpp"
#include "leg.hpp"

RightBackLeg::RightBackLeg() : Leg(7, 8, 9)
{
    Board& m_boardServo=Board::Instance();
}

int RightBackLeg::posReadyToWalk() 
{
    Board& board=Board::Instance();
    for(int i=1; i<=1000; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            // Déclarer les servos en mouvement
            board.setServoAction(m_servoIdCoxa, 120);
            board.setServoAction(m_servoIdFemur, 120);
            board.setServoAction(m_servoIdTibia, 120);

            board.setBoardActive(false); // Désactive le board
            m_servoCoxa.WRITE_Servo_Angle(120,2);
            m_servoFemur.WRITE_Servo_Angle(120,1);
            m_servoTibia.WRITE_Servo_Angle(120,2);

            board.setBoardActive(true); // Réactive le board

            return 1;
        }
        
        usleep(3000);
    }
    board.setBoardActive(true); // Réactive le board
    std::cout << "WARNING : Le mouvement de la patte RightBackLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    

    return 1;
}

int RightBackLeg::posReadyToWalkWait() 
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
    std::cout << "WARNING : Le mouvement de la patte RightBackLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    
    return 1;
}
