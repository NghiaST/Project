#include "inputbox.hpp"

InputBox::InputBox(sf::Vector2f coord, float width, float height, float sizeText, float thickness, bool view, bool keepActive, int print_type, std::string textConst, sf::Font *font, Palette* palette)
    : Button(coord, width, height, sizeText, thickness, view, keepActive, print_type, textConst, font, palette)
{
    this->active = false;
    this->wordInput = "";
    refreshrender();
}

InputBox::~InputBox()
{

}

void InputBox::setWordInput(std::string wordInput)
{
    this->wordInput = wordInput;
}

std::string InputBox::getWordInput()
{
    return this->wordInput;
}

void InputBox::Add_Character(KEYBOARD keyboardType)
{
    this->wordInput += static_cast<char> (keyboardType);
}

void InputBox::Del_Character()
{
    if (this->wordInput.size() > 0) {
        this->wordInput.pop_back();
    }
}

void InputBox::update(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType)
{
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
                this->status = 3;
            break;
        case 3 :
            if (mouseType == MSE_LEFTCLICK)
                this->status = (isMouseInside ? 3 : 0);
            else 
                this->status = 3;
            break;
        default :
            std::cout << "Error inputbox.cpp 1\n";
            exit(2);
    }
    this->active = (this->status == 3);

    if (this->active == true) {
        if (keyboardType == KBD_BACKSPACE) 
            this->Del_Character();
        else if (keyboardType == KBD_NONE || keyboardType == KBD_NEWLINE || keyboardType == KBD_ENTER) 
            ; // do nothing
        else if ('0' <= static_cast<int>(keyboardType) && static_cast<int>(keyboardType) <= '9') 
            this->Add_Character(keyboardType);
        else 
            this->Add_Character(keyboardType);
    }
}

void InputBox::refreshrender() // override
{
    this->shape.setPosition(this->coord);
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);

    this->text.setFont(*this->font);
    this->text.setString((this->word + this->wordInput).c_str());

    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->coord.x + 10,
        this->coord.y + this->height / 2.0 - this->text.getGlobalBounds().height / 2.f - 2
    );
    
    palette->getColor(this->status).Coloring(this->shape, this->text);
}

void InputBox::render(sf::RenderWindow* window) {
    if (this->view == false) return;
    refreshrender();
    window->draw(this->shape);
    window->draw(this->text);
}
