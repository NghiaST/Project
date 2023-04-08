#include "button.hpp"
#include <iostream>

Button::Button(float x, float y, float width, float height, 
        sf::Font* font, bool view, bool keepActive, std::string str, int strsize,
        sf::Color idleFillColor, sf::Color hoverFillColor, sf::Color activeFillColor, sf::Color runFillColor)
{
    this->status = 0;
    this->view = view;
    this->keepActive = keepActive;

    // shape
    this->thickness = 2;

    // font
    this->font = font;

    // color
    this->idleFillColor = idleFillColor;
    this->hoverFillColor = hoverFillColor;
    this->activeFillColor = activeFillColor;
    this->runFillColor = runFillColor;

    this->idleOutlineColor = sf::Color::Black;
    this->hoverOutlineColor = sf::Color::Black;
    this->activeOutlineColor = sf::Color::Black;
    this->runOutlineColor = sf::Color::Black;

    this->textColor = sf::Color::Black;

    ///--- Setup
    // shape
    this->shape.setOutlineThickness(this->thickness);
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    // text
    this->text.setFont(*this->font);
    this->text.setString(str);
    this->text.setCharacterSize(strsize);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );
    
    refreshrender();
}

Button::~Button() {
}

const bool Button::isPressed() const {
    if (this->status == 2)
        return true;

    return false;
}

void Button::setView(bool view)
{
    this->view = view;
}

void Button::changeView()
{
    this->view ^= 1;
}

void Button::setStatus(int status)
{
    this->status = status;
}

bool Button::getView()
{
    return this->view;
}

void Button::update(sf::Vector2f mousePos, int mouseType) 
{
    // enum MOUSE{MSE_NONE = 0, MSE_LEFTCLICK, MSE_RIGHTCLICK, MSE_LEFTHOLD, MSE_RIGHTHOLD};
    if (this->view == false) return;
    const static int MSE_LEFTCLICK = 1;
    const static int MSE_LEFTHOLD = 3;
    bool isInside = this->shape.getGlobalBounds().contains(mousePos);
    switch (this->status)
    {
        case 0 : 
            this->status = isInside;
            break;
        case 1 :
            this->status = isInside;
            if (this->status == 1 && mouseType == MSE_LEFTCLICK)
                this->status = 2;
            break;
        case 2 :
            if (mouseType == MSE_LEFTHOLD)
                this->status = 2;
            else if (this->keepActive == true)
                this->status = 3;
            else 
                this->status = isInside;
            break;
        case 3 :
            if (mouseType == MSE_LEFTCLICK && isInside)
                this->status = 2;
            break;
        default :
            exit(2);
    }
}

void Button::refreshrender()
{
    this->text.setFillColor(this->textColor);
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
            this->shape.setOutlineColor(this->runOutlineColor);
            break;
    }
}

void Button::render(sf::RenderTarget* target) 
{
    if (this->view == false) return;
    this->refreshrender();
    target->draw(this->shape);
    target->draw(this->text);
}