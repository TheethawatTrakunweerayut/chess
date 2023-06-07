#include "piece.h"
#include "square.h"
#include "rule.h"

#include <string>
#include <vector>
#include <array>
#include <filesystem>
#include <cstdint>

Piece::Piece(void) = default;

Piece::Piece(std::string name, std::string color, uint8_t row, uint8_t col)
{
    this -> name = name;
    this -> color = color;
    this -> row = row;
    this -> col = col;
    this -> posX = col * Square::SIZE;
    this -> posY = row * Square::SIZE;
}

std::vector<std::array<uint8_t, 2>> Piece::possibleMoves([[maybe_unused]]std::array<std::array<Square*, 8>, 8> squares)
{
    throw std::logic_error("Derived class must override Piece::possibleMoves");
}

bool Piece::sameColor(Piece* otherPiece)
{
    if (otherPiece -> color == this -> color)
    {
        return true;
    } else return false;
}

Pawn::Pawn(void) = default;

Pawn::Pawn(std::string color, uint8_t row, uint8_t col)
    :Piece("pawn", color, row, col)
{
    (this -> color == "white") ? (this -> dir.insert(dir.end(), {{-1, 0}, {-1, 1}, {-1, -1}})) : (this -> dir.insert(dir.end(), {{1, 0}, {1, 1}, {1, -1}}));
    this -> texture = std::filesystem::current_path().string() + "/assets/images/" + this -> color + '_' + this -> name + ".png";
}

std::vector<std::array<uint8_t, 2>> Pawn::possibleMoves(std::array<std::array<Square*, 8>, 8> squares)
{
    uint8_t a, b;

    std::vector<std::array<uint8_t, 2>> moves;
    a = static_cast<uint8_t>(this -> row + (this -> dir[0][0]));
    b = this -> col;

    if (Rule::validRowCol(a, b) && !squares[a][b] -> hasPiece())
    {
        moves.push_back({a, b});
        a = static_cast<uint8_t>(this -> row + (2 * (this -> dir[0][0])));
        b = this -> col;
        if ((!squares[a][b] -> hasPiece()) && (!(this -> didWalk)))
        {
            moves.push_back({a, b});
        }
    }
    for (uint8_t i = 1; i < 3; i++)
    {
        a = static_cast<uint8_t>(this -> row + (this -> dir[i][0]));
        b = static_cast<uint8_t>(this -> col + (this -> dir[i][1]));
        if (Rule::validRowCol(a, b) && (squares[a][b] -> hasPiece()))
        {
            if (!Piece::sameColor(squares[a][b] -> piece))
            {
                moves.push_back({a, b});
            }
        }
    }

    return moves;
}

Knight::Knight(void) = default;

Knight::Knight(std::string color, uint8_t row, uint8_t col)
    :Piece("knight", color, row, col)
{
    this -> texture = std::filesystem::current_path().string() + "/assets/images/" + this -> color + '_' + this -> name + ".png";
    this -> dir.insert(dir.end(), {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
}

std::vector<std::array<uint8_t, 2>> Knight::possibleMoves(std::array<std::array<Square*, 8>, 8> squares)
{
    uint8_t a, b, c, d;
    
    std::vector<std::array<uint8_t, 2>> moves;
    for (std::array<int8_t, 2> di : this -> dir)
    {
        a = static_cast<uint8_t>(this -> row + di[0]);
        b = static_cast<uint8_t>(this -> col + (2 * di[1]));
        c = static_cast<uint8_t>(this -> row + (2 * di[0]));
        d = static_cast<uint8_t>(this -> col + di[1]);
        if (Rule::validRowCol(a, b))
        {
            if ((!squares[a][b] -> hasPiece()) || (squares[a][b] -> hasPiece() && !Piece::sameColor(squares[a][b] -> piece)))
            {
                moves.push_back({a, b});
            }
        }
        if (Rule::validRowCol(c, d))
        {
            if ((!squares[c][d] -> hasPiece()) || (squares[c][d] -> hasPiece() && !Piece::sameColor(squares[c][d] -> piece)))
            {
                moves.push_back({c, d});
            }
        }
    }

    return moves;
}

Bishop::Bishop(void) = default;

Bishop::Bishop(std::string color, uint8_t row, uint8_t col)
    :Piece("bishop", color, row, col)
{
    this -> texture = std::filesystem::current_path().string() + "/assets/images/" + this -> color + '_' + this -> name + ".png";
    this -> dir.insert(dir.end(), {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
}

std::vector<std::array<uint8_t, 2>> Bishop::possibleMoves(std::array<std::array<Square*, 8>, 8> squares)
{
    uint8_t a, b;
    bool foundPiece = false;

    std::vector<std::array<uint8_t, 2>> moves;
    for (std::array<int8_t, 2> di : this -> dir)
    {
        for (uint8_t i = 1; i < 8; i++)
        {
            a = static_cast<uint8_t>(this -> row + (i * di[0]));
            b = static_cast<uint8_t>(this -> col + (i * di[1]));
            if (Rule::validRowCol(a, b) && (!foundPiece))
            {
                if (!squares[a][b] -> hasPiece())
                {
                    moves.push_back({a, b});
                } else if (squares[a][b] -> hasPiece())
                {
                    if (!Piece::sameColor(squares[a][b] -> piece))
                    {
                        moves.push_back({a, b});
                    }
                    foundPiece = true;
                }
            }
        }
        foundPiece = false;
    }

    return moves;
}

Rook::Rook(void) = default;

Rook::Rook(std::string color, uint8_t row, uint8_t col)
    :Piece("rook", color, row, col)
{
    this -> texture = std::filesystem::current_path().string() + "/assets/images/" + this -> color + '_' + this -> name + ".png";
    this -> dir.insert(dir.end(), {{1, 0}, {-1, 0}, {0, 1}, {0, -1}});
}

std::vector<std::array<uint8_t, 2>> Rook::possibleMoves(std::array<std::array<Square*, 8>, 8> squares)
{
    uint8_t a, b;
    bool foundPiece = false;

    std::vector<std::array<uint8_t, 2>> moves;
    for (std::array<int8_t, 2> di : this -> dir)
    {
        for (uint8_t i = 1; i < 8; i++)
        {
            a = static_cast<uint8_t>(this -> row + (i * di[0]));
            b = static_cast<uint8_t>(this -> col + (i * di[1]));
            if (Rule::validRowCol(a, b) && !foundPiece)
            {
                if (!squares[a][b] -> hasPiece())
                {
                    moves.push_back({a, b});
                } else if (squares[a][b] -> hasPiece())
                {
                    if (!Piece::sameColor(squares[a][b] -> piece))
                    {
                        moves.push_back({a, b});
                    }

                    foundPiece = true;
                }
            }
        }
        foundPiece = false;
    }

    return moves;
}

Queen::Queen(void) = default;

Queen::Queen(std::string color, uint8_t row, uint8_t col)
    :Piece("queen", color, row, col)
{
    this -> texture = std::filesystem::current_path().string() + "/assets/images/" + this -> color + '_' + this -> name + ".png";
    this -> dir.insert(dir.end(), {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}});
}

std::vector<std::array<uint8_t, 2>> Queen::possibleMoves(std::array<std::array<Square*, 8>, 8> squares)
{
    uint8_t a, b;
    bool foundPiece = false;

    std::vector<std::array<uint8_t, 2>> moves;
    for (std::array<int8_t, 2> di : this -> dir)
    {
        for (uint8_t i = 1; i < 8; i++)
        {
            a = static_cast<uint8_t>(this -> row + (i * di[0]));
            b = static_cast<uint8_t>(this -> col + (i * di[1]));
            if (Rule::validRowCol(a, b) && !foundPiece)
            {
                if (!squares[a][b] -> hasPiece())
                {
                    moves.push_back({a, b});
                } else if (squares[a][b] -> hasPiece())
                {
                    if (!Piece::sameColor(squares[a][b] -> piece))
                    {
                        moves.push_back({a, b});
                    }

                    foundPiece = true;
                }
            }
        }
        foundPiece = false;
    }

    return moves;
}

King::King(void) = default;

King::King(std::string color, uint8_t row, uint8_t col)
    :Piece("king", color, row, col)
{
    this -> texture = std::filesystem::current_path().string() + "/assets/images/" + this -> color + '_' + this -> name + ".png";
    this -> dir.insert(dir.end(), {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}});
}

std::vector<std::array<uint8_t, 2>> King::possibleMoves(std::array<std::array<Square*, 8>, 8> squares)
{
    uint8_t a, b;

    std::vector<std::array<uint8_t, 2>> moves;
    for (std::array<int8_t, 2> di : dir)
    {
        a = static_cast<uint8_t>(this -> row + di[0]);
        b = static_cast<uint8_t>(this -> col + di[1]);
        if (Rule::validRowCol(a, b))
        {
            if ((!squares[a][b] -> hasPiece()) || (squares[a][b] -> hasPiece() && (!Piece::sameColor(squares[a][b] -> piece))))
            {
                moves.push_back({a, b});
            }
        }
    }

    return moves;
}
