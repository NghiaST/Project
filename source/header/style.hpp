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
    Themes* theme;
    THEME_TYPE typetheme;
    std::vector<ElementColor> listColor = std::vector<ElementColor>(5, ElementColor());
    // idle - hover - active - run - run2
    sf::Color textOutColor; // +
    
    // texture
    sf::Text text;
public :
    // Style(int x, int y, int sizeText, std::string word, sf::Font* font, Themes* theme);
    Style(int x, int y, sf::Font* font, std::string word, int sizeText, std::vector<ElementColor> listColor);
    Style(int x, int y, sf::Font* font, std::string word, int sizeText, ElementColor idleColor, ElementColor hoverColor, ElementColor activeColor, ElementColor runColor, ElementColor runColor2);
    ~Style();

    // set Private
    void setStatus(int status);
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    void setXY(sf::Vector2f coord);
    void setView(bool view);
    void setWord(std::string word);
    void setWordOut(std::string wordOut);
    void SetFillColor(int id, sf::Color FillColor);
    void SetTextColor(int id, sf::Color TextColor);
    void SetOutlineColor(int id, sf::Color OutlineColor);
    void SetColor(int id, ElementColor Color);
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