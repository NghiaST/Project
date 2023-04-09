#include "button.hpp"
#include <iostream>

Button::Button(int x, int y, int width, int height, sf::Font *font, bool view, bool keepActive, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2)
    : Node(x, y, font, word, sizeText, idleColor, hoverColor, activeColor, runColor, runColor2)
{
    this->view = view;
    this->keepActive = keepActive;

    this->width = width;
    this->height = height;

    // shape
    this->thickness = 2;

    this->SetOutlineColor(0, sf::Color::Black);
    this->SetOutlineColor(1, sf::Color::Black);
    this->SetOutlineColor(2, sf::Color::Black);
    this->SetOutlineColor(3, sf::Color::Black);
    this->SetOutlineColor(4, sf::Color::Black);

    this->SetTextColor(0, sf::Color::Black);
    this->SetTextColor(1, sf::Color::Black);
    this->SetTextColor(2, sf::Color::Black);
    this->SetTextColor(3, sf::Color::Black);
    this->SetTextColor(4, sf::Color::Black);
    
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
    this->shape.setPosition(sf::Vector2f(this->x, this->y));
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);
    this->text.setFont(*this->font);
    this->text.setString(this->word);
    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->x + this->width / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->y + this->height / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );

    this->listColor[this->status].Coloring(this->shape, this->text);
}

void Button::render(sf::RenderWindow* window) 
{
    if (this->view == false) return;
    this->refreshrender();
    window->draw(this->shape);
    window->draw(this->text);
}