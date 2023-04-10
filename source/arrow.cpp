#include "arrow.hpp"
#include <cmath>
#include <iostream>
#include "support_function.hpp"

//-------------------------------------------------------
//-------------------------Arrow-------------------------

void Arrow::setStatus(int status)
{
    this->status = status;
}
void Arrow::setTime(double time)
{
    this->time = time;
}
void Arrow::setFullTime(double fulltime)
{
    this->fulltime = fulltime;
}
void Arrow::setStatusTime(int status, double time)
{
    this->status = status;
    this->time = time;
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

ArrowNode::ArrowNode(int diameterNode)
{
    this->radiusNode = diameterNode / 2;
}
ArrowNode::ArrowNode(int diameterNode, sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    this->radiusNode = diameterNode / 2;
    this->setPoint(startPoint, endPoint);
}

void ArrowNode::render(sf::RenderWindow* window)
{
    // setup time
    double ratio = this->time / this->fulltime;
    if (ratio < 0) ratio = 0;
    if (ratio > 1) ratio = 1;

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

    sf::RectangleShape line;
    line.setPosition(startArrow);
    line.setRotation(rad * 180 / pi);
    line.setFillColor(this->defaultColor);
    line.setOutlineColor(this->defaultColor);
    line.setOutlineThickness(this->thickness);

    sf::RectangleShape line2;
    line2.setPosition(startArrow);
    line2.setRotation(rad * 180 / pi);
    line2.setFillColor(this->activeColor);
    line2.setOutlineColor(this->activeColor);
    line2.setOutlineThickness(this->thickness);

    switch (this->status)
    {
        case 0 : 
            triangle.setFillColor(this->defaultColor);
            line.setSize(sf::Vector2f(tmp_length, 0.f));
            line2.setSize(sf::Vector2f(0.f, 0.f));
            break;
        case 1 :
            if (ratio < 0.99) 
                triangle.setPointCount(0);
            else 
                triangle.setFillColor(this->activeColor);
            line.setSize(sf::Vector2f(0.f, 0.f));
            line2.setSize(sf::Vector2f(tmp_length * ratio, 0.f));
            break;
        case 2 :
            triangle.setFillColor(this->defaultColor);
            line.setSize(sf::Vector2f(tmp_length, 0.f));
            line2.setSize(sf::Vector2f(0, 0.f));
            break;
        case 3 :
            triangle.setFillColor(ratio < 0.99 ? this->defaultColor : this->activeColor);
            line.setSize(sf::Vector2f(tmp_length, 0.f));
            line2.setSize(sf::Vector2f(tmp_length * ratio, 0.f));
            break;
        case 4 :
            if (ratio > 0.01) 
                triangle.setPointCount(0);
            else 
                triangle.setFillColor(this->activeColor);
            line.setSize(sf::Vector2f(0.f, 0.f));
            line2.setSize(sf::Vector2f(tmp_length * (1 - ratio), 0.f));
            break;
        default :
            // debug
            std::cout << "error: no type of print arrow found\n";
            exit(3);
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
void ArrowNode::renderStatusTime(sf::RenderWindow* window, int status, double time)
{
    this->setStatus(status);
    this->setTime(time);
    this->render(window);
}
