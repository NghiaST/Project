#ifndef __graphics_hpp__
#define __graphics_hpp__
#include <SFML/Graphics.hpp>
#include <cstring>
#include "statusbox.hpp"
struct ViewSquareNode : StatusBox {
private:
    sf::Vector2f coord;
    int length = 10;
    std::string str;
    sf::Color idleColor;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font* font;

public:
    void initialize(sf::Font* font, int x, int y, int length, std::string str);
    void setup();
    void render(sf::RenderWindow* window);
};

#endif
/*
#ifndef __squarenode_h__
#define __squarenode_h__

#include <SFML/Graphics.hpp>

struct Node {
private:
    int status; // -1, 0, 1, 2, 3, 4: prepare to be deleted, none, hover, active, run, run2
    bool view;

    // position
    int x, y;

    // shape
    int radius;
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
    sf::CircleShape shape;
    sf::Text text;
    sf::Text textOut;
public:
    Node(int x, int y, int radius, sf::Font* font, std::string textIn, sf::Color idleColor, sf::Color runColor, sf::Color runColor2);
    ~Node();

    // get Private
    void setStatus(int status);
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    void setWordIn(std::string textIn);
    void setWordOut(std::string textOut);
    void setIDLEFillColor(sf::Color idleColor); // x
    void setIDLETextInColor(sf::Color idleOutlineColor); // x
    
    int getX();
    int getY();
    int getStatus();

    //Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    //void update(sf::Vector2f mousePos);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif*/