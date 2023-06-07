#include "rule.h"

#include <vector>
#include <array>
#include <string>
#include <cstdint>
#include <map>

#include <iostream>

bool Rule::whiteTurn = true;

bool Rule::promoting = false;
std::string Rule::colorPromoting;
std::map<std::string, std::string> Rule::namePromotion;

std::map<std::string, std::array<uint8_t, 2>> Rule::kingLoc;
std::map<std::string, std::map<std::string, std::vector<std::array<uint8_t, 2>>>> Rule::locCastle;

void Rule::initialization(void)
{
    Rule::kingLoc["white"] = {7, 4};
    Rule::kingLoc["black"] = {0, 4}; 

    std::array<std::string, 2> colors = {"white", "black"};
    std::string side;
    for (std::string color : colors)
    {
        uint8_t row;
        (color == "white") ? (row = 7) : (row = 0);

        side = "left";

        for (uint8_t i = 0; i < 3; i++)
        {
            Rule::locCastle[color][side].push_back({row, i});
        }

        side = "right";

        for (uint8_t i = 6; i < 8; i++)
        {
            Rule::locCastle[color][side].push_back({row, i});
        }
    }

    Rule::namePromotion["00"] = "queen";
    Rule::namePromotion["01"] = "rook";
    Rule::namePromotion["10"] = "knight";
    Rule::namePromotion["11"] = "bishop";
}

bool Rule::validTurn(Piece* ptrPiece)
{
    if ((Rule::whiteTurn) && (ptrPiece -> color == "white"))
    {
        return true;
    } else if (!(Rule::whiteTurn) && (ptrPiece -> color == "black"))
    {
        return true;
    } else return false;
}

bool Rule::validRowCol(uint8_t row, uint8_t col)
{
    if ((row < 8) && (col < 8))
    {
        return true;
    } else return false;
}

bool Rule::validMove(std::array<std::array<Square*, 8>, 8> squares, Square* ptrSquare, Piece* ptrPiece)
{
    std::vector<std::array<uint8_t, 2>> moves = ptrPiece -> possibleMoves(squares);
    uint8_t row, col;
    row = ptrSquare -> row;
    col = ptrSquare -> col;

    for (std::array<uint8_t, 2> move : moves)
    {
        if ((row == move[0]) && (col == move[1]))
        {
            return true;
        }
    }
    return false;
}

bool Rule::check(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, std::string color)
{   
    for (Piece* piece : pieces)
    {
        if (piece -> color != color)
        {
            std::vector<std::array<uint8_t, 2>> moves = piece -> possibleMoves(squares);
            
            for (std::array<uint8_t, 2> move : moves)
            {
                if ((move[0] == Rule::kingLoc[color][0]) && (move[1] == Rule::kingLoc[color][1]))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Rule::isCastle(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Square* ptrSquare, Piece* ptrPiece)
{
    if (ptrPiece -> name != "king" || ptrPiece -> didWalk || 
    (ptrSquare -> row > 0 && ptrSquare -> row < 7) ||
    (ptrSquare -> col >= 3 && ptrSquare -> col <= 5)) return false;
    
    uint8_t row, col;
    row = ptrSquare -> row;
    col = ptrSquare -> col;

    std::string side;
    (col <= 2) ? side = "left" : side = "right";

    if (side == "left")
    {
        Square* rookSquare = squares[row][0];
        if (!rookSquare -> hasPiece() || rookSquare -> piece -> name != "rook" || rookSquare -> piece -> didWalk)
        {
            return  false;
        } 
    } else
    {
        Square* rookSquare = squares[row][7];
        if (!rookSquare -> hasPiece() || rookSquare -> piece -> name != "rook" || rookSquare -> piece -> didWalk)
        {
            return  false;
        } 
    }

    bool valid = false;

    for (std::array<uint8_t, 2> loc : Rule::locCastle[ptrPiece -> color][side])
    {
        if (Rule::isSquareAttacked(squares, pieces, squares[loc[0]][loc[1]], ptrPiece -> color, side))
        {
            valid = false;
            return valid;
        }

        if ((row == loc[0]) && (col == loc[1]))
        {
            valid = true;
        }
    }

    return valid;
}

bool Rule::isSquareAttacked(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Square* ptrSquare, std::string color, std::string side)
{
    uint8_t row, col;
    row = ptrSquare -> row;
    col = ptrSquare -> col;

    for (Piece* piece : pieces)
    {
        if (piece -> color != color)
        {
            std::vector<std::array<uint8_t, 2>> moves = piece -> possibleMoves(squares);

            for (std::array<uint8_t, 2> move : moves)
            {
                if (((move[0] == row) && (move[1] == col)) || 
                ((side == "left") && ((move[0] == row) && (move[1] == 3))) || 
                ((side == "right") && ((move[0] == row) && (move[1] == 5))) ||
                ((move[0] == row) && (move[1] == 4)))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Rule::isEnpassant(std::array<std::array<Square*, 8>, 8> squares, Square* ptrSquare, Piece* prevPtrPiece, Piece* ptrPiece)
{
    if (ptrPiece -> name != "pawn" || (prevPtrPiece != nullptr && prevPtrPiece -> name != "pawn"))
    {
        return false;
    }

    std::string color = ptrPiece -> color;

    if ((color == "white") && (ptrPiece -> row != 3))
    {
        return false;
    } else if ((color == "black") && (ptrPiece -> row != 4))
    {
        return false;
    }

    uint8_t row, col;
    row = ptrSquare -> row;
    col = ptrSquare -> col;
    
    (color == "white") ? (row++) : (row--);

    if ((!squares[row][col] -> hasPiece()) || (squares[row][col] -> piece -> name != "pawn") || (squares[row][col] -> piece != prevPtrPiece))
    {
        return false;
    }

    return true;
}

bool Rule::isPromoting(Piece* ptrPiece)
{
    if (ptrPiece -> name == "pawn")
    {
        if (ptrPiece -> color == "white")
        {
            if (ptrPiece -> row == 0)
            {
                Rule::colorPromoting = "white";
                return true;
            }
        } else 
        {
            if (ptrPiece -> row == 7)
            {
                Rule::colorPromoting = "black";
                return true;
            }
        }
    }

    return false;
}

void Rule::changePiece(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Piece* ptrPiece, uint8_t optionRow, uint8_t optionCol)
{
    std::string name = Rule::namePromotion[std::to_string(optionRow) + std::to_string(optionCol)];

    if (name == "queen")
    {
        Queen* queen = new Queen(ptrPiece -> color, ptrPiece -> row, ptrPiece -> col);
        queen -> posX = ptrPiece -> posX;
        queen -> posY = ptrPiece -> posY;
        queen -> didWalk = true;

        pieces.push_back(queen);
        squares[ptrPiece -> row][ptrPiece -> col] -> piece = queen;
    } else if (name == "rook")
    {
        Rook* rook = new Rook(ptrPiece -> color, ptrPiece -> row, ptrPiece -> col);
        rook -> posX = ptrPiece -> posX;
        rook -> posY = ptrPiece -> posY;
        rook -> didWalk = true;

        pieces.push_back(rook);
        squares[ptrPiece -> row][ptrPiece -> col] -> piece = rook;
    } else if (name == "knight")
    {
        Knight* knight = new Knight(ptrPiece -> color, ptrPiece -> row, ptrPiece -> col);
        knight -> posX = ptrPiece -> posX;
        knight -> posY = ptrPiece -> posY;
        knight -> didWalk = true;

        pieces.push_back(knight);
        squares[ptrPiece -> row][ptrPiece -> col] -> piece = knight;
    } else if (name == "bishop")
    {
        Bishop* bishop = new Bishop(ptrPiece -> color, ptrPiece -> row, ptrPiece -> col);
        bishop -> posX = ptrPiece -> posX;
        bishop -> posY = ptrPiece -> posY;
        bishop -> didWalk = true;

        pieces.push_back(bishop);
        squares[ptrPiece -> row][ptrPiece -> col] -> piece = bishop;
    }

    pieces.erase(std::remove(pieces.begin(), pieces.end(), ptrPiece), pieces.end());
}


