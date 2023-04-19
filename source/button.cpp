#include "button.hpp"
#include <iostream>

Button::Button(sf::Vector2f coord, float width, float height, float sizeText, float thickness, bool view, bool keepActive, std::string word, sf::Font *font, Palette* palette)
    : Style(coord, sizeText, thickness, word, font, palette)
{
    this->view = view;
    this->keepActive = keepActive;

    this->width = width;
    this->height = height;
    
    refreshrender();
}

Button::~Button()
{
}

const bool Button::isPressed() const {
    if (this->status == 2)
        return true;

    return false;
}

void Button::update(sf::Vector2f mousePos, int mouseType) 
{
    // enum MOUSE{MSE_NONE = 0, MSE_LEFTCLICK, MSE_RIGHTCLICK, MSE_LEFTHOLD, MSE_RIGHTHOLD};
    if (this->view == false) return;
    const static int MSE_LEFTCLICK = 1;
    const static int MSE_LEFTHOLD = 3;
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    switch (this->status)
    {
        case 0 : 
            this->status = isMouseInside;
            break;
        case 1 :
            this->status = isMouseInside;
            if (this->status == 1 && mouseType == MSE_LEFTCLICK)
                this->status = 2;
            break;
        case 2 :
            if (mouseType == MSE_LEFTHOLD)
                this->status = 2;
            else if (this->keepActive == true)
                this->status = 3;
            else 
                this->status = isMouseInside;
            break;
        case 3 :
            if (mouseType == MSE_LEFTCLICK && isMouseInside)
                this->status = 2;
            break;
        default :
            exit(2);
    }
}

void Button::refreshrender()
{
    this->shape.setPosition(this->coord);
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);
    this->text.setFont(*this->font);
    this->text.setString(this->word.c_str());
    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->coord.x + this->width / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->coord.y + this->height / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );
    palette->getColor(this->status).Coloring(this->shape, this->text);
}

void Button::render(sf::RenderWindow* window) 
{
    if (this->view == false) return;
    this->refreshrender();
    window->draw(this->shape);
    window->draw(this->text);
}