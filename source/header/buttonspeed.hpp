#ifndef __buttonspeed_hpp__
#define __buttonspeed_hpp__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include "button.hpp"
#include "inputbox.hpp"
#include "settings.hpp"
#include "mouseKey.hpp"
struct ButtonSpeed {
private :
    sf::RenderWindow* window;
    Themes* theme;
    sf::Font* font;
    double* speed;
    std::vector<Button> listBtn;
public :
    ButtonSpeed(sf::RenderWindow* window, Themes* theme, sf::Font* font, double* speed);
    ~ButtonSpeed();
    sf::Vector2i update(MOUSE mouseType, KEYBOARD keyboardType, sf::Vector2f mousePosView);
    void refreshrender();
    void render();
};

#endif