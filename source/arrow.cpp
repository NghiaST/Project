#include "arrow.hpp"
#include <cmath>
#include <iostream>
#include "support_function.hpp"

void Arrow::setStatus(int status)
{
    this->status = status;
}
void Arrow::setFullTime(double fulltime)
{
    this->fulltime = fulltime;
}
void Arrow::setStartPoint(sf::Vector2f startPoint)
{
    this->startPoint = startPoint;
}
void Arrow::setEndPoint(sf::Vector2f endPoint)
{
    this->endPoint = endPoint;
}
void Arrow::setNextPoint(sf::Vector2f nextPoint)
{
    this->nextPoint = nextPoint;
}
void Arrow::setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->nextPoint = this->endPoint;
}
void Arrow::setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->nextPoint = nextPoint;
}
void Arrow::render(sf::RenderWindow *window)
{
    double pi = 3.141592653589793238462643383279502;
    double lengthx = endPoint.x - startPoint.x;
    double lengthy = endPoint.y - startPoint.y;
    double length = sqrt(lengthx * lengthx + lengthy * lengthy);
    double rad = atan2(lengthy, lengthx);
    double tmp_length = length - radius_triangle;

    sf::Vector2f centerPoint;
    centerPoint.x = endPoint.x - radius_triangle * cos(rad);
    centerPoint.y = endPoint.y - radius_triangle * sin(rad);

    sf::Vector2f p1 = endPoint;
    sf::Vector2f p2(centerPoint.x + this->radius_triangle * cos(rad + pi * 2 / 3), centerPoint.y + radius_triangle * sin(rad + pi * 2 / 3));
    sf::Vector2f p3(centerPoint.x + radius_triangle * cos(rad - pi * 2 / 3), centerPoint.y + radius_triangle * sin(rad - pi * 2 / 3));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, p1);
    triangle.setPoint(1, p2);
    triangle.setPoint(2, p3);

    triangle.setFillColor(this->defaultColor);
    triangle.setOutlineThickness(0);

    sf::RectangleShape lines(sf::Vector2f(tmp_length, 0.f));
    lines.setFillColor(this->defaultColor);
    lines.setOutlineColor(this->defaultColor);
    lines.setOutlineThickness(this->thickness);
    lines.setPosition(this->startPoint);
    lines.setRotation(rad * 180 / pi);

    window->draw(triangle);
    window->draw(lines);
}

void Arrow::renderTime(sf::RenderWindow *window, double time)
{
    /*double pi = 3.141592653589793238462643383279502;
    double lengthx = endPoint.x - startPoint.x;
    double lengthy = endPoint.y - startPoint.y;
    double length = sqrt(lengthx * lengthx + lengthy * lengthy);
    double rad = atan2(lengthy, lengthx);
    double tmp_length = length - radius_triangle;

    sf::Vector2f centerPoint;
    centerPoint.x = endPoint.x - radius_triangle * cos(rad);
    centerPoint.y = endPoint.y - radius_triangle * sin(rad);

    sf::Vector2f p1 = endPoint;
    sf::Vector2f p2(centerPoint.x + this->radius_triangle * cos(rad + pi * 2 / 3), centerPoint.y + radius_triangle * sin(rad + pi * 2 / 3));
    sf::Vector2f p3(centerPoint.x + radius_triangle * cos(rad - pi * 2 / 3), centerPoint.y + radius_triangle * sin(rad - pi * 2 / 3));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, p1);
    triangle.setPoint(1, p2);
    triangle.setPoint(2, p3);

    if (time < 0.98) {
        triangle.setFillColor(this->defaultColor);
    }
    else {
        triangle.setFillColor(this->activeColor);
    }

    triangle.setOutlineThickness(0);

    sf::RectangleShape lines(sf::Vector2f(tmp_length, 0.f));
    lines.setFillColor(this->defaultColor);
    lines.setOutlineColor(this->defaultColor);
    lines.setOutlineThickness(this->thickness);
    lines.setPosition(startPoint);
    lines.setRotation(rad * 180 / pi);

    window->draw(lines);
    window->draw(triangle);

    lines.setFillColor(this->activeColor);
    lines.setOutlineColor(this->activeColor);

    if (time < 0.98) {
        lines.setSize(sf::Vector2f((tmp_length) * time, 0.f));
    }
    else {
        lines.setSize(sf::Vector2f(tmp_length, 0.f));
    }
    lines.setOutlineThickness(this->thickness + 1);
    window->draw(lines);*/
    this->renderStatusTime(window, this->status, time);
}

void Arrow::renderStatusTime(sf::RenderWindow* window, int statuss, double time)
{
    // setup time
    double ratio = time / this->fulltime;
    if (ratio < 0) ratio = 0;
    if (ratio > 1) ratio = 1;

    // setup point
    sf::Vector2f presentPoint;
    presentPoint = endPoint + (nextPoint - endPoint) * ratio;

    /// calculate position arrow
    double pi = 3.141592653589793238462643383279502;
    sf::Vector2f diff = presentPoint - startPoint;
    double length = sqrt(diff.x * diff.x + diff.y * diff.y);
    double tmp_length = length - radius_triangle;
    double rad = atan2(diff.y, diff.x);

    sf::Vector2f centerPoint = presentPoint - sf::Vector2f(cos(rad), sin(rad)) * radius_triangle;

    sf::Vector2f p1 = presentPoint;
    sf::Vector2f p2 = centerPoint + sf::Vector2f(cos(rad + pi * 2 / 3), sin(rad + pi * 2 / 3)) * radius_triangle;
    sf::Vector2f p3 = centerPoint + sf::Vector2f(cos(rad - pi * 2 / 3), sin(rad - pi * 2 / 3)) * radius_triangle;
    // centerPoint.x = presentPoint.x - radius_triangle * cos(rad);
    // centerPoint.y = presentPoint.y - radius_triangle * sin(rad);

    // sf::Vector2f p1 = presentPoint;
    // sf::Vector2f p2(centerPoint.x + this->radius_triangle * cos(rad + pi * 2 / 3), centerPoint.y + radius_triangle * sin(rad + pi * 2 / 3));
    // sf::Vector2f p3(centerPoint.x + radius_triangle * cos(rad - pi * 2 / 3), centerPoint.y + radius_triangle * sin(rad - pi * 2 / 3));

    /// setup shape
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, p1);
    triangle.setPoint(1, p2);
    triangle.setPoint(2, p3);
    triangle.setOutlineThickness(0);

    sf::RectangleShape line;
    line.setPosition(startPoint);
    line.setRotation(rad * 180 / pi);
    line.setFillColor(this->defaultColor);
    line.setOutlineColor(this->defaultColor);
    line.setOutlineThickness(this->thickness);

    sf::RectangleShape line2;
    line2.setPosition(startPoint);
    line2.setRotation(rad * 180 / pi);
    line2.setFillColor(this->activeColor);
    line2.setOutlineColor(this->activeColor);
    line2.setOutlineThickness(this->thickness);

    switch (statuss)
    {
        case 0 : 
            triangle.setFillColor(this->defaultColor);
            line.setSize(sf::Vector2f(tmp_length, 0.f));
            line2.setSize(sf::Vector2f(0.f, 0.f));
            break;
        case 1 :
            if (ratio < 0.98) 
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
            triangle.setFillColor(ratio < 0.98 ? this->defaultColor : this->activeColor);
            line.setSize(sf::Vector2f(tmp_length, 0.f));
            line2.setSize(sf::Vector2f(tmp_length * ratio, 0.f));
            break;
        case 4 :
            if (ratio > 0.02) 
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

    std::cout << statuss << '\n';
}

ArrowNode::ArrowNode(int sizeNode)
{
    this->radiusNode = sizeNode / 2;
}

ArrowNode::ArrowNode(int sizeNode, sf::Vector2f startNode, sf::Vector2f endNode)
{
    this->radiusNode = sizeNode / 2;
    
    double lengthx = endNode.x - startNode.x;
    double lengthy = endNode.y - startNode.y;
    double length = sqrt(lengthx * lengthx + lengthy * lengthy);

    this->startPoint.x = startNode.x + this->radiusNode * lengthx / length;
    this->startPoint.y = startNode.y + this->radiusNode * lengthy / length;

    this->endPoint.x = endNode.x - this->radiusNode * lengthx / length;
    this->endPoint.y = endNode.y - this->radiusNode * lengthy / length;

    this->nextPoint = this->endPoint;
}

void ArrowNode::setNode(sf::Vector2f startNode, sf::Vector2f endNode)
{
    double lengthx = endNode.x - startNode.x;
    double lengthy = endNode.y - startNode.y;
    double length = sqrt(lengthx * lengthx + lengthy * lengthy);

    this->startPoint.x = startNode.x + this->radiusNode * lengthx / length;
    this->startPoint.y = startNode.y + this->radiusNode * lengthy / length;

    this->endPoint.x = endNode.x - this->radiusNode * lengthx / length;
    this->endPoint.y = endNode.y - this->radiusNode * lengthy / length;

    this->nextPoint = this->endPoint;
}

void ArrowNode::setNextNode(sf::Vector2f nextNode)
{
    double lengthx = nextNode.x - this->startPoint.x;
    double lengthy = nextNode.y - this->startPoint.y;
    double length = sqrt(lengthx * lengthx + lengthy * lengthy);

    this->nextPoint.x = nextNode.x - this->radiusNode * lengthx / length;
    this->nextPoint.y = nextNode.y - this->radiusNode * lengthy / length;
}
