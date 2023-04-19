#ifndef __style_hpp__
#define __style_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ElementColor.hpp"
#include "themes.hpp"

struct Style {
protected :
    /**
     *  Note : "// +" means this data is defaulted 
     * */

    int status; // + // 0, 1, 2, 3, 4: none, hover, active, run, run2
    bool view; // +

    // position
    sf::Vector2f coord;

    // shape
    float thickness; // +

    // font
    sf::Font* font;

    // word
    std::string word;
    std::string wordOut; // +

    // wordsize
    unsigned int sizeText; // +

    // color: idle - hover - active - running / animation
    Palette* palette;
    sf::Color textOutColor; // +

    
    
    // texture
    sf::Text text;
public :
    Style(sf::Vector2f coord, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette);
    ~Style();

    // set Private
    void setStatus(int status);
    void setX(float x);
    void setY(float y);
    void setXY(float x, float y);
    void setXY(sf::Vector2f coord);
    void setView(bool view);
    void setTextSize(unsigned int sizeText);
    void setWord(std::string word);
    void setPalette(Palette* palette);
    void swapView();
    
    // get Private
    int getStatus();
    int getX();
    int getY();
    sf::Vector2f getXY();
    bool getView();
    std::string getWord();
    std::string getWordOut();
};

#endif