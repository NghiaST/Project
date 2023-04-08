#ifndef __node_hpp__
#define __node_hpp__
#include <SFML/Graphics.hpp>

struct Node {
public:
    int status; // -1, 0, 1, 2, 3, 4: prepare to be deleted, none, hover, active, run, run2
    bool view;

    // position
    int x, y;

    // shape
    int thickness;

    // font
    sf::Font* font;

    // word
    std::string wordIn; // = value
    std::string wordOut;

    // wordsize
    int sizeTextIn;
    int sizeTextOut;

    // color
    sf::Color idleFillColor;
    sf::Color hoverFillColor;
    sf::Color activeFillColor;
    sf::Color runFillColor;
    sf::Color runFillColor2;

    sf::Color idleOutlineColor;
    sf::Color hoverOutlineColor;
    sf::Color activeOutlineColor;
    sf::Color runOutlineColor;
    sf::Color runOutlineColor2;

    sf::Color textInColor;
    sf::Color textOutColor;
    
    // texture
    sf::Text textIn;
    sf::Text textOut;
public:
    Node() {}
    Node(int x, int y, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
    ~Node();

    // get Private
    void setStatus(int status);
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    void setWordIn(std::string textIn);
    void setWordOut(std::string textOut);
    void setIDLEFillColor(sf::Color idleColor);
    void setIDLETextInColor(sf::Color idleOutlineColor);
    
    int getX();
    int getY();
    int getStatus();

    //Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType, bool isMouseInside);
};

#endif