#include "button.hpp"
#include <iostream>

Button::Button(float x, float y, float width, float height, 
        sf::Font* font, std::string str, 
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(str);
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

    //Hold - 3
    if (this->canEnable == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (this->buttonState == BTN_ACTIVE || this->buttonState == BTN_HOLD))
    {
        this->buttonState = BTN_HOLD;
    }

    //Pressed - 2
    else if (this->canEnable == true && this->shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->buttonState = BTN_ACTIVE;
    }

    //Hover - 1
    else if (canEnable == false && this->shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->canEnable = false;
        this->buttonState = BTN_HOVER;
    }
    else if (this->shape.getGlobalBounds().contains(mousePos)) 
    {
        this->canEnable = true;
        this->buttonState = BTN_HOVER;
    }
    //Idle - 0
    else 
    {
        this->canEnable = false;
        this->buttonState = BTN_IDLE;
    }

    switch (this->buttonState)
    {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;

        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;

        case BTN_ACTIVE: case BTN_HOLD:
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