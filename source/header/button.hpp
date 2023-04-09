#ifndef __button_h__
#define __button_h__
#include <SFML/Graphics.hpp>

struct Button {
private:
    int status; // 0, 1, 2, 3 : none, hover, active, run, active + active
    bool view;
    bool keepActive;

    // position
    // int x, y;

    // shape
    // int width, height;
    int thickness;

    // font
    sf::Font* font;

    // word
    // std::string word;
    // int sizeText;

    // color
    sf::Color idleFillColor;
    sf::Color hoverFillColor;
    sf::Color activeFillColor;
    sf::Color runFillColor;
    
    sf::Color idleOutlineColor;
    sf::Color hoverOutlineColor;
    sf::Color activeOutlineColor;
    sf::Color runOutlineColor;

    sf::Color textColor;

    // texture
    sf::RectangleShape shape;
    sf::Text text;
public:
    Button(float x, float y, float width, float height, 
        sf::Font* font, bool view, bool keepActive, std::string str, int strsize,
        sf::Color idleFillColor, sf::Color hoverFillColor, sf::Color activeFillColor, sf::Color runFillColor);
    ~Button();

    //Accessors
    const bool isPressed() const;
    void setView(bool view);
    void changeView(); // 0 <-> 1
    void setStatus(int x);

    bool getView();

    //Functions
    void update(sf::Vector2f mousePos, int mouseType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif