#include "triplecolor.hpp"
#include "support_function.hpp"
#include <iostream>

TripleColor::TripleColor()
{
    this->FillColor = sf::Color::White;
    this->TextColor = sf::Color::Black;
    this->OutlineColor = sf::Color::Black;
}
TripleColor::TripleColor(sf::Color FillColor)
{
    this->FillColor = FillColor;
    this->TextColor = sf::Color::Black;
    this->OutlineColor = sf::Color::Black;
}
TripleColor::TripleColor(sf::Color FillColor, sf::Color TextColor)
{
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = sf::Color::Black;
}
TripleColor::TripleColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor)
{
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = OutlineColor;
}

void TripleColor::changeFillColor(sf::Color FillColor)
{
    this->FillColor = FillColor;
}

void TripleColor::changeTextColor(sf::Color TextColor)
{
    this->TextColor = TextColor;
}

void TripleColor::changeOutlineColor(sf::Color OutlineColor)
{
    this->OutlineColor = OutlineColor;
}

void TripleColor::changeColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor)
{
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = OutlineColor;
}

void TripleColor::Coloring(sf::RectangleShape &shape, sf::Text &text)
{
    shape.setFillColor(this->FillColor);
    text.setFillColor(this->TextColor);
    shape.setOutlineColor(this->OutlineColor);
}

void TripleColor::Coloring(sf::CircleShape &shape, sf::Text &text)
{
    shape.setFillColor(this->FillColor);
    text.setFillColor(this->TextColor);
    shape.setOutlineColor(this->OutlineColor);
}

void TripleColor::Coloring(sf::CircleShape &shape, sf::Text &text, double ratio)
{
    shape.setFillColor(this->FillColor * ratio);
    text.setFillColor(this->TextColor * ratio);
    shape.setOutlineColor(this->OutlineColor * ratio);
}