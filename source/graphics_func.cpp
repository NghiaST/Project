#include <SFML/Graphics.hpp>
#include <iostream>
#include "graphics_func.hpp"
#include "struct_support.hpp"
/*ViewSquareNode::ViewSquareNode(int _x = 0, int _y = 0, int _l = 10, char* _str = "") {
    coord = sf::Vector2f(_x, _y);
    length = _l;
    str = _str + '\0';
    Vcolor = sf::Color::Black;
    setup();
}*/
void ViewSquareNode::initialize(int _x = 0, int _y = 0, int _l = 10, char* _str = "") {
    coord = sf::Vector2f(_x, _y);
    length = _l;
    str = _str + '\0';
    Vcolor = sf::Color::Black;
    setup();
}
void ViewSquareNode::setup() {
    // square
    shape.setSize(sf::Vector2f(length, length));
    shape.setPosition(coord);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    // shape.setOutlineColor(sf::Color(0, 0, 0));

    // text
    if (!open_font.loadFromFile("./dat/roboto/Roboto-Black.ttf"))
    {
        std::cout << "ERROR";
    }
// cout << "DEBUG 1\n";
    text.setFont(open_font);
    text.setString(str);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Red);
    settextrectangle(text, coord, sf::Vector2f(length, length));
    //tt(text);
    // text.setStyle(sf::Text::Italic);
    
// cout << "DEBUG 2\n";
}
void ViewSquareNode::print(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}


ViewNode::ViewNode(int _x = 0, int _y = 0, int _r = 10) {
    coord.x = _x;
    coord.y = _y;
    radius = _r;
}
void ViewNode::setup() {
    shape = sf::CircleShape(radius);
    shape.setFillColor(Vcolor);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color(0, 0, 0));
}