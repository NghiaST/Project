#include "inputbox.hpp"

InputBox::InputBox(float x, float y, float width, float height, sf::Font* font, bool view, std::string str_const)
{
    this->active = false;
    this->status = 0;
    this->view = view;

    // string
    this->str_const = str_const;
    this->str = "";

    // font
    this->font = font;

    // text
    this->strsize = 12;

    // shape
    this->thickness = 2;

    // color
    this->defaultTextColor = sf::Color::White;
    this->defaultFillColor = sf::Color::Black;
    this->idleOutlineColor = sf::Color(30, 30, 30, 255);
    this->activeOutlineColor = sf::Color::Yellow;
    
    // render

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setFillColor(this->defaultFillColor);
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineThickness(this->thickness);
    this->shape.setOutlineColor(this->idleOutlineColor);
    
    this->text.setString(this->str_const);
    this->text.setFillColor(this->defaultTextColor);
    this->text.setCharacterSize(this->strsize);
    this->text.setFont(*this->font);
    this->text.setPosition(
        this->shape.getPosition().x + 10, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );
}

InputBox::~InputBox()
{

}

void InputBox::setView(bool view)
{
    this->view = view;
}
void InputBox::changeView()
{
    this->view ^= 1;
}

std::string InputBox::getString()
{
    return this->str;
}


void InputBox::Add(int keyboardType)
{
    this->str += (char) keyboardType;
}

void InputBox::Del()
{
    if (this->str.size() > 0) {
        this->str.pop_back();
    }
}

void InputBox::update(sf::Vector2f mousePos, int mouseType, int keyboardType)
{
    this->updateStatus(mousePos, mouseType, keyboardType);

    if (mouseType == 1)
    {
        if (this->shape.getGlobalBounds().contains(mousePos))
            this->active = true;
        else 
            this->active = false;
    }

    if (this->active == true) {
        if (keyboardType == 0) ;
        else if (keyboardType == 8) this->Del();
        else if ('0' <= keyboardType && keyboardType <= '9') this->Add(keyboardType);
        else if (keyboardType == 13 || keyboardType == 10) {
            // return;
        }
        else this->Add(keyboardType);
    }

    refreshrender();
}

void InputBox::refreshrender()
{
    this->text.setString(this->str_const + this->str);
    this->text.setPosition(
        this->shape.getPosition().x + 10, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );
    if (this->active == false) {
        this->shape.setOutlineColor(this->idleOutlineColor);
    }
    else {
        this->shape.setOutlineColor(this->activeOutlineColor);
    }
}

void InputBox::render(sf::RenderTarget* target) {
    if (this->view == false) return;
    refreshrender();
    target->draw(this->shape);
    target->draw(this->text);
}
