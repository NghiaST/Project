#ifndef __graphics_hpp__
#define __graphics_hpp__
#include <SFML/Graphics.hpp>
#include <cstring>
#include "statusshape.hpp"
struct ViewSquareNode : StatusShape {
    sf::Vector2f coord;
    int length = 10;
    std::string str;
    sf::Color idleColor;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font* font;

    // ViewSquareNode();
    /*ViewSquareNode(int x = 0, int y = 0, int length = 10, std::string str = "") {
        std::cout << "Create\n";
        coord = sf::Vector2f(x, y);
        this->length = length;
        this->str = str;
        idleColor = sf::Color::Black;
        
        font = new sf::Font;
        if (!this->font->loadFromFile("dat/roboto/Roboto-Black.ttf")) {
            std::cout << "Error Load Font\n";
        }
        else {
            std::cout << "WW\n";
        }
        setup();
    }*/
    void initialize(sf::Font* font, int x, int y, int length, std::string str);
    void setup();
    void print(sf::RenderWindow* window);
    void print(sf::RenderWindow& window);
};

struct ViewNode {
    sf::Vector2f coord;
    int radius = 10;
    sf::Color Vcolor;
    sf::CircleShape shape;
    ViewNode(int x, int y, int radius);
    void setup();
};

#endif