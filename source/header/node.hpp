#ifndef __node_hpp__
#define __node_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ElementColor.hpp"
#include "style.hpp"
#include "support_function.hpp"
#include "mouseKey.hpp"

enum NODE_ANIMATION{NOD_NOPE = -1, NOD_STABLE, NOD_RECOLOR, NOD_APPEAR, NOD_DEL, NOD_MOVE,   /// manipulate visual
                    NOD_NORMAL,   /// -> NOD_STABLE
                    NOD_SHOW, NOD_SOLVE, NOD_UNSHOW, NOD_ACTIVE,  /// NOD_RECOLOR, manipulate: stable -> change color
                    NOD_SKIP
                    };

struct Node : Style {
    bool running = false;
    
    // visualization
    double fulltime = 1;
    double time;
    double ratioColor;
    NODE_ANIMATION statusAnimation; /// -1, 0, 1, 2, 3, 4 : no draw, common, move, appear node, recolor node, disappear node
    int preStatus;
    sf::Vector2f startPoint, endPoint;

    // shape
    int radius;
    int halflength;
    sf::CircleShape shape;

public :
    Node(sf::Vector2f coord, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette);
    ~Node();

    // other
    virtual bool isMouseInside(sf::Vector2f mousePos) = 0;
    bool getRunning();

    // Functions
    int updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);

    // visualization
    void startAnimation(sf::Vector2f startPoint, sf::Vector2f endPoint, NODE_ANIMATION statusAnimation, int preStatus, int status);
    void stopAnimation();
    // void updateAnimation_Coloring(double ratio);
    void updateAnimation_Moving(double ratio);
    void updateAnimation(double time);
    void renderAnimation(sf::RenderWindow* window, NODE_ANIMATION statusAnimation, double time);

    // print
    void refreshrender();
    void render(sf::RenderWindow* window);
};

struct CircleNode : Node {
public:
    CircleNode(sf::Vector2f coord, float diameter, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette);
    ~CircleNode();

    // other
    bool isMouseInside(sf::Vector2f mousePos) override;
};

struct RectangleNode : Node {
public:
    RectangleNode(sf::Vector2f coord, float length, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette);
    ~RectangleNode();

    // override
    bool isMouseInside(sf::Vector2f mousePos) override;
};

#endif