#include "ElementColor.hpp"
#include "support_function.hpp"
#include <iostream>

ElementColor::ElementColor()
{
    this->FillColor = sf::Color::White;
    this->TextColor = sf::Color::Black;
    this->OutlineColor = sf::Color::Black;
}
ElementColor::ElementColor(sf::Color FillColor)
{
    this->FillColor = FillColor;
    this->TextColor = sf::Color::Black;
    this->OutlineColor = sf::Color::Black;
}
ElementColor::ElementColor(sf::Color FillColor, sf::Color TextColor)
{
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = sf::Color::Black;
}
ElementColor::ElementColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor)
{
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = OutlineColor;
}

void ElementColor::changeFillColor(sf::Color FillColor)
{
    this->FillColor = FillColor;
}

void ElementColor::changeTextColor(sf::Color TextColor)
{
    this->TextColor = TextColor;
}

void ElementColor::changeOutlineColor(sf::Color OutlineColor)
{
    this->OutlineColor = OutlineColor;
}

void ElementColor::changeColor(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor)
{
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = OutlineColor;
}

void ElementColor::Coloring(sf::RectangleShape &shape, sf::Text &text)
{
    shape.setFillColor(this->FillColor);
    text.setFillColor(this->TextColor);
    shape.setOutlineColor(this->OutlineColor);
}

void ElementColor::Coloring(sf::CircleShape &shape, sf::Text &text)
{
    shape.setFillColor(this->FillColor);
    text.setFillColor(this->TextColor);
    shape.setOutlineColor(this->OutlineColor);
}

void ElementColor::Coloring(sf::CircleShape &shape, sf::Text &text, double ratio)
{
    shape.setFillColor(this->FillColor * ratio);
    text.setFillColor(this->TextColor * ratio);
    shape.setOutlineColor(this->OutlineColor * ratio);
}

void ElementColor::Coloring(sf::RectangleShape &shape, sf::Text &text, double ratio)
{
    shape.setFillColor(this->FillColor * ratio);
    text.setFillColor(this->TextColor * ratio);
    shape.setOutlineColor(this->OutlineColor * ratio);
}

void ElementColor::Coloring(sf::RectangleShape &shape)
{
    shape.setFillColor(this->FillColor);
    shape.setOutlineColor(this->OutlineColor);
}

void ElementColor::Coloring(sf::ConvexShape &shape)
{
    shape.setFillColor(this->FillColor);
    shape.setOutlineColor(this->OutlineColor);
}