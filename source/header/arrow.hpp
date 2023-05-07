#ifndef __arrow_hpp__
#define __arrow_hpp__
#include <SFML/Graphics.hpp>
#include "themes.hpp"

const double PI = 3.141592653589793238462643383279502;

enum ARROW_ANIMATION{AR_NOPE = -1, AR_NORMAL, AR_ACTIVE, AR_CREATE, AR_COLOR_TO, AR_DEL, AR_SKIP, AR_MOVE, AR_COLOR_REV, AR_COLOR};
enum ARROW_TYPE{ARR_1 = 0, ARR_2, ARR_LOOP};

struct ArrowShape {
private:
    const double radius_triangle = 6;
    const double thickness = 2;
    double length, ratio;
    sf::RectangleShape line;
    sf::ConvexShape triangle;
public:
    ArrowShape(sf::Vector2f Point1, sf::Vector2f Point2, bool isTriangle);
    ArrowShape(sf::Vector2f Point1, sf::Vector2f Point2);
    ArrowShape& operator = (const ArrowShape& other);
    void setRatio(double ratio);
    void setColor(Palette* palette, int status);
    int getLength();
    void render(sf::RenderWindow* window);
};

struct PolyArrow {
private:
    double length, ratio;
    std::vector<ArrowShape> listArrowShape;
public:
    PolyArrow(std::vector<sf::Vector2f> junction);
    void setRatio(double ratio);
    void setColor(Palette* palette, int status);
    void render(sf::RenderWindow* window);
};

struct Arrow_Control {
protected:
    double fulltime = 1;
    double time = 0;

    Palette *palette;
    int radius_triangle = 6;
    int thickness = 2;
    
    sf::Vector2f startPoint, endPoint;
    sf::Vector2f nextStartPoint, nextEndPoint;

    ARROW_TYPE arrow_type = ARR_1;
    ARROW_ANIMATION statusAnimation = AR_NORMAL;
public:
    void setArrowType(ARROW_TYPE arrow_type);
    void setStatusAnimation(ARROW_ANIMATION statusAnimation);
    void setTime(double time);
    void setFullTime(double fulltime);
    void setStatusAnimationTime(ARROW_ANIMATION statusAnimation, double time);

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

struct ArrowNode : Arrow_Control {
private:
    int radiusNode;
public:
    ArrowNode(int diameterNode, Palette* palette);

    void render_Arr1(sf::RenderWindow* window);
    void render_Arr2(sf::RenderWindow* window);
    void render_ArrLoop(sf::RenderWindow* window);
    void render(sf::RenderWindow* window);
    void renderTime(sf::RenderWindow* window, double time);
    void renderStatusAnimationTime(sf::RenderWindow* window, ARROW_ANIMATION statusAnimations, double time);
};

#endif