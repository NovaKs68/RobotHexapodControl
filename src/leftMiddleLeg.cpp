#include "leftMiddleLeg.hpp"
#include "leg.hpp"

LeftMiddleLeg::LeftMiddleLeg() : Leg(13, 14, 15)
{
    Board& m_boardServo=Board::Instance();
}

int LeftMiddleLeg::posReadyToWalk() 
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

    std::cout << "WARNING : Le mouvement de la patte LeftMiddleLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    

    return 1;
}

int LeftMiddleLeg::posReadyToWalkWait() 
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
    std::cout << "WARNING : Le mouvement de la patte LeftMiddleLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    
    return 1;
}
