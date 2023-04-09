#ifndef __inputbox_hpp__
#define __inputbox_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "node.hpp"

struct InputBox : Node {
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

    void Add(int keyboardType);
    void Del();
    void update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif