#include "circlenode.hpp"
#include <iostream>

///------------------------------------------------------------
// CircleNode

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

///------------------------------------------------------------
// RectangleNode


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
