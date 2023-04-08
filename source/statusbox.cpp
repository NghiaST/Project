#include "statusbox.hpp"

void StatusBox::updateStatus(sf::Vector2f mousePos, int mouseType, bool isMouseWithin)
{
    //Hold - 3
    if (this->canEnable == true && mouseType == 1 && (this->shapeState == SHAPE_ACTIVE || this->shapeState == SHAPE_HOLD))
    {
        this->shapeState = SHAPE_HOLD;
    }
    //Pressed - 2
    else if (this->canEnable == true && isMouseWithin == true && mouseType == 1)
    {
        this->shapeState = SHAPE_ACTIVE;
    }

    //Hover - 1
    else if (canEnable == false && isMouseWithin == true && mouseType == 1)
    {
        this->canEnable = false;
        this->shapeState = SHAPE_HOVER;
    }
    else if (isMouseWithin == true) 
    {
        this->canEnable = true;
        this->shapeState = SHAPE_HOVER;
    }
    //Idle - 0
    else 
    {
        this->canEnable = false;
        this->shapeState = SHAPE_IDLE;
    }
}