#ifndef __arrow_hpp__
#define __arrow_hpp__
#include <SFML/Graphics.hpp>

struct Arrow {
protected:
    sf::Color defaultColor = sf::Color::Black;
    sf::Color activeColor = sf::Color(255, 165, 0);
    // sf::ConvexShape triangle;

    sf::Vector2f startPoint, endPoint;
    int radius_triangle = 6;
    int thickness = 2;
public:
    void setStartPoint(sf::Vector2f startPoint);
    void setEndPoint(sf::Vector2f endPoint);
    void setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint);
    void render(sf::RenderWindow* window);
};

struct ArrowNode : Arrow {
private:
    int radiusNode;
public:
    ArrowNode(int sizeNode);
    ArrowNode(int sizeNode, sf::Vector2f startNode, sf::Vector2f endNode);
    void setNode(sf::Vector2f startNode, sf::Vector2f endNode);
};

#endif