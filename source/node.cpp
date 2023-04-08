#include "node.hpp"

///--------------------------------------------------------------------
///--------------------------------Node--------------------------------

Node::Node(int x, int y, sf::Font* font, std::string word, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2)
{
    // Default
    this->status = 0;
    this->view = true;

    // Position
    this->x = x;
    this->y = y;

    // shape
    this->thickness = 2;

    // font
    this->font = font;

    // word
    this->word = word;
    this->wordOut = "";

    // wordsize
    this->sizeText = 16;
    this->sizeTextOut = 12;

    // color
    this->idleFillColor = idleFillColor;
    this->hoverFillColor = sf::Color::Green;
    this->activeFillColor = sf::Color::Yellow;
    this->runFillColor = runFillColor;
    this->runFillColor2 = runFillColor2;

    this->idleOutlineColor = sf::Color::Black;
    this->hoverOutlineColor = sf::Color::Black;
    this->activeOutlineColor = sf::Color::Black;
    this->runOutlineColor = sf::Color::Black;
    this->runOutlineColor2 = sf::Color::Black;

    this->idleTextColor = sf::Color::Red;
    this->hoverTextColor = sf::Color::Red;
    this->activeTextColor = sf::Color::Red;
    this->runTextColor = sf::Color::Red;
    this->runTextColor2 = sf::Color::Red;
    
    this->textOutColor = sf::Color::Blue;
}

Node::~Node()
{

}

void Node::setStatus(int status)
{
    this->status = status;
}
void Node::setX(int x) 
{
    this->x = x;
}
void Node::setY(int y)
{
    this->y = y;
}
void Node::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Node::setWord(std::string word)
{
    this->word = word;
}
void Node::setWordOut(std::string wordOut)
{
    this->wordOut = wordOut;
}
void Node::setIDLEFillColor(sf::Color idleFillColor)
{
    this->idleFillColor = idleFillColor;
}
void Node::setIDLETextColor(sf::Color idleOutlineColor)
{
    this->idleOutlineColor = idleOutlineColor;
}

int Node::getX()
{
    return this->x;
}
int Node::getY()
{
    return this->y;
}
int Node::getStatus()
{
    return this->status;
}

int Node::updateNode(sf::Vector2f mousePos, int mouseType, int keyboardType, bool isMouseInside) // check if node is active
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
        case 2:
            if (isMouseInside == false && mouseType == MSE_LEFTCLICK)
                this->status = 0;
            break;
        default :
            break;
    }
    return this->status;
}

///--------------------------------------------------------------------
///-----------------------------CircleNode-----------------------------

CircleNode::CircleNode(int x, int y, int radius, sf::Font* font, std::string word, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2)
    : Node(x, y, font, word, idleFillColor, runFillColor, runFillColor2)
{
    // shape
    this->radius = radius;
    this->refreshrender();
}
CircleNode::~CircleNode()
{

}

int CircleNode::update(sf::Vector2f mousePos, int mouseType, int keyboardType) // check if CircleNode is active
{
    bool isMouseInside = this->shape.getGlobalBounds().contains(mousePos);
    return this->Node::updateNode(mousePos, mouseType, keyboardType, isMouseInside);
}
void CircleNode::refreshrender()
{
    this->shape.setPosition(sf::Vector2f(this->x - this->radius, this->y - this->radius));
    this->shape.setRadius(this->radius);
    this->shape.setOutlineThickness(this->thickness);

    switch (this->status)
    {
        case 0:
            this->shape.setFillColor(this->idleFillColor);
            this->shape.setOutlineColor(this->idleOutlineColor);
            this->text.setFillColor(this->idleTextColor);
            break;
        case 1:
            this->shape.setFillColor(this->hoverFillColor);
            this->shape.setOutlineColor(this->hoverOutlineColor);
            this->text.setFillColor(this->hoverTextColor);
            break;
        case 2:
            this->shape.setFillColor(this->activeFillColor);
            this->shape.setOutlineColor(this->activeOutlineColor);
            this->text.setFillColor(this->activeTextColor);
            break;
        case 3:
            this->shape.setFillColor(this->runFillColor);
            this->shape.setOutlineColor(this->runOutlineColor);
            this->text.setFillColor(this->runTextColor);
            break;
        case 4:
            this->shape.setFillColor(this->runFillColor2);
            this->shape.setOutlineColor(this->runOutlineColor2);
            this->text.setFillColor(this->runTextColor2);
            break;
    }

    this->text.setFont(*this->font);
    this->text.setString(this->word);

    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->x - this->text.getGlobalBounds().width / 2.f,
        this->y - this->text.getGlobalBounds().height / 2.f - 2
    );
}
void CircleNode::render(sf::RenderTarget* target) 
{
    this->refreshrender();

    target->draw(this->shape);
    target->draw(this->text);
}

///--------------------------------------------------------------------
///----------------------------RectangleNode---------------------------

RectangleNode::RectangleNode(int x, int y, int width, int height, sf::Font* font, std::string word, sf::Color idleFillColor, sf::Color runFillColor, sf::Color runFillColor2)
    : Node(x, y, font, word, idleFillColor, runFillColor, runFillColor2)
{
    // shape
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
    this->shape.setPosition(sf::Vector2f(this->x - this->width / 2.0, this->y - this->height / 2.0));
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setOutlineThickness(this->thickness);

    switch (this->status)
    {
        case 0:
            this->shape.setFillColor(this->idleFillColor);
            this->shape.setOutlineColor(this->idleOutlineColor);
            this->text.setFillColor(this->idleTextColor);
            break;
        case 1:
            this->shape.setFillColor(this->hoverFillColor);
            this->shape.setOutlineColor(this->hoverOutlineColor);
            this->text.setFillColor(this->hoverTextColor);
            break;
        case 2:
            this->shape.setFillColor(this->activeFillColor);
            this->shape.setOutlineColor(this->activeOutlineColor);
            this->text.setFillColor(this->activeTextColor);
            break;
        case 3:
            this->shape.setFillColor(this->runFillColor);
            this->shape.setOutlineColor(this->runOutlineColor);
            this->text.setFillColor(this->runTextColor);
            break;
        case 4:
            this->shape.setFillColor(this->runFillColor2);
            this->shape.setOutlineColor(this->runOutlineColor2);
            this->text.setFillColor(this->runTextColor2);
            break;
    }

    this->text.setFont(*this->font);
    this->text.setString(this->word);

    this->text.setCharacterSize(this->sizeText);
    this->text.setPosition(
        this->x - this->text.getGlobalBounds().width / 2.f,
        this->y - this->text.getGlobalBounds().height / 2.f - 2
    );
}
void RectangleNode::render(sf::RenderTarget* target) 
{
    this->refreshrender();

    target->draw(this->shape);
    target->draw(this->text);
}
