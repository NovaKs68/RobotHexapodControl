#include "board.hpp"

Board Board::m_instance = Board();

// La mise à jour des servos est faite dans une methode privée pour être appelé dans le thread pour avoir accès aux attributs de la classe

Board::Board()
{
    std::cout << "Board initialisé ! " << std::endl;
    m_boardServosAction[18];
    m_boardServosAngle[18];

    for (int i = 1; i <= 18; i++)
    {
        m_boardServosAction[i - 1] = true; // En mouvement par défaut
        m_boardServosAngle[i - 1] = 0;
    }
    m_boardActive = true;
    int a{2};
    // Répéter 2 fois l'action afin d'init le tableau
    while (a)
    { // Parcours tous les servos afin d'init le tableau récapitulant si ils sont en mouvement en comparant deux fois leur position
        for (int i = 1; i <= 18; i++)
        {
            Servo servo(i);
            int currentAngle = servo.READ_Servo_Angle();
            int test = servo.READ_id();

            // La position est testé avec une marge d'erreur de 2 degrés
            if ((m_boardServosAngle[i - 1] - 1) <= currentAngle & (m_boardServosAngle[i - 1] + 1) >= currentAngle)
            {
                m_boardServosAction[i - 1] = false; // Alors ca veut dire qu'il ne bouge pas
            }
            else
            {
                m_boardServosAction[i - 1] = true; // Alors ca veut dire qu'il est en mouvement
            }
            m_boardServosAngle[i - 1] = currentAngle;

            usleep(1000); // wait 8 millisec
        }

        a--;
    }

    std::thread t(&Board::MAJServos, this);
    t.detach(); // detach permet d'exectuer ce thread à coté du thread principal
}

Board::~Board()
{
    std::cout << "Destruction de la liste de servos" << std::endl;
}
Board &Board::Instance()
{
    return m_instance;
}

bool Board::getAction(int numeroServo)
{
    return m_boardServosAction[(numeroServo - 1)];
}

bool Board::getBoardActionServoFinished(int servoId)
{
    for (int i{0}; i < 2000; i++)
    {
        // Si le servo n'est pas en mouvement
        if (!m_boardServosAction[(servoId - 1)])
        {
            return true;
        }
        usleep(1000);
    }

    return false;
}

bool Board::getBoardActive()
{
    return m_boardActive;
}

void Board::setBoardActive(bool activeOrNot)
{
    m_boardActive = activeOrNot;
}

void Board::setServoAction(int servoId, int angleTarget)
{
    m_boardServosAction[servoId - 1] = {true};       // Set le servo est en déplacement
    m_boardServosAngle[servoId - 1] = {angleTarget}; // Enregistre l'objectif de l'ordre afin de vérifier si il est atteint
}

void Board::MAJServos()
{
    while (1)
    {
        // Faire tourner le board si aucun servo n'envoit d'ordres
        if (m_boardActive)
        {
            int nbrServoAActualiser{0};
            int servoIdAActualiser[18]{0};

            // Parcours tous les servos afin de récupérer seulement ceux qui vont être en mouvement
            for (int i = 1; i <= 18; i++)
            {
                if (m_boardServosAction[i - 1])
                {
                    servoIdAActualiser[nbrServoAActualiser] = i;
                    nbrServoAActualiser++;
                }
            }

            if (nbrServoAActualiser != 0)
            {
                // Parcours tous les servos qui viennent de recevoir un ordre de déplacment
                for (int i = 0; i < nbrServoAActualiser; i++)
                {
                    Servo servo(servoIdAActualiser[i]);
                    int currentAngle = servo.READ_Servo_Angle();
                    // Vérifie si la position de l'ordre est atteint. La position est testé avec une marge d'erreur de 6 degrés
                    if (currentAngle >= (m_boardServosAngle[servoIdAActualiser[i] - 1] - 3) && currentAngle <= (m_boardServosAngle[servoIdAActualiser[i] - 1] + 3)) // On compare ici m'angle futur à l'actuel
                    {
                        // std::cout << "Servo validé " << std::endl;
                        m_boardServosAction[servoIdAActualiser[i] - 1] = false; // Alors ca veut dire qu'il ne bouge pas
                    }
                    else
                    {
                        // std::cout << "Servo refusé " << std::endl;
                        m_boardServosAction[servoIdAActualiser[i] - 1] = true; // Alors ca veut dire qu'il est en mouvement
                    }
                    std::cout << "Avec comme position : " << currentAngle << " et comme objectif : " << m_boardServosAngle[servoIdAActualiser[i] - 1] << std::endl;
                    // std::cout << "Si elle est en mouvement ? " << m_boardServosAction[servoIdAActualiser[i] - 1] << std::endl;
                }
            }
        }
        else // Si board est désactivé c'est que des servos sont mis en mouvement, je les mets donc tous en mvmt, par la suite il faudra mettre seulement celui en mouvement
        {
            std::cout << "Le Board n'est pas activé " << std::endl;
        }
        usleep(1000); // Retenter toutes les millisec
    }
}