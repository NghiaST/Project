#include "arrow.hpp"
#include <cmath>
#include <iostream>
#include "support_function.hpp"

//-------------------------------------------------------
//----------------------ArrowShape-----------------------

ArrowShape::ArrowShape(sf::Vector2f Point1, sf::Vector2f Point2)
{
    sf::Vector2f diff = Point2 - Point1;
    length = sqrt(diff.x * diff.x + diff.y * diff.y) - radius_triangle;
    double rad = atan2(diff.y, diff.x);

    sf::Vector2f Point3 = Point2 - sf::Vector2f(cos(rad), sin(rad)) * radius_triangle;
    sf::Vector2f Point_p1 = Point2;
    sf::Vector2f Point_p2 = Point3 + sf::Vector2f(cos(rad + PI * 2 / 3), sin(rad + PI * 2 / 3)) * radius_triangle;
    sf::Vector2f Point_p3 = Point3 + sf::Vector2f(cos(rad - PI * 2 / 3), sin(rad - PI * 2 / 3)) * radius_triangle;

    triangle.setPointCount(3);
    triangle.setPoint(0, Point_p1);
    triangle.setPoint(1, Point_p2);
    triangle.setPoint(2, Point_p3);

    line.setPosition(Point1);
    line.setRotation(rad * 180 / PI);

    line.setOutlineThickness(thickness);
    triangle.setOutlineThickness(0);
    setRatio(1);
}

ArrowShape &ArrowShape::operator=(const ArrowShape &other)
{
    this->line = other.line;
    this->triangle = other.triangle;
    return *this;
}

void ArrowShape::setRatio(double ratio)
{
    this->ratio = ratio;
    line.setSize(sf::Vector2f(length * ratio, 0.f));
}

void ArrowShape::setColor(Palette* palette, int status)
{
    palette->getColor(status).Coloring(line);
    palette->getColor(status).Coloring(triangle);
}

void ArrowShape::render(sf::RenderWindow* window)
{
    window->draw(line);
    if (ratio > 0.98) window->draw(triangle);
}

//-------------------------------------------------------
//--------------------Arrow_Control----------------------

void Arrow_Control::setArrowType(ARROW_TYPE arrow_type)
{
    this->arrow_type = arrow_type;
}
void Arrow_Control::setStatusAnimation(ARROW_ANIMATION statusAnimation)
{
    this->statusAnimation = statusAnimation;
}
void Arrow_Control::setTime(double time)
{
    this->time = time;
    if (this->time < 0)
        this->time = 0;
    if (this->time > this->fulltime)
        this->time = this->fulltime;
}
void Arrow_Control::setFullTime(double fulltime)
{
    this->fulltime = fulltime;
}
void Arrow_Control::setStatusAnimationTime(ARROW_ANIMATION statusAnimation, double time)
{
    this->setStatusAnimation(statusAnimation);
    this->setTime(time);
}

void Arrow_Control::setStartPoint(sf::Vector2f startPoint)
{
    this->startPoint = startPoint;
}
void Arrow_Control::setEndPoint(sf::Vector2f endPoint)
{
    this->endPoint = endPoint;
}
void Arrow_Control::setNextStartPoint(sf::Vector2f nextStartPoint)
{
    this->nextStartPoint = nextStartPoint;
}
void Arrow_Control::setNextEndPoint(sf::Vector2f nextEndPoint)
{
    this->nextEndPoint = nextEndPoint;
}
void Arrow_Control::setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->nextStartPoint = this->startPoint;
    this->nextEndPoint = this->endPoint;
}
void Arrow_Control::setEndPoint(sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    this->nextStartPoint = nextStartPoint;
    this->nextEndPoint = nextEndPoint;
}
void Arrow_Control::setAllPoint(sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->nextStartPoint = nextStartPoint;
    this->nextEndPoint = nextEndPoint;
}

sf::Vector2f Arrow_Control::getPresentStartPoint()
{
    return this->startPoint + (this->nextStartPoint - this->startPoint) * this->time / this->fulltime;
}
sf::Vector2f Arrow_Control::getPresentStartPoint(int time) 
{
    return this->startPoint + (this->nextStartPoint - this->startPoint) * time / this->fulltime;
}
sf::Vector2f Arrow_Control::getPresentEndPoint()
{
    return this->endPoint + (this->nextEndPoint - this->endPoint) * this->time / this->fulltime;
}
sf::Vector2f Arrow_Control::getPresentEndPoint(int time) 
{
    return this->endPoint + (this->nextEndPoint - this->endPoint) * time / this->fulltime;
}

//-------------------------------------------------------
//-----------------------ArrowNode-----------------------

ArrowNode::ArrowNode(int diameterNode, Palette *palette)
{
    this->radiusNode = diameterNode / 2;
    this->palette = palette;
}

void ArrowNode::render_Arr1(sf::RenderWindow* window)
{
    // setup time
    double ratio = this->time / this->fulltime;

    // setup point
    sf::Vector2f presentStartPoint = this->getPresentStartPoint();
    sf::Vector2f presentEndPoint = this->getPresentEndPoint();
    
    /// calculate position arrow
    sf::Vector2f diff = presentEndPoint - presentStartPoint;
    double rad = atan2(diff.y, diff.x);

    sf::Vector2f startArrow = presentStartPoint + sf::Vector2f(cos(rad), sin(rad)) * radiusNode;
    sf::Vector2f endArrow = presentEndPoint - sf::Vector2f(cos(rad), sin(rad)) * radiusNode;

    std::vector<ArrowShape> listArrowShape;
    listArrowShape.push_back(ArrowShape(startArrow, endArrow));

    switch (this->statusAnimation)
    {
        case AR_NOPE :
            listArrowShape.clear();
            break;
        case AR_NORMAL :
            listArrowShape[0].setColor(palette, 0);
            break;
        case AR_ACTIVE :
            listArrowShape[0].setColor(palette, 1);
            break;
        case AR_CREATE :
            listArrowShape[0].setColor(palette, 1);
            listArrowShape[0].setRatio(ratio);
            break;
        case AR_COLOR_TO :
            listArrowShape.push_back(listArrowShape[0]);
            listArrowShape[0].setColor(palette, 0);
            listArrowShape[1].setColor(palette, 1);
            listArrowShape[1].setRatio(ratio);
            break;
        case AR_DEL :
            listArrowShape[0].setColor(palette, 1);
            listArrowShape[0].setRatio(1 - ratio);
            break;
        case AR_MOVE :
            exit(1);
        default :
            // debug
            std::cout << this->statusAnimation << "error: no type of print arrow found\n";
            exit(5);
            break;
    }
    for(ArrowShape& arrShape : listArrowShape)
        arrShape.render(window);
}

void ArrowNode::render_Arr2(sf::RenderWindow* window)
{
    // setup time
    double ratio = this->time / this->fulltime;
    double fix_rad = PI / 9;

    // setup point
    sf::Vector2f presentStartPoint = this->getPresentStartPoint();
    sf::Vector2f presentEndPoint = this->getPresentEndPoint();
    
    /// calculate position arrow
    sf::Vector2f diff = presentEndPoint - presentStartPoint;
    double rad = atan2(diff.y, diff.x);

    sf::Vector2f startArrow_1 = presentStartPoint + sf::Vector2f(cos(rad - fix_rad), sin(rad - fix_rad)) * radiusNode;
    sf::Vector2f endArrow_1 = presentEndPoint + sf::Vector2f(cos(PI + rad + fix_rad), sin(PI + rad + fix_rad)) * radiusNode;
    sf::Vector2f endArrow_2 = presentStartPoint + sf::Vector2f(cos(rad + fix_rad), sin(rad + fix_rad)) * radiusNode;
    sf::Vector2f startArrow_2 = presentEndPoint + sf::Vector2f(cos(PI + rad - fix_rad), sin(PI + rad - fix_rad)) * radiusNode;

    std::vector<ArrowShape> listArrowShape;
    listArrowShape.push_back(ArrowShape(startArrow_1, endArrow_1));
    listArrowShape.push_back(ArrowShape(startArrow_2, endArrow_2));

    switch (this->statusAnimation)
    {
        case AR_NOPE :
            listArrowShape.clear();
            break;
        case AR_NORMAL :
            listArrowShape[0].setColor(palette, 0);
            listArrowShape[1].setColor(palette, 0);
            break;
        case AR_ACTIVE :
            listArrowShape[0].setColor(palette, 1);
            listArrowShape[1].setColor(palette, 1);
            break;
        case AR_CREATE :
            listArrowShape[0].setColor(palette, 1);
            listArrowShape[1].setColor(palette, 1);
            listArrowShape[0].setRatio(ratio);
            listArrowShape[1].setRatio(ratio);
            break;
        case AR_COLOR_TO :
            listArrowShape.push_back(listArrowShape[0]);
            listArrowShape.push_back(listArrowShape[1]);
            listArrowShape[0].setColor(palette, 0);
            listArrowShape[1].setColor(palette, 0);
            listArrowShape[2].setColor(palette, 1);
            listArrowShape[3].setColor(palette, 1);
            listArrowShape[2].setRatio(ratio);
            listArrowShape[3].setRatio(ratio);
            break;
        case AR_DEL :
            listArrowShape[0].setColor(palette, 1);
            listArrowShape[1].setColor(palette, 1);
            listArrowShape[0].setRatio(1 - ratio);
            listArrowShape[1].setRatio(1 - ratio);
            break;
        case AR_MOVE :
            exit(1);
        default :
            // debug
            std::cout << this->statusAnimation << "error: no type of print arrow found\n";
            exit(5);
            break;
    }
    for(ArrowShape& arrShape : listArrowShape)
        arrShape.render(window);
}

void ArrowNode::render_ArrLoop(sf::RenderWindow* window)
{
    if (statusAnimation == AR_NOPE) return;
    // setup time
    double ratio = this->time / this->fulltime;

    // setup point
    sf::Vector2f presentStartPoint = this->getPresentStartPoint();
    sf::Vector2f presentEndPoint = this->getPresentEndPoint();
    
    /// calculate position arrow

    std::vector<sf::Vector2f> junction;
    junction.push_back(presentStartPoint);
    junction.push_back(junction.back() + sf::Vector2f(30, 0));
    junction.push_back(sf::Vector2f(junction.back().x, 100));
    junction.push_back(sf::Vector2f(presentEndPoint.x - 30, junction.back().y));
    junction.push_back(sf::Vector2f(junction.back().x, presentEndPoint.y));
    junction.push_back(presentEndPoint);

    std::vector<ArrowShape> listArrowShape;
    for(int i = 0; i < 5; i++)
        listArrowShape.push_back(ArrowShape(junction[i], junction[i + 1]));

    for(int i = 0; i < 5; i++)
    switch (this->statusAnimation)
    {
        // int present_ratio = listArrowShape[i].push_back(i);
        case AR_NORMAL :
            listArrowShape[i].setColor(palette, 0);
            break;
        case AR_ACTIVE :
            listArrowShape[0].setColor(palette, 1);
            break;
        case AR_CREATE :
            listArrowShape[i].setColor(palette, 1);
            break;
        case AR_COLOR_TO :
            listArrowShape.push_back(listArrowShape[i]);
            listArrowShape[i].setColor(palette, 0);
            listArrowShape[i + 5].setColor(palette, 1);
            break;
        case AR_DEL :
            listArrowShape[i].setColor(palette, 1);
            break;
        case AR_MOVE :
            exit(1);
        default :
            // debug
            std::cout << this->statusAnimation << "error: no type of print arrow found\n";
            exit(5);
            break;
    }
    for(ArrowShape& arrShape : listArrowShape)
        arrShape.render(window);
}

void ArrowNode::render(sf::RenderWindow* window)
{
    switch (arrow_type)
    {
        case ARR_1 : render_Arr1(window); break;
        case ARR_2 : render_Arr2(window); break;
        case ARR_LOOP : render_ArrLoop(window); break;
    }
}
void ArrowNode::renderTime(sf::RenderWindow* window, double time)
{
    this->setTime(time);
    this->render(window);
}
void ArrowNode::renderStatusAnimationTime(sf::RenderWindow* window, ARROW_ANIMATION statusAnimation, double time)
{
    this->setStatusAnimationTime(statusAnimation, time);
    this->render(window);
}
