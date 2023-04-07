#include <SFML/Graphics.hpp>
#include <iostream>
#include "graphics_func.hpp"
#include "struct_support.hpp"

void ViewSquareNode::initialize(sf::Font* font, int x, int y, int length, std::string str) 
{
    coord = sf::Vector2f(x, y);
    idleColor = sf::Color::Black;
    this->length = length;
    this->str = str;
    this->font = font;
    setup();
}
void ViewSquareNode::setup() 
{
    // square
    shape.setSize(sf::Vector2f(length, length));
    shape.setPosition(coord);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    // shape.setOutlineColor(sf::Color(0, 0, 0));
    
    text.setFont(*this->font);
    text.setString(str);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Red);
    settextrectangle(text, coord, sf::Vector2f(length, length));
    // text.setStyle(sf::Text::Italic);
    
// cout << "DEBUG 2\n";
}
void ViewSquareNode::print(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void ViewSquareNode::print(sf::RenderWindow *window)
{
    window->draw(shape);
    window->draw(text);
}

ViewNode::ViewNode(int x = 0, int y = 0, int radius = 10) {
    coord.x = x;
    coord.y = y;
    this->radius = radius;
}
void ViewNode::setup() {
    shape = sf::CircleShape(radius);
    shape.setFillColor(Vcolor);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color(0, 0, 0));
}