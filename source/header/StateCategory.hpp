#ifndef __StateCategory_hpp__
#define __StateCategory_hpp__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include "button.hpp"
#include "inputbox.hpp"
#include "settings.hpp"
#include "mouseKey.hpp"

struct StateCategory {
private :
    sf::RenderWindow* window;
    Themes* theme;
    sf::Font* font;
    int cntCategory;
    int cntManipulate;
    int typeCategory;
    int typeManipulate;
    int typesubManipulate;

    std::vector<Button> buttonCategory;
    std::vector<Button> buttonManipulate;
    std::vector<std::vector<Button>> buttonsubManipulate;
    std::vector<InputBox> listBox;
    std::vector<std::vector<int>> listShow;
    std::vector<Button> buttonRand;

public :
    StateCategory(sf::RenderWindow* window, Themes* theme, sf::Font* font, int typeCategory, std::vector<std::string> strCategory, std::vector<std::string> strManipulate, std::vector<std::vector<std::string>> strsubManipulate, std::vector<std::string> strInputBox, std::vector<std::vector<int>> listShow);
    ~StateCategory();

    void Clean();

    sf::Vector2i update(MOUSE mouseType, KEYBOARD keyboardType, sf::Vector2f mousePosView);
    void updateInputBox(int pos, int value);
    std::vector<std::string> getInputBox(int typeManipulate);

    void render();
};

#endif