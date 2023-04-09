#include "inputbox.hpp"

InputBox::InputBox(int x, int y, int width, int height, sf::Font* font, bool view, std::string textConst)
    : Node(x, y, font, textConst, 12, TripleColor(), TripleColor(), TripleColor(), TripleColor(), TripleColor())
{
    this->active = false;
    this->view = view;
    
    // shape
    this->width = width;
    this->height = height;

    // string
    this->wordInput = "";

    // text
    this->sizeText = 12;

    // shape
    this->thickness = 2;

    // color
    this->SetTextColor(0, sf::Color::Blue);
    this->SetFillColor(0, sf::Color::Transparent);
    this->SetColor(3, TripleColor(sf::Color(245, 194, 117), sf::Color::Red, sf::Color(190, 57, 141)));
    
    refreshrender();
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

void InputBox::setWordInput(std::string wordInput)
{
    this->wordInput = wordInput;
}

std::string InputBox::getTextInput()
{
    return this->wordInput;
}

void InputBox::Add(int keyboardType)
{
    this->wordInput += (char) keyboardType;
}

void InputBox::Del()
{
    if (this->wordInput.size() > 0) {
        this->wordInput.pop_back();
    }
}

void InputBox::update(sf::Vector2f mousePos, int mouseType, int keyboardType)
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
            exit(2);
    }
    this->active = (this->status == 3);

    const static int KBD_NONE = 0;
    const static int KBD_BACKSPACE = 8;
    const static int KBD_NEWLINE = 10;
    const static int KBD_ENTER = 13;
    const static int KBD_DEL = 127;

    if (this->active == true) {
        if (keyboardType == KBD_BACKSPACE) 
            this->Del();
        else if (keyboardType == KBD_NONE || keyboardType == KBD_NEWLINE || keyboardType == KBD_ENTER) 
            ; // do nothing
        else if ('0' <= keyboardType && keyboardType <= '9') 
            this->Add(keyboardType);
        else 
            this->Add(keyboardType);
    }
}

void InputBox::refreshrender()
{
    this->shape.setPosition(sf::Vector2f(this->x, this->y));
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);

    this->text.setFont(*this->font);
    this->text.setString(this->word + this->wordInput);

    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->x + 10,
        this->y + this->height / 2.0 - this->text.getGlobalBounds().height / 2.f - 2
    );
    
    this->listColor[this->status].Coloring(shape, text);
}

void InputBox::render(sf::RenderTarget* target) {
    if (this->view == false) return;
    refreshrender();
    target->draw(this->shape);
    target->draw(this->text);
}
