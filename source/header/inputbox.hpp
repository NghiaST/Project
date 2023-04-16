#ifndef __inputbox_hpp__
#define __inputbox_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "style.hpp"

struct InputBox : Style {
private:
    bool active;

    // shape
    int width, height;

    // string
    std::string wordInput;

    // render
    sf::RectangleShape shape;

public:
    InputBox(int x, int y, int width, int height, sf::Font* font, bool view, std::string textConst);
    ~InputBox();
    
    void setView(bool view);
    void changeView();
    void setWordInput(std::string wordInput);
    std::string getTextInput();

    void Add_Character(int keyboardType);
    void Del_Character();
    void update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderWindow* window);
};

#endif