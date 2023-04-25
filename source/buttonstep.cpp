#include "buttonstep.hpp"

ButtonStep::ButtonStep(sf::RenderWindow *window, Themes *theme, sf::Font *font, std::vector<std::vector<std::vector<std::vector<std::string>>>> listStrStep)
{
    this->window = window;
    this->theme = theme;
    this->font = font;
    this->listStrStep = listStrStep;

    sf::Vector2f coord, velocity, sizeRec;
    coord = sf::Vector2f(1000, 433);
    velocity = sf::Vector2f(0, 36);
    sizeRec = sf::Vector2f(342, 35);

    for (int i = 0; i < 7; i++)
    {
        listBtn.push_back(Button(coord, sizeRec.x, sizeRec.y, 12, 0, true, false, "", this->font, this->theme->getButtonStep()));
        coord += velocity;
    }
}

ButtonStep::~ButtonStep()
{
}

void ButtonStep::assign(int typeCategory, int typeManipulate, int typeSubManipulate)
{
    for (Button &btn : listBtn)
        btn.setWord("");
    if (typeCategory == -1) 
        return;
    for (int i = 0; i < listStrStep[typeCategory][typeManipulate][typeSubManipulate].size(); i++)
    {
        listBtn[i].setWord(listStrStep[typeCategory][typeManipulate][typeSubManipulate][i]);
    }
}

void ButtonStep::update(int typeStep)
{
    for (int i = 0; i < listBtn.size(); i++)
    {
        if (i == typeStep)
            listBtn[i].setStatus(1);
        else
            listBtn[i].setStatus(0);
    }
}

void ButtonStep::render()
{
    for (Button &btn : listBtn)
        btn.render(window);
}
