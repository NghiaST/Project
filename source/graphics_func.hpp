#ifndef __graphics_hpp__
#define __graphics_hpp__
#include <SFML/Graphics.hpp>
#include <cstring>
struct ViewSquareNode {
    sf::Vector2f coord;
    int length = 10;
    std::string str;
    sf::Color idleColor;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font open_font;

    //ViewSquareNode() {}
    ViewSquareNode(int x = 0, int y = 0, int length = 10, std::string str = "") {
        coord = sf::Vector2f(x, y);
        this->length = length;
        this->str = str;
        idleColor = sf::Color::Black;
        setup();
    }
    void initialize(sf::Font& font, int x, int y, int length, std::string str);
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