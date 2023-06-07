#ifndef PIECE_H
#define PIECE_H

#include "square.h"

#include <string>
#include <array>
#include <vector>
#include <cstdint>

class Piece
{
    public:
        std::string name;
        std::string color;
        std::string texture;
        uint8_t row;
        uint8_t col;
        unsigned int posX;
        unsigned int posY;
        std::vector<std::array<int8_t, 2>> dir;
        bool didWalk = false;
        Piece(void);
        Piece(std::string name, std::string color, uint8_t row, uint8_t col);
        bool sameColor(Piece* otherPiece);
        virtual std::vector<std::array<uint8_t, 2>> possibleMoves(std::array<std::array<Square*, 8>, 8> squares) = 0;
};

class Pawn : public Piece
{
    public:
        Pawn(void);
        Pawn(std::string color, uint8_t row, uint8_t col);
        std::vector<std::array<uint8_t, 2>> possibleMoves(std::array<std::array<Square*, 8>, 8> squares) override;
};

class Knight : public Piece
{
    public:
        Knight(void);
        Knight(std::string color, uint8_t row, uint8_t col);
        std::vector<std::array<uint8_t, 2>> possibleMoves(std::array<std::array<Square*, 8>, 8> squares) override;
};

class Bishop : public Piece
{
    public:
        Bishop(void);
        Bishop(std::string color, uint8_t row, uint8_t col);
        std::vector<std::array<uint8_t, 2>> possibleMoves(std::array<std::array<Square*, 8>, 8> squares) override;
};

class Rook : public Piece
{
    public:
        Rook(void);
        Rook(std::string color, uint8_t row, uint8_t col);
        std::vector<std::array<uint8_t, 2>> possibleMoves(std::array<std::array<Square*, 8>, 8> squares) override;
};

class Queen : public Piece
{
    public:
        Queen(void);
        Queen(std::string color, uint8_t row, uint8_t col);
        std::vector<std::array<uint8_t, 2>> possibleMoves(std::array<std::array<Square*, 8>, 8> squares) override;
};

class King : public Piece
{
    public:
        King(void);
        King(std::string color, uint8_t row, uint8_t col);
        std::vector<std::array<uint8_t, 2>> possibleMoves(std::array<std::array<Square*, 8>, 8> squares) override;
};

#endif