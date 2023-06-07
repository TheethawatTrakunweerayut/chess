#include "graphic.h"
#include "board.h"
#include "square.h"
#include "rule.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <vector>
#include <cstdint>
#include <filesystem>

const Graphic::RGBA Graphic::white = {189, 196, 180, 255};
const Graphic::RGBA Graphic::black = {129, 142, 112, 255};
const Graphic::RGBA Graphic::grey = {128, 128, 128, 50};
const Graphic::RGBA Graphic::highlight = {140, 164, 200, 200};

std::array<std::array<int, 2>, 4> Graphic::locTextPromotion = {{{0, 0}, {175, 0}, {0, 175}, {175, 175}}};

void Graphic::showBoard(sf::RenderWindow& window, Board& board)
{
    uint8_t r, g, b, a;
    
    for (std::array<Square*, 8> sqrow : board.squares)
    {
        for (Square* sq : sqrow)
        {
            (sq -> color == "white") ? (r = Graphic::white.R, g = Graphic::white.G, b = Graphic::white.B, a = Graphic::white.A):
            (sq -> color == "black") ? (r = Graphic::black.R, g = Graphic::black.G, b = Graphic::black.B, a = Graphic::black.A):
                                       (r = Graphic::highlight.R, g = Graphic::highlight.G, b = Graphic::highlight.B, a = Graphic::highlight.A);

            sf::RectangleShape rect(sf::Vector2f(sq -> SIZE, sq -> SIZE));
            rect.setPosition((sq -> col * sq -> SIZE), (sq -> row * sq -> SIZE));
            rect.setFillColor(sf::Color(r, g, b, a));

            window.draw(rect);
        }
    }
}

void Graphic::showPieces(sf::RenderWindow& window, std::vector<Piece*> pieces)
{
    sf::Texture texture;

    for (Piece* piece: pieces)
    {
        texture.loadFromFile(piece -> texture);
        sf::Sprite sprite(texture);
        sprite.setPosition((piece -> posX), (piece -> posY));
        window.draw(sprite);
    }
}

void Graphic::showPopup(sf::RenderWindow& popup, std::string color)
{
    sf::RectangleShape background(sf::Vector2f(Graphic::WIDTH_POPUP, Graphic::HEIGHT_POPUP));
    background.setFillColor(sf::Color(Graphic::white.R, Graphic::white.G, Graphic::white.B, Graphic::white.A));
    popup.draw(background);

    sf::Texture texture;
    std::string textPath;

    uint8_t i = 0;

    for (const auto& pair : Rule::namePromotion)
    {
        const std::string name = pair.second;
        textPath = std::filesystem::current_path().string() + "/assets/images/" + color + '_' + name + ".png";
        texture.loadFromFile(textPath);
        sf::Sprite sprite(texture);
        sprite.setPosition(Graphic::locTextPromotion[i][0], Graphic::locTextPromotion[i][1]);
        popup.draw(sprite);

        i++;
    }
}

void Graphic::highlightOption(sf::RenderWindow& popup, sf::Vector2i mousePosition)
{
    unsigned int row, col;
    row = mousePosition.y / Square::SIZE;
    col = mousePosition.x / Square::SIZE;

    sf::RectangleShape rect(sf::Vector2f(Square::SIZE, Square::SIZE));
    rect.setPosition((col * Square::SIZE), (row * Square::SIZE));
    rect.setFillColor(sf::Color(Graphic::grey.R, Graphic::grey.G, Graphic::grey.B, Graphic::grey.A));
    popup.draw(rect);
}