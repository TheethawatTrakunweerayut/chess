#ifndef SQUARE_H
#define SQUARE_H

#include "board.h"

#include <string>
#include <cstdint>

class Piece;

class Square
{
    public:
        static constexpr float SIZE = Board::WIDTH / 8;
        static constexpr float HALF_SIZE = SIZE / 2;
        std::string color;
        uint8_t row;
        uint8_t col;
        Piece* piece;
        Square(void);
        Square(uint8_t row, uint8_t col, std::string color);
        bool hasPiece(void);
};

#endif