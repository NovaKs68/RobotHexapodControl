#include "leftFrontLeg.hpp"
#include "leg.hpp"

LeftFrontLeg::LeftFrontLeg() : Leg(16, 17, 18)
{
    Board& m_boardServo=Board::Instance();
    m_servoCoxa.WRITE_Servo_Offset_Adjust(30);
}

int LeftFrontLeg::posReadyToWalk() 
{
    Board& board=Board::Instance();
    for(int i=1; i<=2000; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            board.setBoardActive(false); // Désactive le board

            int posServoCoxa {140};
            int posServoFemur {70};
            int posServoTibia {40};

            // Déclarer les servos en mouvement
            board.setServoAction(m_servoIdCoxa, posServoCoxa);
            board.setServoAction(m_servoIdFemur, posServoFemur);
            board.setServoAction(m_servoIdTibia, posServoTibia);

            m_servoCoxa.WRITE_Servo_Angle(posServoCoxa,0.5);
            m_servoTibia.WRITE_Servo_Angle(posServoTibia,0);
            m_servoFemur.WRITE_Servo_Angle(posServoFemur,2);

            board.setBoardActive(true); // Réactive le board

            return 1;
        }
        
        usleep(3000);
    }

    std::cout << "WARNING : Le mouvement de la patte LeftFrontLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    

    return 1;
}

int LeftFrontLeg::posReadyToWalkWait() 
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
    std::cout << "WARNING : Le mouvement de la patte LeftFrontLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;
    
    return 1;
}
