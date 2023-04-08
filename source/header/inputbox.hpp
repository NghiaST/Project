#ifndef __inputbox_hpp__
#define __inputbox_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "statusbox.hpp"

struct InputBox : StatusBox {
private:
    bool active;
    int status;
    bool view;

    // string
    std::string str_const;
    std::string str;

    // font
    sf::Font* font;

    // text
    int strsize;

    // shape
    int thickness;

    // color
    sf::Color defaultTextColor;
    sf::Color defaultFillColor;
    sf::Color idleOutlineColor;
    sf::Color activeOutlineColor;

    // render
    sf::Text text;
    sf::RectangleShape shape;

public:
    InputBox(float x, float y, float width, float height, sf::Font* font, bool view, std::string str_const);
    ~InputBox();
    
    void setView(bool view);
    void changeView();
    std::string getString();

    void Add(int keyboardType);
    void Del();
    void update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif