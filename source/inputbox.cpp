#include "inputbox.hpp"

InputBox::InputBox(float x, float y, float width, float height, sf::Font* font, std::string str_const)
{
    // Default
    this->idleOutlineColor = sf::Color::Black;
    this->activeOutlineColor = sf::Color::Yellow;
    this->active = false;
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOutlineThickness(2);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(12);

    // assign
    this->str_const = str_const;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineColor(this->idleOutlineColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );

    this->text.setString(this->str_const);
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

void InputBox::update(sf::Vector2f mousePos, int unicode)
{
    int mouseType = 0;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mouseType = 1;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        mouseType = 2;
    this->updateStatus(mousePos, mouseType, this->shape.getGlobalBounds().contains(mousePos));

    if (mouseType == 1)
    {
        if (this->shape.getGlobalBounds().contains(mousePos))
            this->active = true;
        else 
            this->active = false;
    }

    if (this->active == true) {
        if (unicode == 0) ;
        else if (unicode == 8) this->Del();
        else if ('0' <= unicode && unicode <= '9') this->Add(unicode);
        else if (unicode == 13 || unicode == 10) {
            // return;
        }
        else this->Add(unicode);
    }

    // freshrender
    this->text.setString(this->str_const + this->str);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f, 
        this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f - 2
    );
    if (this->active == false) {
        this->shape.setOutlineColor(this->idleOutlineColor);
    }
    else {
        this->shape.setOutlineColor(this->activeOutlineColor);
    }
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
