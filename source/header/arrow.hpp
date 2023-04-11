#ifndef __arrow_hpp__
#define __arrow_hpp__
#include <SFML/Graphics.hpp>
const int AR_NOPE = -1, AR_NORMAL = 0, AR_CREATE = 1, AR_MOVE = 2, AR_COLOR_TO = 3, AR_DEL = 4, AR_ACTIVE = 5, AR_ACTIVEMOVE = 6;

struct Arrow {
protected:
    double fulltime = 1;
    double time = 0;
    sf::Color defaultColor = sf::Color::Black;
    sf::Color activeColor = sf::Color(255, 165, 0);
    int radius_triangle = 6;
    int thickness = 2;
    
    sf::Vector2f startPoint, endPoint;
    sf::Vector2f nextStartPoint, nextEndPoint;

    int statusAnimation = 0; // -1, 0, 1: do nothing, color normal, create from start to end
                    // 2, 3, 4, 5 :, move arrow, color from start to end, remove from end to start, color running
public:
    void setStatusAnimation(int statusAnimation);
    void setTime(double time);
    void setFullTime(double fulltime);
    void setStatusAnimationTime(int statusAnimation, double time);

    void setStartPoint(sf::Vector2f startPoint);
    void setEndPoint(sf::Vector2f endPoint);
    void setNextStartPoint(sf::Vector2f nextStartPoint);
    void setNextEndPoint(sf::Vector2f nextEndPoint);
    void setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint);
    void setEndPoint(sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    void setAllPoint(sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    
    sf::Vector2f getPresentStartPoint();
    sf::Vector2f getPresentStartPoint(int time);
    sf::Vector2f getPresentEndPoint();
    sf::Vector2f getPresentEndPoint(int time);
};

struct ArrowNode : Arrow {
private:
    int radiusNode;
public:
    ArrowNode(int diameterNode);
    ArrowNode(int diameterNode, sf::Vector2f startPoint, sf::Vector2f endPoint);

    void render(sf::RenderWindow* window);
    void renderTime(sf::RenderWindow* window, double time);
    void renderStatusAnimationTime(sf::RenderWindow* window, int statusAnimations, double time);
};

#endif