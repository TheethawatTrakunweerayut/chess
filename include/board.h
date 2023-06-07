#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <array>
#include <vector>

class Square;

class Piece;

class Board
{
    public:
        static constexpr float WIDTH = 1400.0f;
        static constexpr float HEIGHT = 1400.0f;
        std::array<std::array<Square*, 8>, 8> squares;
        std::vector<Piece*> pieces;
        Board(void);
        void addPieces(void);
};

#endif