#ifndef __style_hpp__
#define __style_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "triplecolor.hpp"

struct Style {
protected :
    /**
     *  Note : "// +" means this data is defaulted 
     * */

    int status; // + // 0, 1, 2, 3, 4: none, hover, active, run, run2
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
//    TripleColor idleColor, hoverColor, activeColor, runColor, runColor2;

    // color
    std::vector<TripleColor> listColor = std::vector<TripleColor>(5, TripleColor());
    // idle - hover - active - run - run2
    sf::Color textOutColor; // +
    
    // texture
    sf::Text text;
public :
    Style(int x, int y, sf::Font* font, std::string word, int sizeText, std::vector<TripleColor> listColor);
    Style(int x, int y, sf::Font* font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    ~Style();

    // set Private
    void setStatus(int status);
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    void setView(bool view);
    void setWord(std::string word);
    void setWordOut(std::string wordOut);
    void SetFillColor(int id, sf::Color FillColor);
    void SetTextColor(int id, sf::Color TextColor);
    void SetOutlineColor(int id, sf::Color OutlineColor);
    void SetColor(int id, TripleColor Color);
    void swapView();
    
    // get Private
    int getStatus();
    int getX();
    int getY();
    sf::Vector2f getXY();
    bool getView();
};

#endif