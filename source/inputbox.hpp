#ifndef __inputbox_hpp__
#define __inputbox_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "statusshape.hpp"

struct InputBox : StatusShape {
private:
    sf::RectangleShape shape;

    std::string str_const;
    std::string str;
    sf::Font* font;
    sf::Text text;
    bool active;

    sf::Color idleOutlineColor;
    sf::Color activeOutlineColor;

public:
    InputBox(float x, float y, float width, float height, sf::Font* font, std::string str_const);
    ~InputBox();
    void Add(int unicode);
    void Del();
    void update(sf::Vector2f mousePos, int unicode);
    void render(sf::RenderTarget* target);

    std::string getString();
};

#endif