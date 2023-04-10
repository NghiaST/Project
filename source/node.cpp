#include "node.hpp"

///--------------------------------------------------------------------
///--------------------------------Node--------------------------------

Node::Node(int x, int y, sf::Font *font, std::string word, int sizeText, std::vector<TripleColor> listColor)
    : Style(x, y, font, word, sizeText, listColor)
{

}

Node::Node(int x, int y, sf::Font *font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2)
    : Style(x, y, font, word, sizeText, idleColor, hoverColor, activeColor, runColor, runColor2)
{

}

Node::~Node()
{

}

int Node::updateNode(sf::Vector2f mousePos, int mouseType, int keyboardType, bool isMouseInside) // check if Style is active
{
    const static int KBD_ENTER = 13;
    const static int KBD_DELETE = 127;
    const static int MSE_LEFTCLICK = 1;
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

///--------------------------------------------------------------------
///-----------------------------CircleNode-----------------------------

CircleNode::CircleNode(int x, int y, int radius, sf::Font *font, std::string word, int sizeText, std::vector<TripleColor> listColor)
    : Node(x, y, font, word, sizeText, listColor)
{
    this->radius = radius;
    this->refreshrender();
}

CircleNode::CircleNode(int x, int y, int radius, sf::Font *font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2)
    : Node(x, y, font, word, sizeText, idleColor, hoverColor, activeColor, runColor, runColor2)
{
    this->radius = radius;
    this->refreshrender();
}

CircleNode::~CircleNode()
{

}

int CircleNode::update(sf::Vector2f mousePos, int mouseType, int keyboardType) // check if CircleNode is active
{
    if (this->running == true) 
        return -1;
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    return this->Node::updateNode(mousePos, mouseType, keyboardType, isMouseInside);
}
void CircleNode::refreshrender()
{
    this->shape.setPosition(sf::Vector2f(this->x - this->radius, this->y - this->radius));
    this->shape.setRadius(this->radius);
    this->shape.setOutlineThickness(this->thickness);

    this->text.setFont(*this->font);
    this->text.setString(this->word);
    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->x - this->text.getGlobalBounds().width / 2.f - 1,
        this->y - this->text.getGlobalBounds().height / 2.f - 4
    );

    this->listColor[this->status % 5].Coloring(this->shape, this->text);
}
void CircleNode::render(sf::RenderWindow* window) 
{
    this->refreshrender();

    window->draw(this->shape);
    window->draw(this->text);
}

// visualization
void CircleNode::prepareAnimation(sf::Vector2f endPoint, int status)
{
    this->startPoint = this->getXY();
    this->endPoint = endPoint;
    this->status = status;
    this->running = false;
}
void CircleNode::stopAnimation()
{
    this->setXY(this->endPoint);
    this->startPoint = this->endPoint = sf::Vector2f(0, 0);
    this->status = 0;
    this->running = false;
}
void CircleNode::updateMoving(int status, double time)
{
    double ratio = time / fulltime;
    if (ratio < 0) ratio = 0;
    if (ratio > 1) ratio = 1;
    sf::Vector2f presentPoint = startPoint + (endPoint - startPoint) * ratio;
    this->status = status;
    this->setXY(presentPoint);
}
void CircleNode::renderAnimation(sf::RenderWindow *window, int status, double time)
{
    this->updateMoving(status, time);

    this->render(window);
}
///--------------------------------------------------------------------
///----------------------------RectangleNode---------------------------

RectangleNode::RectangleNode(int x, int y, int width, int height, sf::Font *font, std::string word, int sizeText, std::vector<TripleColor> listColor)
    : Node(x, y, font, word, sizeText, listColor)
{
    this->width = width;
    this->height = height;
    this->refreshrender();
}

RectangleNode::RectangleNode(int x, int y, int width, int height, sf::Font *font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2)
    : Node(x, y, font, word, sizeText, idleColor, hoverColor, activeColor, runColor, runColor2)
{
    this->width = width;
    this->height = height;
    this->refreshrender();
}
RectangleNode::~RectangleNode()
{

}

int RectangleNode::update(sf::Vector2f mousePos, int mouseType, int keyboardType) // check if CircleNode is active
{
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    return this->Node::updateNode(mousePos, mouseType, keyboardType, isMouseInside);
}
void RectangleNode::refreshrender()
{
    this->shape.setPosition(sf::Vector2f(this->x - this->width / 2.f, this->y - this->height / 2.f));
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);

    this->text.setFont(*this->font);
    this->text.setString(this->word);

    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->x - this->text.getGlobalBounds().width / 2.f,
        this->y - this->text.getGlobalBounds().height / 2.f - 4
    );

    this->listColor[this->status].Coloring(this->shape, this->text);
}
void RectangleNode::render(sf::RenderWindow* window) 
{
    this->refreshrender();

    window->draw(this->shape);
    window->draw(this->text);
}
