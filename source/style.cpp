#include "style.hpp"

///--------------------------------------------------------------------
///--------------------------------Style--------------------------------

Style::Style(sf::Vector2f coord, unsigned int sizeText, float thickness, std::string word, sf::Font *font, Palette* palette)
{
    // Default
    this->status = 0;
    this->view = true;

    // Position
    this->coord = coord;

    // shape
    this->thickness = thickness;

    // font
    this->font = font;

    // word
    this->word = word;

    // wordsize
    this->sizeText = sizeText;
    this->palette = palette;
}

Style::~Style()
{

}

void Style::setStatus(int status)
{
    this->status = status;
}
void Style::setX(float x) 
{
    this->coord.x = x;
}
void Style::setY(float y)
{
    this->coord.y = y;
}
void Style::setXY(float x, float y)
{
    this->coord = sf::Vector2f(x, y);
}
void Style::setXY(sf::Vector2f coord)
{
    this->coord = coord;
}
void Style::setView(bool view)
{
    this->view = view;
}
void Style::setWord(std::string word)
{
    this->word = word;
}
void Style::setPalette(Palette* palette)
{
    this->palette = palette;
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
    return this->coord.x;
}
int Style::getY()
{
    return this->coord.y;
}
sf::Vector2f Style::getXY()
{
    return this->coord;
}
bool Style::getView()
{
    return this->view;
}
std::string Style::getWord()
{
    return this->word;
}
std::string Style::getWordOut()
{
    return this->wordOut;
}