#ifndef __button_hpp__
#define __button_hpp__
#include <SFML/Graphics.hpp>
#include "style.hpp"
#include "mouseKey.hpp"

struct Button : Style {
protected:
    bool keepActive;
    int print_type;

    int width, height;
    sf::RectangleShape shape;

public:
    Button(sf::Vector2f coord, float width, float height, float sizeText, float thickness, bool view, bool keepActive, int print_type, std::string word, sf::Font *font, Palette* palette);
    ~Button();

    //Accessors
    const bool isPressed() const;

    //Functions
    void update(sf::Vector2f mousePos, MOUSE mouseType);
    bool updateCheckClick(sf::Vector2f mousePos, MOUSE mouseType);
    virtual void refreshrender();
    virtual void render(sf::RenderWindow* window);
};

#endif