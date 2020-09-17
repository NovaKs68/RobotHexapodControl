#include "body.hpp"

Body Body::m_instance=Body();

Body::Body()
{
    std::cout << "Body initialisé !" << std::endl;
    std::string const logErreur("log/errorDebug.txt");
    m_fluxError.open (logErreur.c_str());
    usleep(500000); // Temps pour init tous les servos dans le board etc
}

Body::~Body()
{ 
    std::cout << "Destruction Body !" << std::endl;
    m_fluxError.close();
}

Body& Body::Instance()
{
    return m_instance;
}


void Body::bodyPosDown()
{
    m_leg1.posDown();
    m_leg2.posDown();
    m_leg3.posDown();
    m_leg4.posDown();
    m_leg5.posDown();
    m_leg6.posDown();

    int move1 = m_leg1.getMoveFinished();
    int move2 = m_leg2.getMoveFinished();
    int move3 = m_leg3.getMoveFinished();
    int move4 = m_leg4.getMoveFinished();
    int move5 = m_leg5.getMoveFinished();
    int move6 = m_leg6.getMoveFinished();

    if(move1 && move2 && move3 && move4 && move5 && move6)
    {
        std::cout << "Le bodyPosDown s'est bien effectué !" << std::endl;
        m_fluxError << "Le bodyPosDown s'est bien effectué !" << std::endl;
    } else
    {
        std::cout << "Warning : Le mouvement bodyPosDown ne s'est pas effectué." << std::endl;
        m_fluxError << "Warning : Le mouvement bodyPosDown ne s'est pas effectué." << std::endl;
    }
    
}

void Body::bodyPosReadyToWalk()
{
    m_leg1.posReadyToWalk();
    m_leg2.posReadyToWalk();
    m_leg3.posReadyToWalk();
    m_leg4.posReadyToWalk();
    m_leg5.posReadyToWalk();
    m_leg6.posReadyToWalk();

    int move1 = m_leg1.getMoveFinished();
    int move2 = m_leg2.getMoveFinished();
    int move3 = m_leg3.getMoveFinished();
    int move4 = m_leg4.getMoveFinished();
    int move5 = m_leg5.getMoveFinished();
    int move6 = m_leg6.getMoveFinished();

    if(move1 && move2 && move3 && move4 && move5 && move6)
    {
        std::cout << "Le bodyPosDown s'est bien effectué ! " << std::endl;
    } else
    {
        std::cout << "Warning : Le mouvement bodyPosDown ne s'est pas effectué." << std::endl;
    }
}

void Body::bodyPosDownToPosReadyToWalk()
{
    
}