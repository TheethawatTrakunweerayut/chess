#include "graphic.h"
#include "dragger.h"
#include "rule.h"
#include "board.h"
#include "square.h"
#include "piece.h"
#include "sound.h"

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode(Graphic::WIDTH, Graphic::HEIGHT), "Chess");

    sf::RenderWindow popup(sf::VideoMode(Graphic::WIDTH_POPUP, Graphic::HEIGHT_POPUP), "Promoting");
    popup.setVisible(false);

    Sound::initialization();
    Rule::initialization();

    Board board;
    board.addPieces();

    uint8_t row, col;

    while (window.isOpen())
    {
        window.clear();
        popup.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                popup.close();
            } else if (event.type == sf::Event::MouseButtonPressed)
            {
                Dragger::updatePressedPos(event.mouseButton.x, event.mouseButton.y);
                row = Dragger::y / Square::SIZE;
                col = Dragger::x / Square::SIZE;

                if (board.squares[row][col] -> hasPiece())
                {
                    Square* ptrSquare = board.squares[row][col];
                    Piece* ptrPiece = ptrSquare -> piece;
                    if (Rule::validTurn(ptrPiece))
                    {
                        std::vector<Piece*>::iterator iter = std::find(board.pieces.begin(), board.pieces.end(), ptrPiece);
                        std::iter_swap(iter, board.pieces.end() - 1);

                        Dragger::dragPiece(ptrSquare, ptrPiece);
                        Dragger::updatePos(ptrSquare);
                    }
                }
                
            } else if (event.type == sf::Event::MouseMoved)
            {
                if (Dragger::dragging)
                {
                    Dragger::updatePressedPos(event.mouseMove.x, event.mouseMove.y);

                    row = Dragger::y / Square::SIZE;
                    col = Dragger::x / Square::SIZE;
                    Square* ptrSquare = board.squares[row][col];

                    Dragger::updatePos(ptrSquare);
                }
            } else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (Dragger::ptrPiece != nullptr)
                {
                    row = Dragger::y / Square::SIZE;
                    col = Dragger::x / Square::SIZE;
                    Square* ptrSquare = board.squares[row][col];

                    Dragger::undragPiece(board.squares, board.pieces, ptrSquare);
                }
            }
        }

        if (Rule::promoting) 
        {
            popup.setVisible(true);
            popup.setActive(true);
            window.setActive(false);

            Graphic::showPopup(popup, Rule::colorPromoting);

            sf::Event eventPopup;

            sf::Vector2i mousePosition = sf::Mouse::getPosition(popup);
            if (mousePosition.x >= 0 && mousePosition.y >= 0)
            {
                Graphic::highlightOption(popup, mousePosition);

                while (popup.pollEvent(eventPopup))
                {
                    if (eventPopup.type == sf::Event::MouseButtonReleased)
                    {
                        popup.setVisible(false);
                        popup.setActive(false);
                        window.setActive(true);

                        uint8_t optionRow = mousePosition.y / Square::SIZE;
                        uint8_t optionCol = mousePosition.x / Square::SIZE;

                        Rule::changePiece(board.squares, board.pieces, Dragger::ptrPiecePromoted, optionRow, optionCol);

                        Sound::promote();

                        Rule::promoting = false;
                    }
                }
            }
        }
        Graphic::showBoard(window, board);
        Graphic::showPieces(window, board.pieces);
        window.display();
        popup.display();
    }

    return 0;
}