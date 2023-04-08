#include "node.hpp"
#include <iostream>

///--------------------------------------------------------------------
///--------------------------------Node--------------------------------

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

///--------------------------------------------------------------------
///-----------------------------CircleNode-----------------------------

CircleNode::CircleNode(int x, int y, int radius, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2)
    : Node(x, y, font, wordIn, idleFillColor, runFillColor, runFillColor2)
{
    // shape
    this->radius = radius;
    this->refreshrender();
}
CircleNode::~CircleNode()
{

}

int CircleNode::update(sf::Vector2f mousePos, int mouseType, int keyboardType) // check if CircleNode is active
{
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    return this->Node::update(mousePos, mouseType, keyboardType, isMouseInside);
}
void CircleNode::refreshrender()
{
    this->shape.setPosition(sf::Vector2f(this->x, this->y));
    this->shape.setRadius(this->radius);
    this->shape.setOutlineThickness(this->thickness);

    switch (this->status)
    {
        case 0:
            this->shape.setFillColor(this->idleFillColor);
            this->shape.setOutlineColor(this->idleOutlineColor);
            break;
        case 1:
            this->shape.setFillColor(this->hoverFillColor);
            this->shape.setOutlineColor(this->hoverOutlineColor);
            break;
        case 2:
            this->shape.setFillColor(this->activeFillColor);
            this->shape.setOutlineColor(this->activeOutlineColor);
            break;
        case 3:
            this->shape.setFillColor(this->runFillColor);
            this->shape.setOutlineColor(this->runFillColor);
            break;
        case 4:
            this->shape.setFillColor(this->runFillColor2);
            this->shape.setOutlineColor(this->runFillColor2);
            break;
    }

    this->textIn.setFont(*this->font);
    this->textIn.setString(this->wordIn);
    this->textIn.setFillColor(this->textInColor);

    this->textIn.setCharacterSize(this->sizeTextIn);
    this->textIn.setPosition(
        this->x + this->radius - this->textIn.getGlobalBounds().width / 2.f, 
        this->y + this->radius - this->textIn.getGlobalBounds().height / 2.f - 2
    );
}
void CircleNode::render(sf::RenderTarget* target) 
{
    this->refreshrender();

    target->draw(this->shape);
    target->draw(this->textIn);
}

///--------------------------------------------------------------------
///----------------------------RectangleNode---------------------------

RectangleNode::RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2)
    : Node(x, y, font, wordIn, idleFillColor, runFillColor, runFillColor2)
{
    // shape
    this->width = width;
    this->height = height;
    this->refreshrender();
}
RectangleNode::~RectangleNode()
{

}

int RectangleNode::update(sf::Vector2f mousePos, int mouseType, int keyboardType) // check if CircleNode is active
{
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    return this->Node::update(mousePos, mouseType, keyboardType, isMouseInside);
}
void RectangleNode::refreshrender()
{
    this->shape.setPosition(sf::Vector2f(this->x, this->y));
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);

    switch (this->status)
    {
        case 0:
            this->shape.setFillColor(this->idleFillColor);
            this->shape.setOutlineColor(this->idleOutlineColor);
            break;
        case 1:
            this->shape.setFillColor(this->hoverFillColor);
            this->shape.setOutlineColor(this->hoverOutlineColor);
            break;
        case 2:
            this->shape.setFillColor(this->activeFillColor);
            this->shape.setOutlineColor(this->activeOutlineColor);
            break;
        case 3:
            this->shape.setFillColor(this->runFillColor);
            this->shape.setOutlineColor(this->runFillColor);
            break;
        case 4:
            this->shape.setFillColor(this->runFillColor2);
            this->shape.setOutlineColor(this->runFillColor2);
            break;
    }

    this->textIn.setFont(*this->font);
    this->textIn.setString(this->wordIn);
    this->textIn.setFillColor(this->textInColor);

    this->textIn.setCharacterSize(this->sizeTextIn);
    this->textIn.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->textIn.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->textIn.getGlobalBounds().height / 2.f - 2
    );
}
void RectangleNode::render(sf::RenderTarget* target) 
{
    this->refreshrender();

    target->draw(this->shape);
    target->draw(this->textIn);
}
