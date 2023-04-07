#include "button.hpp"
#include <iostream>

Button::Button(float x, float y, float width, float height, 
        sf::Font* font, std::string str, int strsize,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color runningColor)
{
    // Default
    this->shapeState = SHAPE_IDLE;
    this->active = false;

    // Assign
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;

    this->text.setFont(*this->font);
    this->text.setString(str);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(strsize);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    this->runningColor = runningColor;

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
    if (this->shapeState == SHAPE_ACTIVE)
        return true;

    return false;
}

void Button::update(sf::Vector2f mousePos) {
    int mouseType = 0;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mouseType = 1;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        mouseType = 2;
    this->updateStatus(mousePos, mouseType, this->shape.getGlobalBounds().contains(mousePos));

    switch (this->shapeState)
    {
        case SHAPE_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;

        case SHAPE_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;

        case SHAPE_ACTIVE: case SHAPE_HOLD:
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