#ifndef __node_hpp__
#define __node_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "triplecolor.hpp"

struct Node {
protected :
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
    std::vector<TripleColor> listColor = std::vector<TripleColor>(5, TripleColor());
    // idle - hover - active - run - run2
    sf::Color textOutColor; // +
    
    // texture
    sf::Text text;
public :
    Node() {}
    Node(int x, int y, sf::Font* font, std::string wordIn, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    ~Node();

    // set Private
    void setStatus(int status);
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    void setWord(std::string word);
    void setWordOut(std::string wordOut);
    void SetFillColor(int id, sf::Color FillColor);
    void SetTextColor(int id, sf::Color TextColor);
    void SetOutlineColor(int id, sf::Color OutlineColor);
    void SetColor(int id, TripleColor Color);
    
    // get Private
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
    CircleNode(int x, int y, int radius, sf::Font* font, std::string wordIn, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    // CircleNode(int x, int y, int radius, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
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
    RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    // RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
    ~RectangleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif