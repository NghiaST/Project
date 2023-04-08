#ifndef __CircleNode_hpp__
#define __CircleNode_hpp__

#include <SFML/Graphics.hpp>
#include "node.hpp"

struct CircleNode : Node {
private:
    int radius;
    sf::CircleShape shape;
public:
    CircleNode(int x, int y, int radius, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
    ~CircleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

struct RectangleNode : Node {
private:
    int width, height;
    sf::RectangleShape shape;
public:
    RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string wordIn, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2);
    ~RectangleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderTarget* target);
};

#endif