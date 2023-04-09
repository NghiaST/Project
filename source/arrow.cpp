#include "arrow.hpp"
#include <cmath>
#include <iostream>

void Arrow::setStartPoint(sf::Vector2f startPoint)
{
    this->startPoint = startPoint;
}
void Arrow::setEndPoint(sf::Vector2f endPoint)
{
    this->endPoint = endPoint;
}
void Arrow::setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}
void Arrow::render(sf::RenderWindow *window)
{
    double pi = 3.141592653589793238462643383279502;
    double lengthx = endPoint.x - startPoint.x;
    double lengthy = endPoint.y - startPoint.y;
    double length = sqrt(lengthx * lengthx + lengthy * lengthy);
    double rad = atan2(lengthy, lengthx);

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

    sf::RectangleShape lines(sf::Vector2f(length - radius_triangle, 0.f));
    lines.setFillColor(this->defaultColor);
    lines.setOutlineColor(this->defaultColor);
    lines.setOutlineThickness(this->thickness);
    lines.setPosition(centerPoint);
    lines.setRotation(180 + rad * 180 / pi);

    window->draw(triangle);
    window->draw(lines);
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
}