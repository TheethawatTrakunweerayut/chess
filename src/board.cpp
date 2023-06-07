#include "board.h"
#include "square.h"
#include "piece.h"

#include <string>
#include <cstdint>

Board::Board(void)
{
    std::string color;

    for (uint8_t row = 0; row < 8; row++)
    {
        for (uint8_t col = 0; col < 8; col++)
        {
            ((row + col) % 2 == 0) ? (color = "white") : (color = "black");
            this -> squares[row][col] = new Square(row, col, color);
        }
    }

}

void Board::addPieces(void)
{
    std::string colors[] = {"white", "black"};
    uint8_t pRow, oRow;
    
    for (std::string color : colors)
    {
        (color == "white") ? (pRow = 6, oRow = 7) : (pRow = 1, oRow = 0);

        //pawns
        for (uint8_t col = 0; col < 8; col++)
        {
            Pawn* pawn = new Pawn(color, pRow, col);
            this -> squares[pRow][col] -> piece = pawn;
            this -> pieces.push_back(pawn);
        }

        //knights
        Knight* lKnight = new Knight(color, oRow, 1);
        Knight* rKnight = new Knight(color, oRow, 6);
        this -> squares[oRow][1] -> piece = lKnight;
        this -> squares[oRow][6] -> piece = rKnight;
        this  -> pieces.push_back(lKnight);
        this  -> pieces.push_back(rKnight);

        //bishops
        Bishop* lBishop = new Bishop(color, oRow, 2);
        Bishop* rBishop = new Bishop(color, oRow, 5);
        this -> squares[oRow][2] -> piece = lBishop;
        this -> squares[oRow][5] -> piece = rBishop;
        this  -> pieces.push_back(lBishop);
        this  -> pieces.push_back(rBishop);

        //rooks
        Rook* lRook = new Rook(color, oRow, 0);
        Rook* rRook = new Rook(color, oRow, 7);
        this -> squares[oRow][0] -> piece = lRook;
        this -> squares[oRow][7] -> piece = rRook;
        this  -> pieces.push_back(lRook);
        this  -> pieces.push_back(rRook);

        //queen
        Queen* queen = new Queen(color, oRow, 3);
        this -> squares[oRow][3] -> piece = queen;
        this  -> pieces.push_back(queen);
         
        //king
        King* king = new King(color, oRow, 4);
        this -> squares[oRow][4] -> piece = king;
        this  -> pieces.push_back(king);

    }
}