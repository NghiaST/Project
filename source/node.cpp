#include "node.hpp"
#include <iostream>

Node::Node(int x, int y, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2)
{
    // Default
    this->status = 0;
    this->view = true;

    // Position
    this->x = x;
    this->y = y;

    // shape
    this->thickness = 2;

    // font
    this->font = font;

    // word
    this->wordIn = wordIn;
    this->wordOut = "";

    // wordsize
    this->sizeTextIn = 16;
    this->sizeTextOut = 12;

    // color
    this->idleFillColor = idleFillColor;
    this->hoverFillColor = sf::Color::Green;
    this->activeFillColor = sf::Color::Yellow;
    this->runFillColor = runFillColor;
    this->runFillColor2 = runFillColor2;

    this->idleOutlineColor = sf::Color::Black;
    this->hoverOutlineColor = sf::Color::Black;
    this->activeOutlineColor = sf::Color::Black;
    this->runOutlineColor = sf::Color::Black;
    this->runOutlineColor2 = sf::Color::Black;

    this->textInColor = sf::Color::Red;
    this->textOutColor = sf::Color::Blue;
}

Node::~Node()
{

}

void Node::setStatus(int status)
{
    this->status = status;
}
void Node::setX(int x) 
{
    this->x = x;
}
void Node::setY(int y)
{
    this->y = y;
}
void Node::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Node::setWordIn(std::string wordIn)
{
    this->wordIn = wordIn;
}
void Node::setWordOut(std::string wordOut)
{
    this->wordOut = wordOut;
}
void Node::setIDLEFillColor(sf::Color idleFillColor)
{
    this->idleFillColor = idleFillColor;
}
void Node::setIDLETextInColor(sf::Color idleOutlineColor)
{
    this->idleOutlineColor = idleOutlineColor;
}

int Node::getX()
{
    return this->x;
}
int Node::getY()
{
    return this->y;
}
int Node::getStatus()
{
    return this->status;
}

int Node::update(sf::Vector2f mousePos, int mouseType, int keyboardType, bool isMouseInside) // check if node is active
{
    const static int KBD_ENTER = 13;
    const static int KBD_DELETE = 127;
    const static int MSE_LEFTCLICK = 1;
    switch (this->status)
    {
        case 0 :
            this->status = isMouseInside;
            break;
        case 1 :
            this->status = isMouseInside;
            if (mouseType == MSE_LEFTCLICK)
                this->status = 2;
            break;
        case 2:
            if (keyboardType == KBD_DELETE) 
                this->status = -1;
            break;
        default :
            break;
    }
    return this->status;
}