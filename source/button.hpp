#ifndef __button_h__
#define __button_h__

#include <SFML/Graphics.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_HOLD};

class Button {
private:

    short unsigned buttonState;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    
    int thickness;
    sf::Color idleOutlineColor;
    
    bool canEnable = false; // check if mouse to be pressed inside or outside the button

public:
    Button(float x, float y, float width, float height, 
        sf::Font* font, std::string str, 
        sf::Color idleColor, sf::Color hovercOlor, sf::Color activeColor);
    ~Button();

    //Accessors
    const bool isPressed() const;

    //Functions
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};

#endif