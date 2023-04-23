#ifndef __node_hpp__
#define __node_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ElementColor.hpp"
#include "style.hpp"
#include "support_function.hpp"
#include "mouseKey.hpp"

const int NOD_NOPE = -1, NOD_STABLE = 0, NOD_RECOLOR = 1, NOD_APPEAR = 2, NOD_DEL = 3, NOD_MOVE = 4;   /// manipulate visual
const int NOD_NORMAL = 5;   /// -> NOD_STABLE
const int NOD_SHOW = 6, NOD_SOLVE = 7, NOD_UNSHOW = 8, NOD_ACTIVE = 9;  /// NOD_RECOLOR, manipulate: stable -> change color
const int NOD_SKIP = 10;

struct Node : Style {
    bool running = false;
    
    // visualization
    double fulltime = 1;
    double time;
    double ratioColor;
    int statusAnimation; /// -1, 0, 1, 2, 3, 4 : no draw, common, move, appear node, recolor node, disappear node
public :
    Node(sf::Vector2f coord, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette);
    ~Node();
    
    // Functions
    int updateNode(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType, bool isMouseInside);
    bool getRunning();
};

struct CircleNode : Node {
private:
    int radius;
    sf::CircleShape shape;
    sf::Vector2f startPoint, endPoint;  // center

public:
    CircleNode(sf::Vector2f coord, float diameter, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette);
    ~CircleNode();

    // Functions
    int update(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);
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
    RectangleNode(sf::Vector2f coord, float width, float height, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette);
    ~RectangleNode();

    // Functions
    int update(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);
    void refreshrender();
    void render(sf::RenderWindow* window);
};

#endif