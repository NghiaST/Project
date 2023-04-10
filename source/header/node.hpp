#ifndef __node_hpp__
#define __node_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "triplecolor.hpp"
#include "style.hpp"

struct Node : Style {
public :
    Node(int x, int y, sf::Font* font, std::string word, int sizeText, std::vector<TripleColor> listColor);
    Node(int x, int y, sf::Font* font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    ~Node();
    
    // Functions
    int updateNode(sf::Vector2f mousePos, int mouseType, int keyboardType, bool isMouseInside);
};

struct CircleNode : Node {
private:
    int radius;
    sf::CircleShape shape;
public:
    CircleNode(int x, int y, int radius, sf::Font* font, std::string word, int sizeText, std::vector<TripleColor> Color);
    CircleNode(int x, int y, int radius, sf::Font* font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    ~CircleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderWindow* window);
};

struct RectangleNode : Node {
private:
    int width, height;
    sf::RectangleShape shape;
public:
    RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string word, int sizeText, std::vector<TripleColor> listColor);
    RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2);
    ~RectangleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderWindow* window);
};

#endif