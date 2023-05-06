#include "buttonspeed.hpp"

ButtonSpeed::ButtonSpeed(sf::RenderWindow *window, Themes *theme, sf::Font *font, double *speed)
{
    this->window = window;
    this->theme = theme;
    this->font = font;
    this->speed = speed;
    std::vector<std::string> strSpeed = {"Speed", "<", "", ">"};

    std::vector<int> listWidth  = {74, 20, 40, 20};
    int height = 35;
    std::vector<int> Posx = {280};
    int posy = 650;

    for(int i = 0; i < 3; i++)
        Posx.push_back(Posx.back() + listWidth[i] + 2);

    for(int i = 0; i < 4; i++)
    {
        if (i & 1)
            listBtn.push_back(Button(sf::Vector2f(Posx[i], posy), listWidth[i], height, 12, 2, true, false, 0, strSpeed[i], font, theme->getButtonDS()));
        else
            listBtn.push_back(Button(sf::Vector2f(Posx[i], posy), listWidth[i], height, 12, 2, true, false, 0, strSpeed[i], font, theme->getButtonStep()));
    }
}

ButtonSpeed::~ButtonSpeed()
{
}

sf::Vector2i ButtonSpeed::update(MOUSE mouseType, KEYBOARD keyboardType, sf::Vector2f mousePosView)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < 4; i++)
    {
        if (listBtn[i].updateCheckClick(mousePosView, mouseType) && (i == 1 || i == 3))
            ret = sf::Vector2i(400, i == 3);
    }
    return ret;
}

void ButtonSpeed::refreshrender()
{
    std::string str = std::to_string(*speed);
    while (str.back() == '0' || str.back() == '.') str.pop_back();
    listBtn[2].setWord(str);
}

void ButtonSpeed::render()
{
    refreshrender();
    for(Button& btn : listBtn)
        btn.render(window);
}