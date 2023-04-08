#ifndef __statusbox_hpp__
#define __statusbox_hpp__
#include <SFML/Graphics.hpp>
struct StatusBox {
protected:
    enum rectangle_states{SHAPE_IDLE = 0, SHAPE_HOVER, SHAPE_ACTIVE, SHAPE_HOLD};
    rectangle_states shapeState;
    bool canEnable; // check if mouse to be pressed inside or outside the button

public:
    void updateStatus(sf::Vector2f mousePos, int mouseType, bool isMouseWithin);
    // mouseType 0, 1, 2 -> NONE, LEFTCLICK, RIGHTCLICK
};


#endif