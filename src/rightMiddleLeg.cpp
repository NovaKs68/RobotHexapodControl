#include "rightMiddleLeg.hpp"
#include "leg.hpp"

RightMiddleLeg::RightMiddleLeg() : Leg(4, 5, 6)
{
    Board &m_boardServo = Board::Instance();
    m_servoFemur.WRITE_Servo_Offset_Adjust(7);
    m_servoTibia.WRITE_Servo_Offset_Adjust(-6);
    m_servoCoxa.WRITE_Servo_Offset_Adjust(3);
}

int RightMiddleLeg::posReadyToWalk(double timeCoxa, double timeFemur, double timeTibia)
{
    Board &board = Board::Instance();
    for (int i = 1; i <= 2000; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            board.setBoardActive(false); // Désactive le board

            int posServoCoxa{120};
            int posServoFemur{75};
            int posServoTibia{40};

            // Déclarer les servos en mouvement
            board.setServoAction(m_servoIdCoxa, posServoCoxa);
            board.setServoAction(m_servoIdFemur, posServoFemur);
            board.setServoAction(m_servoIdTibia, posServoTibia);

            m_servoCoxa.WRITE_Servo_Angle(posServoCoxa, timeCoxa);
            m_servoFemur.WRITE_Servo_Angle(posServoFemur, timeFemur);
            m_servoTibia.WRITE_Servo_Angle(posServoTibia, timeTibia);

            board.setBoardActive(true); // Réactive le board

            return 1;
        }

        usleep(3000);
    }

    std::cout << "WARNING : Le mouvement de la patte RightMiddleLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;

    return 1;
}

int RightMiddleLeg::posReadyToWalkWait()
{
    Board &board = Board::Instance();
    for (int i = 1; i <= 500; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            board.setBoardActive(false); // Désactive le board
            m_servoCoxa.WRITE_Servo_Move_Time_Wait(120, 1);
            m_servoFemur.WRITE_Servo_Move_Time_Wait(100, 2);
            m_servoTibia.WRITE_Servo_Move_Time_Wait(50, 1);
            board.setBoardActive(true); // Réactive le board
            return 1;
        }

        usleep(1000);
    }
    board.setBoardActive(true); // Réactive le board
    std::cout << "WARNING : Le mouvement de la patte RightMiddleLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;

    return 1;
}

int RightMiddleLeg::posDownToPosReadyToWalk1()
{
    Board &board = Board::Instance();
    for (int i = 1; i <= 2000; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            board.setBoardActive(false); // Désactive le board

            int posServoCoxa{120};
            int posServoFemur{20};
            int posServoTibia{25};

            // Déclarer les servos en mouvement
            board.setServoAction(m_servoIdCoxa, posServoCoxa);
            board.setServoAction(m_servoIdFemur, posServoFemur); 
            board.setServoAction(m_servoIdTibia, posServoTibia);

            m_servoCoxa.WRITE_Servo_Angle(posServoCoxa, 0);
            m_servoTibia.WRITE_Servo_Angle(posServoTibia, 0);
            m_servoFemur.WRITE_Servo_Angle(posServoFemur, 0);

            board.setBoardActive(true); // Réactive le board

            return 1;
        }

        usleep(3000);
    }

    std::cout << "WARNING : Le mouvement de la patte LeftBackLeg (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;

    return 1;
}
