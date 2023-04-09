#include "node.hpp"

///--------------------------------------------------------------------
///--------------------------------Node--------------------------------

Node::Node(int x, int y, sf::Font *font, std::string word, int sizeText, TripleColor idleColor, TripleColor hoverColor, TripleColor activeColor, TripleColor runColor, TripleColor runColor2)
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
    this->sizeText = sizeText;
    this->sizeTextOut = 12;

    // color
    this->listColor[0] = idleColor;
    this->listColor[1] = hoverColor;
    this->listColor[2] = activeColor;
    this->listColor[3] = runColor;
    this->listColor[4] = runColor2;

    // default
    this->listColor[1].changeFillColor(sf::Color::Green);
    this->listColor[2].changeFillColor(sf::Color::Yellow);

    this->listColor[0].changeTextColor(sf::Color::Red);
    this->listColor[1].changeTextColor(sf::Color::Red);
    this->listColor[2].changeTextColor(sf::Color::Red);
    this->listColor[3].changeTextColor(sf::Color::Red);
    this->listColor[4].changeTextColor(sf::Color::Red);

    this->listColor[0].changeOutlineColor(sf::Color::Black);
    this->listColor[1].changeOutlineColor(sf::Color::Black);
    this->listColor[2].changeOutlineColor(sf::Color::Black);
    this->listColor[3].changeOutlineColor(sf::Color::Black);
    this->listColor[4].changeOutlineColor(sf::Color::Black);

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
void Node::setView(bool view)
{
    this->view = view;
}
void Node::setWord(std::string word)
{
    this->word = word;
}
void Node::setWordOut(std::string wordOut)
{
    this->wordOut = wordOut;
}
void Node::SetFillColor(int id, sf::Color FillColor)
{
    this->listColor[id].changeFillColor(FillColor);
}
void Node::SetTextColor(int id, sf::Color TextColor)
{
    this->listColor[id].changeTextColor(TextColor);
}
void Node::SetOutlineColor(int id, sf::Color OutlineColor)
{
    this->listColor[id].changeOutlineColor(OutlineColor);
}
void Node::SetColor(int id, TripleColor Color)
{
    this->listColor[id] = Color;
}
void Node::swapView()
{
    this->view = !this->view;
}

int Node::getStatus()
{
    return this->status;
}
int Node::getX()
{
    return this->x;
}
int Node::getY()
{
    return this->y;
}
bool Node::getView()
{
    return this->view;
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
        this->x - this->text.getGlobalBounds().width / 2.f,
        this->y - this->text.getGlobalBounds().height / 2.f - 4
    );

    this->listColor[this->status].Coloring(this->shape, this->text);
}
void CircleNode::render(sf::RenderTarget* target) 
{
    this->refreshrender();

    target->draw(this->shape);
    target->draw(this->text);
}

///--------------------------------------------------------------------
///----------------------------RectangleNode---------------------------

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
void RectangleNode::render(sf::RenderTarget* target) 
{
    this->refreshrender();

    target->draw(this->shape);
    target->draw(this->text);
}
