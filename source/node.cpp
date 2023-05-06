#include "node.hpp"

///--------------------------------------------------------------------
///--------------------------------Node--------------------------------

Node::Node(sf::Vector2f coord, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette)
    : Style(coord, sizeText, thickness, word, font, palette)
{

}

Node::~Node()
{

}

bool Node::getRunning()
{
    return this->running;
}

int Node::updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType) // check if Style is active
{
    if (this->running == true) 
        return -1;
    bool isMouseInside = this->isMouseInside(mousePos);

    switch (this->status)
    {
        case 0 :
            this->status = isMouseInside;
            break;
        case 1 :
            this->status = isMouseInside;
            if (mouseType == MSE_LEFTCLICK)
                this->status = 2;
            break;
        case 2 :
            if (isMouseInside == false && mouseType == MSE_LEFTCLICK)
                this->status = 0;
            break;
        case 3 : case 4 :
            if (isMouseInside == true && mouseType == MSE_LEFTCLICK)
                this->status = 2;
        default :
            break;
    }
    return this->status;
}

// visualization
void Node::startAnimation(sf::Vector2f startPoint, sf::Vector2f endPoint, NODE_ANIMATION statusAnimation, int preStatus, int status)
{
    this->statusAnimation = statusAnimation;
    this->preStatus = preStatus;
    this->status = status;
    this->startPoint = startPoint;
    this->setXY(this->startPoint);
    this->endPoint = endPoint;

    this->running = true;
    this->ratioColor = 1;
}
void Node::stopAnimation()
{
    this->running = false;
    this->setXY(this->endPoint);
    this->startPoint = this->endPoint = sf::Vector2f(0, 0);
    this->status = 0;
    this->ratioColor = 1;
    this->statusAnimation = NOD_NOPE;
}
void Node::updateAnimation_Moving(double ratio)
{
    sf::Vector2f presentPoint = startPoint + (endPoint - startPoint) * ratio;
    this->setXY(presentPoint);
}
void Node::updateAnimation(double time)
{
    if (time < 0) time = 0;
    if (time > this->fulltime) time = this->fulltime;
    this->time = this->fulltime;

    double ratio = time / fulltime;
    switch (this->statusAnimation)
    {
        case NOD_NOPE :
            break;
        case NOD_STABLE :    /// do nothing
            this->ratioColor = 1;
            break;
        case NOD_RECOLOR :    /// recolor node
            this->ratioColor = ratio;
            break;
        case NOD_APPEAR :    /// create node
            this->ratioColor = ratio;
            break;
        case NOD_DEL :    /// disappear node
            this->ratioColor = 1 - ratio;
            break;
        case NOD_MOVE :    /// move
            this->ratioColor = 1;
            updateAnimation_Moving(ratio);
            break;
        default :
            std::cout << statusAnimation << " Error circlenode::updateanimation\n";
            //exit(1);
    }
}
void Node::renderAnimation(sf::RenderWindow *window, NODE_ANIMATION statusAnimation, double time)
{
    this->updateAnimation(time);
    this->render(window);
}

// print
void Node::refreshrender()
{
    this->shape.setRadius(this->radius);
    this->shape.setOutlineThickness(this->thickness);
    this->shape.setOrigin(this->radius, this->radius);
    this->shape.setPosition(this->coord);

    this->text.setFont(*this->font);
    this->text.setString((this->word).c_str());
    this->text.setCharacterSize(this->sizeText);
    this->text.setOrigin(text.getLocalBounds().left + this->text.getLocalBounds().width / 2.f,
                        text.getLocalBounds().top + this->text.getLocalBounds().height / 2.f);
    this->text.setPosition(this->coord);

    if (this->running == false) {
        palette->getColor(this->status).Coloring(this->shape, this->text);
    }
    else {
        palette->getColor(this->status).Coloring(this->shape, this->text, this->ratioColor);
    }

    if (this->running == false) {
        palette->getColor(this->status).Coloring(this->shape, this->text);
    }
    else if (this->statusAnimation == NOD_APPEAR || this->statusAnimation == NOD_DEL) {
        palette->getColor(this->status).Coloring(this->shape, this->text, this->ratioColor);
    }
    else {
        palette->getColor(this->status).Coloring(this->shape, this->text, this->ratioColor, palette->getColor(this->preStatus));
    }
}
void Node::render(sf::RenderWindow* window) 
{
    this->refreshrender();
    if (this->running == true && this->statusAnimation == NOD_NOPE)
        return;
    window->draw(this->shape);
    window->draw(this->text);
}

///--------------------------------------------------------------------
///-----------------------------CircleNode-----------------------------

CircleNode::CircleNode(sf::Vector2f coord, float diameter, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette)
    : Node(coord, sizeText, thickness, word, font, palette)
{
    this->radius = diameter / 2;
    this->refreshrender();
}

CircleNode::~CircleNode()
{

}

bool CircleNode::isMouseInside(sf::Vector2f mousePos)
{
    return (coord.x - mousePos.x) * (coord.x - mousePos.x) + (coord.y - mousePos.y) * (coord.y - mousePos.y) <= this->radius * this->radius;
}

///--------------------------------------------------------------------
///----------------------------RectangleNode---------------------------

RectangleNode::RectangleNode(sf::Vector2f coord, float length, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette)
    : Node(coord, sizeText, thickness, word, font, palette) // initialize halflength data member
{
    this->halflength = length / 2;
    this->radius = this->halflength * 1.41421;
    shape.setOrigin(this->radius, this->radius);
    shape.setPointCount(4);
    shape.rotate(45.f);
    this->refreshrender();
}

RectangleNode::~RectangleNode()
{

}

bool RectangleNode::isMouseInside(sf::Vector2f mousePos)
{
    return (this->coord.x - this->halflength <= mousePos.x && mousePos.x <= this->coord.x + this->halflength)
        && (this->coord.y - this->halflength <= mousePos.y && mousePos.y <= this->coord.y + this->halflength);
}