#ifndef RULE_H
#define RULE_H

#include "piece.h"
#include "square.h"

#include <vector>
#include <array>
#include <string>
#include <map>
#include <cstdint>

class Rule
{
    public:
        static bool whiteTurn;
        static bool promoting;
        static std::string colorPromoting;
        static std::map<std::string, std::string> namePromotion;
        static std::map<std::string, std::array<uint8_t, 2>> kingLoc;
        static std::map<std::string, std::map<std::string, std::vector<std::array<uint8_t, 2>>>> locCastle;
        static void initialization(void);
        static bool validTurn(Piece* ptrPiece);
        static bool validRowCol(uint8_t row, uint8_t col);
        static bool validMove(std::array<std::array<Square*, 8>, 8> squares, Square* ptrSquare, Piece* ptrPiece);
        static bool check(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, std::string color);
        static bool isCastle(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Square* ptrSquare, Piece* ptrPiece);
        static bool isSquareAttacked(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Square* ptrSquare, std::string color, std::string side);
        static bool isEnpassant(std::array<std::array<Square*, 8>, 8> squares, Square* ptrSquare, Piece* prevPtrPiece, Piece* ptrPiece);
        static bool isPromoting(Piece* ptrPiece);
        static void changePiece(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Piece* ptrPiece, uint8_t optionRow, uint8_t optionCol);
};

#endif