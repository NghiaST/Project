#ifndef __arrow_hpp__
#define __arrow_hpp__
#include <SFML/Graphics.hpp>

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

    int status = 0; // 0, 1, 2 : color normal, create from start to end, move arrow
                    // 3, 4, 5 : color from start to end, remove from end to start, nothing
public:
    void setStatus(int status);
    void setTime(double time);
    void setFullTime(double fulltime);
    void setStatusTime(int status, double time);

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
    void renderStatusTime(sf::RenderWindow* window, int statuss, double time);
};

#endif