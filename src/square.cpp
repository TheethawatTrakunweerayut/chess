#include "square.h"

#include <string>
#include <cstdint>

Square::Square(void) = default;

Square::Square(uint8_t row, uint8_t col, std::string color)
{
    this -> row = row;
    this -> col = col;
    this -> color = color;
    this -> piece = nullptr;
}

bool Square::hasPiece(void)
{
    if (this -> piece != nullptr)
    {
        return true;
    } else 
    {
        return false;
    }   
}