#include "button.hpp"
#include <iostream>

Button::Button(float x, float y, float width, float height, 
        sf::Font* font, std::string text, 
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(16);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);

// Init
    this->thickness = 2;
    this->idleOutlineColor = sf::Color::Black;

    this->text.setFillColor(sf::Color::Black);
    this->shape.setOutlineThickness(this->thickness);
    this->shape.setOutlineColor(this->idleOutlineColor);
}

Button::~Button() {
}

const bool Button::isPressed() const {
    if (this->buttonState == BTN_ACTIVE)
        return true;

    return false;
}

void Button::update(sf::Vector2f mousePos) {
    /* update the booleans for hover and pressed */

    //Idle
    this->buttonState = BTN_IDLE;
    
    //Hover
    if (this->shape.getGlobalBounds().contains(mousePos)) 
    {
        this->buttonState = BTN_HOVER;
    }
    
    //Pressed
    if (this->shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->buttonState = BTN_ACTIVE;
    }

    switch (this->buttonState)
    {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;

        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;

        case BTN_ACTIVE:
            this->shape.setFillColor(this->activeColor);
            break;

        default:
            this->shape.setFillColor(sf::Color::Red);
            break;
    }
}

void Button::render(sf::RenderTarget* target) {
    target->draw(this->shape);
    target->draw(this->text);
}