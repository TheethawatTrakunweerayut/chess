#ifndef DRAGGER_H
#define DRAGGER_H

#include "piece.h"
#include "square.h"

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <string>
#include <vector>

class Dragger
{
    public:
        static unsigned int x;
        static unsigned int y;
        static Square* ptrInitSquare;
        static Square* ptrPrevSquare;
        static std::string initSquareColor;
        static std::string prevSquareColor;
        static Piece* ptrPiece;
        static Piece* prevPtrPiece;
        static Piece* ptrPiecePromoted;
        static bool dragging;
        static void updatePressedPos(unsigned int x, unsigned int y);
        static void dragPiece(Square* ptrSquare, Piece* ptrPiece);
        static void undragPiece(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Square* ptrSquare);
        static void updatePos(Square* ptrSquare);
};

#endif