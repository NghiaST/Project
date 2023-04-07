#ifndef __statusshape_hpp__
#define __statusshape_hpp__
#include <SFML/Graphics.hpp>
struct StatusShape {
protected:
    enum rectangle_states{SHAPE_IDLE = 0, SHAPE_HOVER, SHAPE_ACTIVE, SHAPE_HOLD};
    rectangle_states shapeState;
    bool canEnable; // check if mouse to be pressed inside or outside the button

public:
    void updateStatus(sf::Vector2f mousePos, int mouseType, bool isMouseWithin);
    // mouseType 0, 1, 2 -> NONE, LEFTCLICK, RIGHTCLICK
};
/*
struct ColorShapex4 {
protected:
    sf::Color 
}


template <typename sfShape>
struct Shape : StatusShape {
protected:
    sfShape Shape;
public:
};*/

#endif