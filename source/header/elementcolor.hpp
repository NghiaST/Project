#ifndef __triplecolor_hpp__
#define __triplecolor_hpp__
#include <SFML/Graphics.hpp>

struct ElementColor {
private:
    sf::Color FillColor;
    sf::Color TextColor;
    sf::Color OutlineColor;
public:
    ElementColor();
    ElementColor(sf::Color FillColor);
    ElementColor(sf::Color FillColor, sf::Color TextColor);
    ElementColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor);
    void changeFillColor(sf::Color FillColor);
    void changeTextColor(sf::Color TextColor);
    void changeOutlineColor(sf::Color OutlineColor);
    void changeColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor);
    void Coloring(sf::CircleShape& shape, sf::Text& text);
    void Coloring(sf::RectangleShape& shape, sf::Text& text);
    void Coloring(sf::CircleShape& shape, sf::Text& text, double ratio);
};

#endif
