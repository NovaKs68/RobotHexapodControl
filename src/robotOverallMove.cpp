#include "robotOverallMove.hpp"

RobotOverallMove::RobotOverallMove()
{
    Body &body = Body::Instance();
    std::cout << "Init de RobotOverallMove !" << std::endl;
}

void RobotOverallMove::moveStepsForward(int nbrSteps)
{
    Body &body = Body::Instance();

    bool multiStep{false}; // Détermine si plusieurs mouvements s'enchaines afin d'améliorer la marche

    for (nbrSteps; nbrSteps > 0; nbrSteps--)
    {
        std::cout << "f" << std::endl;
        // Va permettre d'alterner (avancer d'un coté puis de l'autre)
        if (nbrSteps % 2 == 0) // Si le nombre est paire
        {
            if (!multiStep)
                body.walkRight1();
            body.walkRight2();
            body.walkRight3();
            body.walkRight4();
            body.walkRight5();
            if (nbrSteps >= 1)
                body.walkRight6();
            multiStep = {false};
        }
        else
        {
            body.walkLeft2();
            body.walkLeft3();
            body.walkLeft4();
            body.walkLeft5();
            if (!nbrSteps > 1)
                body.walkLeft6();
            multiStep = {true};
        }
    }
}

void RobotOverallMove::moveStepsBack(int nbrSteps)
{
    Body &body = Body::Instance();

    bool multiStep{false}; // Détermine si plusieurs mouvements s'enchaines afin d'améliorer la marche

    for (nbrSteps; nbrSteps == 0; nbrSteps--)
    {
        // Va permettre d'alterner (avancer d'un coté puis de l'autre)
        if (nbrSteps % 2 == 0) // Si le nombre est paire
        {
            if (!multiStep)
                body.walkBackRight1();
            body.walkBackRight2();
            body.walkBackRight3();
            body.walkBackRight4();
            body.walkBackRight5();
            if (nbrSteps > 1)
                body.walkBackRight6();
            multiStep = {false};
        }
        else
        {
            body.walkBackLeft2();
            body.walkBackLeft3();
            body.walkBackLeft4();
            body.walkBackLeft5();
            if (nbrSteps > 1)
                body.walkBackLeft6();
            multiStep = {true};
        }
    }
}

void RobotOverallMove::moveRotateRight(int degres)
{
    degres *= 1.8195; // Transforme le mouvement du robot en degrés
    Body &body = Body::Instance();

    while (degres)
    {
        if (degres > 40)
        {
            body.walkLeft1();
            body.rotateRight2(40);
            body.rotateRight3(40);
            body.rotateRight4(40);
            body.rotateRight5();
            body.walkLeft6();
            degres -= 40;
        }
        else if (degres <= 40 && degres > 0)
        {
            body.walkLeft1();
            body.rotateRight2(degres);
            body.rotateRight3(degres);
            body.rotateRight4(degres);
            body.rotateRight5();
            body.walkLeft6();
            degres = 0;
        } else
        {
            degres = 0;
        }
    }
}

void RobotOverallMove::moveRotateLeft(int degres)
{
    degres *= 1.8195; // Transforme le mouvement du robot en degrés
    Body &body = Body::Instance();

    while (degres)
    {
        if (degres > 40)
        {
            body.walkRight1();
            body.rotateLeft2(40);
            body.rotateLeft3(40);
            body.rotateLeft4(40);
            body.rotateLeft5();
            body.walkRight6();
            degres -= 40;
        }
        else if (degres <= 40 && degres > 0)
        {
            body.walkRight1();
            body.rotateLeft2(degres);
            body.rotateLeft3(degres);
            body.rotateLeft4(degres);
            body.rotateLeft5();
            body.walkRight6();
            degres = 0;
        } else
        {
            degres = 0;
        }
    }
}