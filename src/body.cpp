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
    m_bodyPosCurrent = {"posDown"}; // En en posDown
    m_leg1.posDown();
    m_leg2.posDown();
    m_leg3.posDown();
    m_leg4.posDown();
    m_leg5.posDown();
    m_leg6.posDown();

    bodyAction(); // Debug
}

void Body::bodyPosReadyToWalk()
{
    // Si la position est posDown
    if (m_bodyPosCurrent == "posDown")
    {
        this->bodyPosDownToPosReadyToWalk();
        m_bodyPosCurrent = {"posReadyToWalk"}; // Est en posReadyToWalk
    } else if (m_bodyPosCurrent == "posReadyToWalk") // Si la position est posReadyToWalk
    {
        m_leg1.posReadyToWalk(0,2,0);
        m_leg2.posReadyToWalk(0,2,0);
        m_leg3.posReadyToWalk(0,2,0);
        m_leg4.posReadyToWalk(0,2,0);
        m_leg5.posReadyToWalk(0,2,0);
        m_leg6.posReadyToWalk(0,2,0);
    }
    m_leg1.posReadyToWalk(0,2,0);
        m_leg2.posReadyToWalk(0,2,0);
        m_leg3.posReadyToWalk(0,2,0);
        m_leg4.posReadyToWalk(0,2,0);
        m_leg5.posReadyToWalk(0,2,0);
        m_leg6.posReadyToWalk(0,2,0);

    bodyAction(); // Debug
}

// Mouvement transition de posDown à posReadyToWalk
void Body::bodyPosDownToPosReadyToWalk()
{
    m_leg1.posDownToPosReadyToWalk1();
    m_leg2.posDownToPosReadyToWalk1();
    m_leg3.posDownToPosReadyToWalk1();
    m_leg4.posDownToPosReadyToWalk1();
    m_leg5.posDownToPosReadyToWalk1();
    m_leg6.posDownToPosReadyToWalk1();
    m_bodyPosCurrent = {"posDownToPosReadyToWalk1"};
    bodyAction();
    m_leg1.posReadyToWalk(0,0,0.5);
    m_leg2.posReadyToWalk(0,0,0.5);
    m_leg3.posReadyToWalk(0,0,0.5);
    m_leg4.posReadyToWalk(0,0,0.5);
    m_leg5.posReadyToWalk(0,0,0.5);
    m_leg6.posReadyToWalk(0,0,0.5);
    m_bodyPosCurrent = {"posReadyToWalk"};
    bodyAction();
}

// Va écrire dans le fichier debug l'état de chaque patte si elles n'ont pas finit leur mouvement et va valider la pos
bool Body::bodyAction()
{
    int move1 = m_leg1.getMoveFinished();
    int move2 = m_leg2.getMoveFinished();
    int move3 = m_leg3.getMoveFinished();
    int move4 = m_leg4.getMoveFinished();
    int move5 = m_leg5.getMoveFinished();
    int move6 = m_leg6.getMoveFinished();

    if (!move1)
        m_fluxError << "Le mouvement : " << m_bodyPosCurrent << " de la patte : RightFrontLeg ne s'est pas effectué !" << std::endl;

    if (!move2)
        m_fluxError << "Le mouvement : " << m_bodyPosCurrent << " de la patte : RightMiddleLeg ne s'est pas effectué !" << std::endl;

    if (!move3)
        m_fluxError << "Le mouvement : " << m_bodyPosCurrent << " de la patte : RightBackLeg ne s'est pas effectué !" << std::endl;

    if (!move4)
        m_fluxError << "Le mouvement : " << m_bodyPosCurrent << " de la patte : LeftBackLeg ne s'est pas effectué !" << std::endl;

    if (!move5)
        m_fluxError << "Le mouvement : " << m_bodyPosCurrent << " de la patte : LeftMiddleLeg ne s'est pas effectué !" << std::endl;

    if (!move6)
        m_fluxError << "Le mouvement : " << m_bodyPosCurrent << " de la patte : LeftFrontLeg ne s'est pas effectué !" << std::endl;

    if(move1 && move2 && move3 && move4 && move5 && move6)
    {
        std::cout << "Le mouvement : " << m_bodyPosCurrent << " s'est bien effectué !" << std::endl;
        m_fluxError << "Le mouvement : " << m_bodyPosCurrent << " s'est bien effectué !" << std::endl;

        return true; // Tout est ok
    } else
    {
        std::cout << "Warning : Le mouvement : " << m_bodyPosCurrent << " ne s'est pas effectué." << std::endl;
        m_fluxError << "Warning : Le mouvement : " << m_bodyPosCurrent << " ne s'est pas effectué." << std::endl;

        return false; // Le mouvement n'est pas fait 
    }
}

// Mouvements pré-enregistrés (par la suite ce sera un axe x,y,z qui fera déplacer une patte) :

int Body::walkRight1()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkRight2()
{
    m_leg1.posReadyToWalkAngleTime(145,30,80,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(160,30,30,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(80,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkRight3()
{
    m_leg1.posReadyToWalkAngleTime(145,85,80,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(160,70,30,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(80,75,50,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkRight4()
{
    m_leg1.posReadyToWalkAngleTime(145,85,80,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(160,70,25,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(80,75,50,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkRight5()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkRight6()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkLeft1()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkLeft2()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(160,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(80,30,30,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(95,30,80,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkLeft3()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(160,75,50,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(80,70,30,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(95,85,80,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkLeft4()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(160,75,50,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(80,70,25,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(95,85,80,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkLeft5()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkLeft6()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::rotateRight2()
{
    m_leg1.posReadyToWalkAngleTime(160,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(160,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(160,30,45,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::rotateRight3()
{
    m_leg1.posReadyToWalkAngleTime(160,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(160,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(160,75,45,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::rotateRight4()
{
    m_leg1.posReadyToWalkAngleTime(160,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(160,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(160,75,45,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::rotateRight5()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,45,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}



int Body::rotateLeft2()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(80,30,45,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(80,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(80,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::rotateLeft3()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(80,75,45,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(80,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(80,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::rotateLeft4()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(80,75,45,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(80,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(80,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::rotateLeft5()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,45,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}



int Body::walkBackRight1()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackRight2()
{
    m_leg1.posReadyToWalkAngleTime(80,30,30,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(95,30,80,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(160,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackRight3()
{
    m_leg1.posReadyToWalkAngleTime(80,70,30,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(95,85,80,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(160,75,50,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackRight4()
{
    m_leg1.posReadyToWalkAngleTime(80,70,25,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(95,85,80,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(160,75,50,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackRight5()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackRight6()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackLeft1()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackLeft2()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(80,30,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(145,30,80,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(160,30,30,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackLeft3()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(80,75,50,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(145,85,80,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(160,70,30,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackLeft4()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(80,75,50,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(145,85,80,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(160,70,25,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackLeft5()
{
    m_leg1.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,30,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}

int Body::walkBackLeft6()
{
    m_leg1.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg2.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg3.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg4.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_leg5.posReadyToWalkAngleTime(120,75,40,0.5,0.5,0.5);
    m_leg6.posReadyToWalkAngleTime(120,70,40,0.5,0.5,0.5);
    m_bodyPosCurrent = {"posWalkRight1"};
    bodyAction();
    return 1;
}