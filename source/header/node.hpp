#ifndef __node_hpp__
#define __node_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ElementColor.hpp"
#include "style.hpp"
#include "support_function.hpp"
const int NOD_NOPE = -1, NOD_STABLE = 0, NOD_RECOLOR = 1, NOD_APPEAR = 2, NOD_DEL = 3, NOD_MOVE = 4;   /// manipulate visual
const int NOD_NORMAL = 5;   /// -> NOD_STABLE
const int NOD_SHOW = 6, NOD_SOLVE = 7, NOD_UNSHOW = 8, NOD_ACTIVE = 9;  /// NOD_RECOLOR, manipulate: stable -> change color
const int NOD_SKIP = 10;

struct Node : Style {
    bool running = false;
public :
    Node(int x, int y, sf::Font* font, std::string word, int sizeText, std::vector<ElementColor> listColor);
    Node(int x, int y, sf::Font* font, std::string word, int sizeText, ElementColor idleColor, ElementColor hoverColor, ElementColor activeColor, ElementColor runColor, ElementColor runColor2);
    ~Node();
    
    // Functions
    int updateNode(sf::Vector2f mousePos, int mouseType, int keyboardType, bool isMouseInside);
    bool getRunning();
};

struct CircleNode : Node {
private:
    int radius;
    sf::CircleShape shape;

    // visualization
    // bool running = false;
    double ratioColor;
    int statusAnimation; /// -1, 0, 1, 2, 3, 4 : no draw, common, move, appear node, recolor node, disappear node
    double fulltime = 1;
    double time;
    sf::Vector2f startPoint, endPoint;

public:
    CircleNode(int x, int y, int radius, sf::Font* font, std::string word, int sizeText, std::vector<ElementColor> Color);
    CircleNode(int x, int y, int radius, sf::Font* font, std::string word, int sizeText, ElementColor idleColor, ElementColor hoverColor, ElementColor activeColor, ElementColor runColor, ElementColor runColor2);
    ~CircleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderWindow* window);

    // visualization
    void prepareAnimation(sf::Vector2f startPoint, sf::Vector2f endPoint, int statusAnimation, int status);
    void stopAnimation();
    void updateAnimation_Moving(double time);
    void updateAnimation(double time);
    void renderAnimation(sf::RenderWindow* window, int statusAnimation, double time);
};

struct RectangleNode : Node {
private:
    int width, height;
    sf::RectangleShape shape;
public:
    RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string word, int sizeText, std::vector<ElementColor> listColor);
    RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string word, int sizeText, ElementColor idleColor, ElementColor hoverColor, ElementColor activeColor, ElementColor runColor, ElementColor runColor2);
    ~RectangleNode();

    // Functions
    int update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render(sf::RenderWindow* window);
};

#endif