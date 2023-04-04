#include "inputbox.hpp"

InputBox::InputBox(float x, float y, float width, float height, sf::Font* font)
{
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOutlineThickness(1);
    this->shape.setOutlineColor(sf::Color::Black);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(12);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );
}

InputBox::~InputBox()
{

}

void InputBox::Add(int unicode)
{
    this->str += (char) unicode;
}

void InputBox::Del()
{
    if (this->str.size() > 0) {
        this->str.pop_back();
    }
}

void InputBox::update(int unicode)
{
    if (unicode == 8) this->Del();
    else if ('0' <= unicode && unicode <= '9') this->Add(unicode);
    else if (unicode == 13 || unicode == 10) {
        // return;
    }
    else this->Add(unicode);

    // rerender
    this->text.setString(this->str);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );
}

std::string InputBox::getString()
{
    std::string str = this->str;
    this->str = "";
    return str;
}

void InputBox::render(sf::RenderTarget* target) {
    target->draw(this->shape);
    target->draw(this->text);
}
