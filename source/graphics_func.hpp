#ifndef __graphics_hpp__
#define __graphics_hpp__
#include <SFML/Graphics.hpp>

struct ViewSquareNode {
    sf::Vector2f coord;
    int length = 10;
    char* str;
    sf::Color Vcolor;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font open_font;

    ViewSquareNode(int _x = 0, int _y = 0, int _l = 10, char* _str = "") {
        coord = sf::Vector2f(_x, _y);
        length = _l;
        str = _str + '\0';
        Vcolor = sf::Color::Black;
        setup();
    }
    //ViewSquareNode(int _x = 0, int _y = 0, int _l = 0, char* _str = "");
    void initialize(int _x, int _y, int _l, char* _str);
    void setup();
    void print(sf::RenderWindow* window);
    void print(sf::RenderWindow& window);
};

struct ViewNode {
    sf::Vector2f coord;
    int radius = 10;
    sf::Color Vcolor;
    sf::CircleShape shape;
    ViewNode(int _x, int _y, int _r);
    void setup();
};

#endif