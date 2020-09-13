#include "board.hpp"

Board Board::m_instance=Board();

// La mise à jour des servos est faite dans une methode privée pour être appelé dans le thread pour avoir accès aux attributs de la classe

Board::Board()
{
    std::cout << "Board initialisé ! " << std::endl;
    m_boardServosAction[18];
    m_boardServosAngle[18];
    
    for(int i=1; i<=18; i++)
    {
        m_boardServosAction[i] = true; // En mouvement par défaut
        m_boardServosAngle[i] = 0;
    }
    m_boardActive = true;
    int a =2;
    while(a)
    {   
        for(int i=1; i<=18; i++)
        {
            Servo servo(i);     
            int currentAngle = servo.READ_Servo_Angle();
            int test = servo.READ_id();

            // La position est testé avec une marge d'erreur de 2 degrés
            if ((m_boardServosAngle[i] - 1) <= currentAngle & (m_boardServosAngle[i] + 1) >= currentAngle)
            {
                m_boardServosAction[i] = false; // Alors ca veut dire qu'il ne bouge pas
            } else 
            {
                m_boardServosAction[i] = true; // Alors ca veut dire qu'il est en mouvement
            }
            m_boardServosAngle[i] = currentAngle;
            // std::cout << "Servo " << i << " testé !" << std::endl;
            // std::cout << "Avec comme position : " << m_boardServosAngle[i] << std::endl;
            // std::cout << "Si elle est en mouvement ? " << m_boardServosAction[i] << std::endl;

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
Board& Board::Instance()
{
    return m_instance;
}

bool Board::getAction(int numeroServo)
{
    return m_boardServosAction[(numeroServo -1)];
}

bool Board::getBoardActive()
{
    return m_boardActive;
}

void Board::setBoardActive(bool activeOrNot)
{
    m_boardActive = activeOrNot;
}

void Board::MAJServos()
{
    while(1)
    {
        if(m_boardActive)
        {
            for(int i=1; i<=18; i++)
            {
                Servo servo(i);
                int currentAngle = servo.READ_Servo_Angle();

                // La position est testé avec une marge d'erreur de 2 degrés
                if ((m_boardServosAngle[i] - 1) <= currentAngle & (m_boardServosAngle[i] + 1) >= currentAngle)
                {
                    m_boardServosAction[i] = false; // Alors ca veut dire qu'il ne bouge pas
                } else 
                {
                    m_boardServosAction[i] = true; // Alors ca veut dire qu'il est en mouvement
                }
                m_boardServosAngle[i] = currentAngle;
                // std::cout << "Servo " << i << " testé !" << std::endl;
                std::cout << "Avec comme position : " << m_boardServosAngle[i] << std::endl;
                std::cout << "Si elle est en mouvement ? " << m_boardServosAction[i] << std::endl;

                usleep(1000); // wait 8 millisec 
            }
        } else // Si board est désactivé c'est que des servos sont mis en mouvement, je les mets donc tous en mvmt, par la suite il faudra mettre seulement celui en mouvement
        {
            for(int i=1; i<=18; i++)
            {
                m_boardServosAction[i] = true; // Alors ca veut dire qu'il est en mouvement
            }
        }
       usleep(1000); // Retenter toutes les millisec
    }
}