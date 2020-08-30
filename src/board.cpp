#include "board.hpp"

Board Board::m_instance=Board();


Board::Board()
{
    // Ajouter la cration du tableau multidimensionnel
}

Board::~Board()
{
    std::cout << "Destruction de la liste de servos" << std::endl;
}
Board& Board::Instance()
{
    return m_instance;
}