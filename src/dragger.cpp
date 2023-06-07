#include "dragger.h"
#include "square.h"
#include "piece.h"
#include "rule.h"
#include "sound.h"

#include <SFML/Audio.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include <iostream>

unsigned int Dragger::x;
unsigned int Dragger::y;

Square* Dragger::ptrInitSquare = nullptr;
Square* Dragger::ptrPrevSquare = nullptr;

std::string Dragger::initSquareColor = "";
std::string Dragger::prevSquareColor = "";

Piece* Dragger::ptrPiece = nullptr;
Piece* Dragger::prevPtrPiece = nullptr;
Piece* Dragger::ptrPiecePromoted = nullptr;

bool Dragger::dragging = false;

void Dragger::updatePressedPos(unsigned int x, unsigned int y)
{
    Dragger::x = x;
    Dragger::y = y;
}

void Dragger::dragPiece(Square* ptrSquare, Piece* ptrPiece)
{
    if ((Dragger::initSquareColor != "") && (Dragger::prevSquareColor != ""))
    {
        Dragger::ptrPrevSquare -> color = Dragger::prevSquareColor;
        Dragger::ptrInitSquare -> color = Dragger::initSquareColor;
    }

    Dragger::ptrInitSquare = ptrSquare;
    Dragger::ptrPrevSquare = ptrSquare;
    Dragger::initSquareColor = ptrSquare -> color;
    Dragger::prevSquareColor = ptrSquare -> color;

    ptrSquare -> color = "highlight";

    Dragger::ptrPiece = ptrPiece;
    Dragger::dragging = true;
}

void Dragger::undragPiece(std::array<std::array<Square*, 8>, 8> squares, std::vector<Piece*>& pieces, Square* ptrSquare)
{
    Dragger::dragging = false;

    bool canMove = false;

    if (Dragger::ptrInitSquare != ptrSquare)
    {
        if (Rule::isCastle(squares, pieces, ptrSquare, Dragger::ptrPiece))
        {
            canMove = true;

            std::string side;
            (ptrSquare -> col <= 2) ? (side = "left") : (side = "right");

            if (side == "left")
            {
                Piece* ptrRook = squares[ptrPiece -> row][0] -> piece;
                squares[ptrPiece -> row][0] -> piece = nullptr;

                squares[Dragger::ptrPiece -> row][3] -> piece = ptrRook;
                squares[Dragger::ptrPiece -> row][2] -> piece = Dragger::ptrPiece;

                ptrRook -> didWalk = true;

                Dragger::ptrPiece -> col = 2;
                Dragger::ptrPiece -> posX = 2 * Square::SIZE;

                ptrRook -> col = 3;
                ptrRook -> posX = 3 * Square::SIZE;
            } else
            {
                Piece* ptrRook = squares[ptrPiece -> row][7] -> piece;
                squares[Dragger::ptrPiece -> row][7] -> piece = nullptr;

                squares[Dragger::ptrPiece -> row][5] -> piece = ptrRook;
                squares[Dragger::ptrPiece -> row][6] -> piece = Dragger::ptrPiece;

                ptrRook -> didWalk = true;

                Dragger::ptrPiece -> col = 6;
                Dragger::ptrPiece -> posX = 6 * Square::SIZE;

                ptrRook -> col = 5;
                ptrRook -> posX = 5 * Square::SIZE;
            }

            Dragger::ptrPiece -> posY = Dragger::ptrPiece -> row * Square::SIZE;
            Sound::castle();

            Rule::kingLoc[Dragger::ptrPiece -> color] = {Dragger::ptrPiece -> row, Dragger::ptrPiece -> col};

        } else if (Rule::isEnpassant(squares, ptrSquare, Dragger::prevPtrPiece, Dragger::ptrPiece))
        {
            pieces.erase(std::remove(pieces.begin(), pieces.end(), Dragger::prevPtrPiece), pieces.end());
            squares[prevPtrPiece -> row][prevPtrPiece -> col] -> piece = nullptr;

            ptrSquare -> piece = Dragger::ptrPiece;
            Dragger::ptrInitSquare -> piece = nullptr;

            if (Rule::check(squares, pieces, Dragger::ptrPiece -> color))
            {
                pieces.push_back(Dragger::prevPtrPiece);
                squares[prevPtrPiece -> row][prevPtrPiece -> col] -> piece = Dragger::prevPtrPiece;
                Dragger::ptrInitSquare -> piece = Dragger::ptrPiece;
                ptrSquare -> piece = nullptr;
            } else
            {
                canMove = true;

                Dragger::ptrPiece -> row = ptrSquare -> row;
                Dragger::ptrPiece -> col = ptrSquare -> col;
                Dragger::ptrPiece -> posX = ptrSquare -> col * Square::SIZE;
                Dragger::ptrPiece -> posY = ptrSquare -> row * Square::SIZE;

                Sound::capture();
            }
            
        } else if (Rule::validMove(squares, ptrSquare, Dragger::ptrPiece))
        {
            if (Dragger::ptrPiece -> name == "king")
            {
                Rule::kingLoc[Dragger::ptrPiece -> color] = {ptrSquare -> row, ptrSquare -> col};
            }

            Piece* delPiece = nullptr;

            if (ptrSquare -> hasPiece())
            {
                delPiece = ptrSquare -> piece;
                pieces.erase(std::remove(pieces.begin(), pieces.end(), delPiece), pieces.end());
            } 

            Dragger::ptrInitSquare -> piece = nullptr;
            ptrSquare -> piece = Dragger::ptrPiece;

            if (Rule::check(squares, pieces, Dragger::ptrPiece -> color))
            {
                if (delPiece != nullptr)
                {
                    pieces.push_back(delPiece);
                }

                Dragger::ptrInitSquare -> piece = Dragger::ptrPiece;
                ptrSquare -> piece = delPiece;
            } else
            {
                canMove = true;

                if (delPiece != nullptr)
                {
                    Sound::capture();
                } else
                {
                    Sound::move();
                }

                Dragger::ptrPiece -> row = ptrSquare -> row;
                Dragger::ptrPiece -> col = ptrSquare -> col;
                Dragger::ptrPiece -> posX = ptrSquare -> col * Square::SIZE;
                Dragger::ptrPiece -> posY = ptrSquare -> row * Square::SIZE;
            }

        }
    }
    if (canMove)
    {
        Rule::whiteTurn = Rule::whiteTurn ^ 1;
        Dragger::prevPtrPiece = Dragger::ptrPiece;
        Dragger::ptrPiece -> didWalk = true;

        std::string color;
        (Dragger::ptrPiece -> color == "white") ? (color = "black") : (color = "white");

        if (Rule::check(squares, pieces, color))
        {
            Sound::check();
        }

        if (Rule::isPromoting(Dragger::ptrPiece))
        {
            Dragger::ptrPiecePromoted = Dragger::ptrPiece;
            Rule::promoting = true;
        }
    } else
    {
        Dragger::ptrPiece -> posX = Dragger::ptrInitSquare -> col * Square::SIZE;
        Dragger::ptrPiece -> posY = Dragger::ptrInitSquare -> row * Square::SIZE;
        if (Dragger::ptrPiece -> name == "king")
        {
            Rule::kingLoc[ptrPiece -> color] = {ptrInitSquare -> row, ptrInitSquare -> col};
        }
    }

    Dragger::ptrPiece = nullptr;
}

void Dragger::updatePos(Square* ptrSquare)
{
    Dragger::ptrPiece -> posX = Dragger::x - Square::HALF_SIZE;
    Dragger::ptrPiece -> posY = Dragger::y - Square::HALF_SIZE;
    
    if (ptrSquare != Dragger::ptrPrevSquare)
    {
        if (Dragger::ptrPrevSquare != Dragger::ptrInitSquare)
        {
            Dragger::ptrPrevSquare -> color = Dragger::prevSquareColor;
        }
        Dragger::prevSquareColor = ptrSquare -> color;
        ptrSquare -> color = "highlight";
    }

    Dragger::ptrPrevSquare = ptrSquare;
}
