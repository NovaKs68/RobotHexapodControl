#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <thread>
#include <array>
#include "cmdServo.hpp"
#include "leg.hpp"

class Board
{

public:
    // Constructeur singlton
    static Board &Instance();

    // Va retourner si oui ou nan le servo est en action
    bool getAction(int numeroServo);

    // Va retourner si oui ou non la com est libre
    bool getBoardActive();
    void setBoardActive(bool activeOrNot);

    // Va retourner true quand le servo aura fini son mouvement
    bool getBoardActionServoFinished(int servoId);

    void setServoAction(int servoId, int angleTarget);

    void MAJServos();

private:
    // singleton
    Board &operator=(const Board &);
    Board(const Board &);
    static Board m_instance;
    Board();
    ~Board();

    std::array<int, 18> m_boardServosAngle;   // Va comporter les currents angles des servos
    std::array<bool, 18> m_boardServosAction; // Va comporter true si il est en action et false si il est désactivé
    bool m_boardActive;                       // True si active et false si desactive
};

#endif