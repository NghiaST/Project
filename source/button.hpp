#ifndef __button_h__
#define __button_h__

#include <SFML/Graphics.hpp>
#include "statusshape.hpp"

struct Button : private StatusShape  {
private:
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;
    int thickness;
    bool active;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    sf::Color runningColor;
    
    sf::Color idleOutlineColor;
    sf::Color hoverOutlineColor;
    sf::Color activeOutlineColor;
    sf::Color runningOutlineColor;

public:
    Button(float x, float y, float width, float height, 
        sf::Font* font, std::string str, int strsize,
        sf::Color idleColor, sf::Color hovercOlor, sf::Color activeColor, sf::Color runningColor);
    ~Button();

    //Accessors
    const bool isPressed() const;

    //Functions
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};

#endif