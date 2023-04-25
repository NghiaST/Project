#ifndef __buttonstep_hpp__
#define __buttonstep_hpp__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include "button.hpp"
#include "inputbox.hpp"
#include "settings.hpp"
#include "mouseKey.hpp"
struct ButtonStep {
private :
    sf::RenderWindow* window;
    Themes* theme;
    sf::Font* font;
    std::vector<Button> listBtn;
    std::vector<std::vector<std::vector<std::vector<std::string>>>> listStrStep;
public :
    ButtonStep(sf::RenderWindow* window, Themes* theme, sf::Font* font, std::vector<std::vector<std::vector<std::vector<std::string>>>> strBtnStep);
    ~ButtonStep();
    void assign(int typeCategory, int typeManipulate, int typeSubManipulate);
    void update(int typeStep);
    void render();
};

#endif