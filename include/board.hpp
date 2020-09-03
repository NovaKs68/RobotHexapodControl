#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <thread>
#include <array>
#include "cmdServo.hpp"

class Board {

public:

    // Constructeur singlton
    static Board& Instance();

    // Va retourner si oui ou nan le servo est en action
    bool getAction(int numeroServo); 

private:

    // singleton 
    Board& operator= (const Board&);
    Board (const Board&);
    static Board m_instance;
    Board();
    ~Board();

    int m_device;
    std::array<int, 18> m_boardServosAngle; // Va comporter les currents angles des servos
    std::array<bool, 18> m_boardServosAction; // Va comporter true si il est en action et false si il est désactivé
};

#endif