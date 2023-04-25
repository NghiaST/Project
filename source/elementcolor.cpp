#include "ElementColor.hpp"
#include "support_function.hpp"
#include <iostream>

ElementColor::ElementColor()
{
    this->FillColor = sf::Color(0, 0, 0, 0);
    this->TextColor = sf::Color(0, 0, 0, 0);
    this->OutlineColor = sf::Color(0, 0, 0, 0);
}
ElementColor::ElementColor(sf::Color FillColor)
{
    this->FillColor = FillColor;
    this->TextColor = sf::Color::Transparent;
    this->OutlineColor = sf::Color::Transparent;
}
ElementColor::ElementColor(sf::Color FillColor, sf::Color TextColor)
{
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = sf::Color::Transparent;
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

sf::Color ElementColor::getFillColor()
{
    return this->FillColor;
}
sf::Color ElementColor::getTextColor()
{
    return this->TextColor;
}
sf::Color ElementColor::getOutlineColor()
{
    return this->OutlineColor;
}

void ElementColor::Coloring(sf::Shape &shape)
{
    shape.setFillColor(this->FillColor);
    shape.setOutlineColor(this->OutlineColor);
}

void ElementColor::Coloring(sf::Shape &shape, sf::Text &text)
{
    shape.setFillColor(this->FillColor);
    text.setFillColor(this->TextColor);
    shape.setOutlineColor(this->OutlineColor);
}

void ElementColor::Coloring(sf::Shape &shape, sf::Text &text, double ratio)
{
    shape.setFillColor(appearColor(this->FillColor, ratio));
    text.setFillColor(appearColor(this->TextColor, ratio));
    shape.setOutlineColor(appearColor(this->OutlineColor, ratio));
}

void ElementColor::Coloring(sf::Shape &shape, sf::Text &text, double ratio, ElementColor eColor)
{
    shape.setFillColor(convertColor(eColor.getFillColor(), this->FillColor, ratio));
    text.setFillColor(convertColor(eColor.getTextColor(), this->TextColor, ratio));
    shape.setOutlineColor(convertColor(eColor.getOutlineColor(), this->OutlineColor, ratio));
}