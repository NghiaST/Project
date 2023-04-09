#ifndef __button_hpp__
#define __button_hpp__
#include <SFML/Graphics.hpp>
#include "node.hpp"

struct Button : Node {
private:
    bool keepActive;

    int width, height;
    sf::RectangleShape shape;

public:
    Button() {}
    Button(int x, int y, int width, int height, sf::Font* font, bool view, bool keepActive, std::string word, int sizeText, 
        TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    ~Button();

    //Accessors
    const bool isPressed() const;

    //Functions
    void update(sf::Vector2f mousePos, int mouseType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif