#include "leg.hpp"

Leg::Leg(int servoIdCoxa, int servoIdFemur, int servoIdTibia) : m_servoIdCoxa(servoIdCoxa), m_servoIdFemur(servoIdFemur), m_servoIdTibia(servoIdTibia), m_servoCoxa(servoIdCoxa), m_servoFemur(servoIdFemur), m_servoTibia(servoIdTibia), m_servos(254), m_accessCom(true)
{
}

int Leg::posDown()
{
    Board &board = Board::Instance();
    for (int i = 1; i <= 2000; i++) // Recommencer 1000 fois au final ca donnera 1sec sec d'attente. Ca équivaut à deux fois la durée max d'execution d'un ordre pour le servo (0.48 sec). Ca va permettre d'effectuer cette ordre meme si un autre à été envoyé.
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            if (board.getBoardActive())
            {
                board.setBoardActive(false); // Désactive le board afin de ne pas faire des requetes en meme temps que lui

                // Déclarer les servos en mouvement
                board.setServoAction(m_servoIdCoxa, 120);
                board.setServoAction(m_servoIdFemur, 30);
                board.setServoAction(m_servoIdTibia, 60);

                m_servoFemur.WRITE_Servo_Angle(30, 0.5);
                m_servoCoxa.WRITE_Servo_Angle(120, 1);
                m_servoTibia.WRITE_Servo_Angle(60, 1);

                board.setBoardActive(true); // Réactive le board

                // L'ordre s'est bien envoyé
                return 1;
            }
        }

        usleep(3000); // Retenter toutes les 3 millisec
    }
    board.setBoardActive(true); // Réactive le board
    std::cout << "WARNING : Le mouvement de la patte avec le servo tibia d'id " << m_servoIdTibia << " n'a pas pu s'effectuer !" << std::endl;
    return 0;
}

// Une erreur peut survenir d'ici car le board n'a peut-être pas le temps de s'arreter (il lui faudra max 18 millisec pour s'arreter)
int Leg::posDownWait()
{
    Board &board = Board::Instance();
    board.setBoardActive(false); // Désactive le board
    m_servoCoxa.WRITE_Servo_Move_Time_Wait(120, 2);
    m_servoFemur.WRITE_Servo_Move_Time_Wait(40, 1);
    m_servoTibia.WRITE_Servo_Move_Time_Wait(60, 2);
    board.setBoardActive(true); // Réactive le board
    return 1;
}

int Leg::posReadyToWalk(double angleCoxa, double angleFemur, double angleTibia, double timeCoxa, double timeFemur, double timeTibia)
{
    Board &board = Board::Instance();
    for (int i = 1; i <= 2000; i++)
    {
        if (!board.getAction(m_servoIdCoxa) && !board.getAction(m_servoIdFemur) && !board.getAction(m_servoIdTibia))
        {
            board.setBoardActive(false); // Désactive le board

            int posServoCoxa{120};
            int posServoFemur{70};
            int posServoTibia{40};

            // Déclarer les servos en mouvement
            board.setServoAction(m_servoIdCoxa, posServoCoxa);
            board.setServoAction(m_servoIdFemur, posServoFemur); 
            board.setServoAction(m_servoIdTibia, posServoTibia);

            m_servoCoxa.WRITE_Servo_Angle(posServoCoxa, timeCoxa);
            m_servoTibia.WRITE_Servo_Angle(posServoTibia, timeFemur);
            m_servoFemur.WRITE_Servo_Angle(posServoFemur, timeTibia);

            board.setBoardActive(true); // Réactive le board

            return 1;
        }

        usleep(3000);
    }

    std::cout << "WARNING : Le mouvement de la patte avec l'id : " << m_servoIdCoxa << ", " << m_servoIdFemur << ", " << m_servoIdTibia <<" (posReadyToWalk) n'a pas pu s'effectuer !" << std::endl;

    return 1;
}

int Leg::start()
{
    Board &board = Board::Instance();
    board.setBoardActive(false); // Désactive le board
    for (int i = 1; i <= 500; i++)
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

bool Leg::getMoveFinished()
{
    Board &board = Board::Instance();
    bool move1 = board.getBoardActionServoFinished(m_servoIdCoxa);
    bool move2 = board.getBoardActionServoFinished(m_servoIdFemur);
    bool move3 = board.getBoardActionServoFinished(m_servoIdTibia);

    if (move1 && move2 && move3)
    {
        return true;
    }
    else
    {
        std::cout << "Warning : Patte avec servoId : " << m_servoIdTibia << " n'a pas fini son mouvement." << std::endl;
        return false;
    }
}