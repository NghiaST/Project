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

int Node::updateNode(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType, bool isMouseInside) // check if Style is active
{
    const static int KBD_ENTER = 13;
    const static int KBD_DELETE = 127;
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

bool Node::getRunning()
{
    return this->running;
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

int CircleNode::update(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType) // check if CircleNode is active
{
    if (this->running == true) 
        return -1;
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    return this->Node::updateNode(mousePos, mouseType, keyboardType, isMouseInside);
}
void CircleNode::refreshrender()
{
    this->shape.setPosition(this->coord - sf::Vector2f(this->radius, this->radius));
    this->shape.setRadius(this->radius);
    this->shape.setOutlineThickness(this->thickness);

    this->text.setFont(*this->font);
    this->text.setString((this->word).c_str());
    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->coord.x - this->text.getGlobalBounds().width / 2.f - 1,
        this->coord.y - this->text.getGlobalBounds().height / 2.f - 4
    );

    if (this->running == false) {
        palette->getColor(this->status).Coloring(this->shape, this->text);
    }
    else {
        palette->getColor(this->status).Coloring(this->shape, this->text, this->ratioColor);
    }
}
void CircleNode::render(sf::RenderWindow* window) 
{
    this->refreshrender();
    if (this->running == true && this->statusAnimation == NOD_NOPE)
        return;
    window->draw(this->shape);
    window->draw(this->text);
}

// visualization
void CircleNode::prepareAnimation(sf::Vector2f startPoint, sf::Vector2f endPoint, int statusAnimation, int status)
{
    this->statusAnimation = statusAnimation;
    this->status = status;
    this->startPoint = startPoint;
    this->setXY(this->startPoint);
    this->endPoint = endPoint;

    this->running = true;
    this->ratioColor = 1;
}
void CircleNode::stopAnimation()
{
    this->running = false;
    this->setXY(this->endPoint);
    this->startPoint = this->endPoint = sf::Vector2f(0, 0);
    this->status = 0;
    this->ratioColor = 1;
    this->statusAnimation = NOD_NOPE;
}
void CircleNode::updateAnimation_Moving(double ratio)
{
    sf::Vector2f presentPoint = startPoint + (endPoint - startPoint) * ratio;
    this->setXY(presentPoint);
}
void CircleNode::updateAnimation(double time)
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
void CircleNode::renderAnimation(sf::RenderWindow *window, int statusAnimation, double time)
{
    this->updateAnimation(time);
    this->render(window);
}

///--------------------------------------------------------------------
///----------------------------RectangleNode---------------------------

RectangleNode::RectangleNode(sf::Vector2f coord, float width, float height, unsigned int sizeText, float thickness, std::string word, sf::Font* font, Palette* palette)
    : Node(coord, sizeText, thickness, word, font, palette)
{
    this->width = width;
    this->height = height;
    this->refreshrender();
}

RectangleNode::~RectangleNode()
{

}

int RectangleNode::update(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType) // check if CircleNode is active
{
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    return this->Node::updateNode(mousePos, mouseType, keyboardType, isMouseInside);
}
void RectangleNode::refreshrender()
{
    this->shape.setPosition(this->coord - sf::Vector2f(this->width, this->height) / 2);
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);

    this->text.setFont(*this->font);
    this->text.setString((this->word).c_str());
    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->coord.x - this->text.getGlobalBounds().width / 2.f - 1,
        this->coord.y - this->text.getGlobalBounds().height / 2.f - 4
    );

    if (this->running == false) {
        palette->getColor(this->status).Coloring(this->shape, this->text);
    }
    else {
        palette->getColor(this->status).Coloring(this->shape, this->text, this->ratioColor);
    }
}
void RectangleNode::render(sf::RenderWindow* window) 
{
    this->refreshrender();
    if (this->running == true && this->statusAnimation == NOD_NOPE)
        return;

    window->draw(this->shape);
    window->draw(this->text);
}
