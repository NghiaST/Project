#ifndef __arrow_hpp__
#define __arrow_hpp__
#include <SFML/Graphics.hpp>

struct Arrow {
protected:
    sf::Color defaultColor = sf::Color::Black;
    sf::Color activeColor = sf::Color(255, 165, 0);
    // sf::ConvexShape triangle;

    sf::Vector2f startPoint, endPoint, nextPoint;
    int radius_triangle = 6;
    int thickness = 2;

    int status = 0; // 0, 1, 2 : color normal, create from start to end, move arrow
                    // 3, 4 : color from start to end, remove from end to start
    double fulltime = 1;
public:
    void setStatus(int status);
    void setFullTime(double fulltime);

    void setStartPoint(sf::Vector2f startPoint);
    void setEndPoint(sf::Vector2f endPoint);
    void setNextPoint(sf::Vector2f nextPoint);
    void setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint);
    void setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextPoint);
    void render(sf::RenderWindow* window);
    void renderTime(sf::RenderWindow* window, double time);

    void renderStatusTime(sf::RenderWindow* window, int statuss, double time);
};

struct ArrowNode : Arrow {
private:
    int radiusNode;
public:
    ArrowNode(int sizeNode);
    ArrowNode(int sizeNode, sf::Vector2f startNode, sf::Vector2f endNode);
    void setNode(sf::Vector2f startNode, sf::Vector2f endNode);
    void setNextNode(sf::Vector2f nextNode);
};

#endif