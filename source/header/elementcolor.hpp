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

    sf::Color getFillColor();
    sf::Color getTextColor();
    sf::Color getOutlineColor();

    void Coloring(sf::Shape& shape);
    void Coloring(sf::Shape& shape, sf::Text& text);
    void Coloring(sf::Shape& shape, sf::Text& text, double ratio);
    void Coloring(sf::Shape& shape, sf::Text& text, double ratio, ElementColor eColor);
};

#endif
