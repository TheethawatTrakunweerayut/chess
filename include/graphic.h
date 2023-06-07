#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "board.h"
#include "piece.h"

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <vector>
#include <array>

class Graphic
{
    public:
        static constexpr unsigned int WIDTH = 1400;
        static constexpr unsigned int HEIGHT = 1400;
        static constexpr unsigned int WIDTH_POPUP = 350;
        static constexpr unsigned int HEIGHT_POPUP = 350;
        static std::array<std::array<int, 2>, 4> locTextPromotion;
        struct RGBA 
        {
            uint8_t R;
            uint8_t G;
            uint8_t B;
            uint8_t A;
        };
        static const RGBA white;
        static const RGBA black;
        static const RGBA highlight;
        static const RGBA grey;
        static void showBoard(sf::RenderWindow& window, Board& board);
        static void showPieces(sf::RenderWindow& window, std::vector<Piece*> pieces);
        static void showPopup(sf::RenderWindow& popup, std::string color);
        static void highlightOption(sf::RenderWindow& popup, sf::Vector2i mousePosition);
};

#endif