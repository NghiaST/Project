#include "arrow.hpp"
#include <cmath>
#include <iostream>
#include "support_function.hpp"

//-------------------------------------------------------
//-------------------------Arrow-------------------------

void Arrow::setStatusAnimation(int statusAnimation)
{
    this->statusAnimation = statusAnimation;
}
void Arrow::setTime(double time)
{
    this->time = time;
    if (this->time < 0)
        this->time = 0;
    if (this->time > this->fulltime)
        this->time = this->fulltime;
}
void Arrow::setFullTime(double fulltime)
{
    this->fulltime = fulltime;
}
void Arrow::setStatusAnimationTime(int statusAnimation, double time)
{
    this->setStatusAnimation(statusAnimation);
    this->setTime(time);
}

void Arrow::setStartPoint(sf::Vector2f startPoint)
{
    this->startPoint = startPoint;
}
void Arrow::setEndPoint(sf::Vector2f endPoint)
{
    this->endPoint = endPoint;
}
void Arrow::setNextStartPoint(sf::Vector2f nextStartPoint)
{
    this->nextStartPoint = nextStartPoint;
}
void Arrow::setNextEndPoint(sf::Vector2f nextEndPoint)
{
    this->nextEndPoint = nextEndPoint;
}
void Arrow::setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->nextStartPoint = this->startPoint;
    this->nextEndPoint = this->endPoint;
}
void Arrow::setEndPoint(sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    this->nextStartPoint = nextStartPoint;
    this->nextEndPoint = nextEndPoint;
}
void Arrow::setAllPoint(sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->nextStartPoint = nextStartPoint;
    this->nextEndPoint = nextEndPoint;
}

sf::Vector2f Arrow::getPresentStartPoint()
{
    return this->startPoint + (this->nextStartPoint - this->startPoint) * this->time / this->fulltime;
}
sf::Vector2f Arrow::getPresentStartPoint(int time) 
{
    return this->startPoint + (this->nextStartPoint - this->startPoint) * time / this->fulltime;
}
sf::Vector2f Arrow::getPresentEndPoint()
{
    return this->endPoint + (this->nextEndPoint - this->endPoint) * this->time / this->fulltime;
}
sf::Vector2f Arrow::getPresentEndPoint(int time) 
{
    return this->endPoint + (this->nextEndPoint - this->endPoint) * time / this->fulltime;
}

//-------------------------------------------------------
//-----------------------ArrowNode-----------------------

ArrowNode::ArrowNode(int diameterNode, Palette* palette)
{
    this->radiusNode = diameterNode / 2;
    this->palette = palette;
}

void ArrowNode::render(sf::RenderWindow* window)
{
    // setup time
    double ratio = this->time / this->fulltime;

    // setup point
    sf::Vector2f presentStartPoint = this->getPresentStartPoint();
    sf::Vector2f presentEndPoint = this->getPresentEndPoint();
    
    /// calculate position arrow    
    double pi = 3.141592653589793238462643383279502;
    sf::Vector2f diff = presentEndPoint - presentStartPoint;
    double length = sqrt(diff.x * diff.x + diff.y * diff.y);
    double tmp_length = length - this->radius_triangle - this->radiusNode * 2;
    double rad = atan2(diff.y, diff.x);

    sf::Vector2f startArrow = presentStartPoint + sf::Vector2f(cos(rad), sin(rad)) * radiusNode;
    sf::Vector2f temp_endArrow = presentEndPoint - sf::Vector2f(cos(rad), sin(rad)) * radiusNode;
    sf::Vector2f endArrow = temp_endArrow - sf::Vector2f(cos(rad), sin(rad)) * radius_triangle;

    sf::Vector2f p1 = temp_endArrow;
    sf::Vector2f p2 = endArrow + sf::Vector2f(cos(rad + pi * 2 / 3), sin(rad + pi * 2 / 3)) * radius_triangle;
    sf::Vector2f p3 = endArrow + sf::Vector2f(cos(rad - pi * 2 / 3), sin(rad - pi * 2 / 3)) * radius_triangle;

    /// setup shape
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, p1);
    triangle.setPoint(1, p2);
    triangle.setPoint(2, p3);
    triangle.setOutlineThickness(0);
    this->palette->getColor(0).Coloring(triangle);

    sf::RectangleShape line;
    line.setPosition(startArrow);
    line.setRotation(rad * 180 / pi);
    line.setOutlineThickness(this->thickness);
    this->palette->getColor(0).Coloring(line);

    sf::RectangleShape line2;
    line2.setPosition(startArrow);
    line2.setRotation(rad * 180 / pi);
    line2.setOutlineThickness(this->thickness);
    this->palette->getColor(1).Coloring(line2);

    switch (this->statusAnimation)
    {
        case AR_NOPE :    
            this->palette->getColor(0).Coloring(triangle);
            triangle.setPointCount(0);
            line.setSize(sf::Vector2f(0.f, 0.f));
            line2.setSize(sf::Vector2f(0.f, 0.f));
            break;
        case AR_NORMAL : case AR_NORMALMOVE :
            this->palette->getColor(0).Coloring(triangle);
            line.setSize(sf::Vector2f(tmp_length, 0.f));
            line2.setSize(sf::Vector2f(0.f, 0.f));
            break;
        case AR_ACTIVE : case AR_ACTIVEMOVE :
            this->palette->getColor(1).Coloring(triangle);
            line.setSize(sf::Vector2f(0.f, 0.f));
            line2.setSize(sf::Vector2f(tmp_length, 0.f));
            break;
        case AR_CREATE :
            this->palette->getColor(1).Coloring(triangle);
            if (ratio < 0.99) 
                triangle.setPointCount(0);
            line.setSize(sf::Vector2f(0.f, 0.f));
            line2.setSize(sf::Vector2f(tmp_length * ratio, 0.f));
            break;
        case AR_COLOR_TO :
            this->palette->getColor(ratio < 0.99 ? 0 : 1).Coloring(triangle);
            line.setSize(sf::Vector2f(tmp_length, 0.f));
            line2.setSize(sf::Vector2f(tmp_length * ratio, 0.f));
            break;
        case AR_DEL :
            this->palette->getColor(1).Coloring(triangle);
            if (ratio > 0.01) 
                triangle.setPointCount(0);
            else 
            line.setSize(sf::Vector2f(0.f, 0.f));
            line2.setSize(sf::Vector2f(tmp_length * (1 - ratio), 0.f));
            break;
        default :
            // debug
            std::cout << this->statusAnimation << "error: no type of print arrow found\n";
            exit(5);
            break;
    }

    window->draw(triangle);
    window->draw(line);
    window->draw(line2);
}
void ArrowNode::renderTime(sf::RenderWindow* window, double time)
{
    this->setTime(time);
    this->render(window);
}
void ArrowNode::renderStatusAnimationTime(sf::RenderWindow* window, int statusAnimation, double time)
{
    this->setStatusAnimationTime(statusAnimation, time);
    this->render(window);
}
