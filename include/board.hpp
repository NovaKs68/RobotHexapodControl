#ifndef DEF_CMDSERVO
#define DEF_CMDSERVO

#include <iostream>
#include "cmdServo.hpp"

class Board {

public:

    // Constructeur singlton
    static Board& Instance();

private:

    // singleton
    Board& operator= (const Board&);
    Board (const Board&);

    static Board m_instance;
    Board();
    ~Board();

    int m_device;
    int m_boardServos[];
};

#endif