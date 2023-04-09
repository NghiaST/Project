#ifndef __triplecolor_hpp__
#define __triplecolor_hpp__
#include <SFML/Graphics.hpp>

struct TripleColor {
private:
    sf::Color FillColor;
    sf::Color TextColor;
    sf::Color OutlineColor;
public:
    TripleColor();
    TripleColor(sf::Color FillColor);
    TripleColor(sf::Color FillColor, sf::Color TextColor);
    TripleColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor);
    void changeFillColor(sf::Color FillColor);
    void changeTextColor(sf::Color TextColor);
    void changeOutlineColor(sf::Color OutlineColor);
    void changeColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor);
    void Coloring(sf::CircleShape& shape, sf::Text& text);
    void Coloring(sf::RectangleShape& shape, sf::Text& text);
};

#endif
