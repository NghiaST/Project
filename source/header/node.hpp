#ifndef __node_hpp__
#define __node_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>

struct Node {
public:
    /**
     *  Note : "// +" means this data is defaulted 
     * */

    int status; // + // -1, 0, 1, 2, 3, 4: prepare to be deleted, none, hover, active, run, run2
    bool view; // +

    // position
    int x, y;

    // shape
    int thickness; // +

    // font
    sf::Font* font;

    // word
    std::string word;
    std::string wordOut; // +

    // wordsize
    int sizeText; // +
    int sizeTextOut; // +

    // color
    sf::Color idleFillColor;
    sf::Color hoverFillColor; // +
    sf::Color activeFillColor; // +
    sf::Color runFillColor;
    sf::Color runFillColor2;

    sf::Color idleOutlineColor; // +
    sf::Color hoverOutlineColor; // +
    sf::Color activeOutlineColor; // +
    sf::Color runOutlineColor; // +
    sf::Color runOutlineColor2; // +

    sf::Color idleTextColor; // +
    sf::Color hoverTextColor; // +
    sf::Color activeTextColor; // +
    sf::Color runTextColor; // +
    sf::Color runTextColor2; // +

    sf::Color textOutColor; // +
    
    // texture
    sf::Text text;
public:
    Node() {}
    Node(int x, int y, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
    ~Node();

    // get Private
    void setStatus(int status);
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    void setWord(std::string word);
    void setWordOut(std::string wordOut);
    void setIDLEFillColor(sf::Color idleColor);
    void setIDLETextColor(sf::Color idleOutlineColor);
    
    int getX();
    int getY();
    int getStatus();

    //Functions
    int updateNode(sf::Vector2f mousePos, int mouseType, int keyboardType, bool isMouseInside);
};

struct CircleNode : Node {
private:
    int radius;
    sf::CircleShape shape;
public:
    CircleNode(int x, int y, int radius, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
    ~CircleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

struct RectangleNode : Node {
private:
    int width, height;
    sf::RectangleShape shape;
public:
    RectangleNode() {}
    RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
    ~RectangleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif