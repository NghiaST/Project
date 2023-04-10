#include "style.hpp"

///--------------------------------------------------------------------
///--------------------------------Style--------------------------------

Style::Style(int x, int y, sf::Font *font, std::string word, int sizeText, std::vector<TripleColor> listColor)
{
    // Default
    this->status = 0;
    this->view = true;

    // Position
    this->x = x;
    this->y = y;

    // shape
    this->thickness = 2;

    // font
    this->font = font;

    // word
    this->word = word;
    this->wordOut = "";

    // wordsize
    this->sizeText = sizeText;
    this->sizeTextOut = 12;

    while (listColor.size() < 5) {
        listColor.push_back(TripleColor());
        std::cout << "Style::Style warning: listColor don't have enough color\n";
    }
    this->listColor = listColor;
}

Style::Style(int x, int y, sf::Font *font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2)
{
    // Default
    this->status = 0;
    this->view = true;

    // Position
    this->x = x;
    this->y = y;

    // shape
    this->thickness = 2;

    // font
    this->font = font;

    // word
    this->word = word;
    this->wordOut = "";

    // wordsize
    this->sizeText = sizeText;
    this->sizeTextOut = 12;

    // color
    this->listColor[0] = idleColor;
    this->listColor[1] = hoverColor;
    this->listColor[2] = activeColor;
    this->listColor[3] = runColor;
    this->listColor[4] = runColor2;

    // default
    this->listColor[1].changeFillColor(sf::Color::Green);
    this->listColor[2].changeFillColor(sf::Color::Yellow);

    this->listColor[0].changeTextColor(sf::Color::Red);
    this->listColor[1].changeTextColor(sf::Color::Red);
    this->listColor[2].changeTextColor(sf::Color::Red);
    this->listColor[3].changeTextColor(sf::Color::Red);
    this->listColor[4].changeTextColor(sf::Color::Red);

    this->listColor[0].changeOutlineColor(sf::Color::Black);
    this->listColor[1].changeOutlineColor(sf::Color::Black);
    this->listColor[2].changeOutlineColor(sf::Color::Black);
    this->listColor[3].changeOutlineColor(sf::Color::Black);
    this->listColor[4].changeOutlineColor(sf::Color::Black);

    this->textOutColor = sf::Color::Blue;
}

Style::~Style()
{

}

void Style::setStatus(int status)
{
    this->status = status;
}
void Style::setX(int x) 
{
    this->x = x;
}
void Style::setY(int y)
{
    this->y = y;
}
void Style::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Style::setXY(sf::Vector2f coord)
{
    this->x = coord.x;
    this->y = coord.y;
}
void Style::setView(bool view)
{
    this->view = view;
}
void Style::setWord(std::string word)
{
    this->word = word;
}
void Style::setWordOut(std::string wordOut)
{
    this->wordOut = wordOut;
}
void Style::SetFillColor(int id, sf::Color FillColor)
{
    this->listColor[id].changeFillColor(FillColor);
}
void Style::SetTextColor(int id, sf::Color TextColor)
{
    this->listColor[id].changeTextColor(TextColor);
}
void Style::SetOutlineColor(int id, sf::Color OutlineColor)
{
    this->listColor[id].changeOutlineColor(OutlineColor);
}
void Style::SetColor(int id, TripleColor Color)
{
    this->listColor[id] = Color;
}
void Style::swapView()
{
    this->view = !this->view;
}

int Style::getStatus()
{
    return this->status;
}
int Style::getX()
{
    return this->x;
}
int Style::getY()
{
    return this->y;
}
sf::Vector2f Style::getXY()
{
    return sf::Vector2f(this->x, this->y);
}
bool Style::getView()
{
    return this->view;
}