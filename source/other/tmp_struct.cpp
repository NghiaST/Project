#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <unistd.h>
#include <windows.h>
using namespace std;

struct coord {
    int x, y;
};
struct color {
    int r, g, b;
    sf::Color getcolor() {
        return sf::Color(r, g, b);
    }
};
struct ViewNode {
    coord point;
    int radius = 10;
    color Vcolor;
    sf::CircleShape shape;
    ViewNode(int _x = 0, int _y = 0, int _r = 10) {
        point.x = _x;
        point.y = _y;
        radius = _r;
    }
    void setup() {
        shape = sf::CircleShape(radius);
        shape.setFillColor(Vcolor.getcolor());
        shape.setOutlineThickness(5);
        shape.setOutlineColor(sf::Color(0, 0, 0));
    }
};

class DataVisualization {
private:
    bool running = true;
    void CommonView();
    void StaticArray();
    void DynamicArray();
    void LinkedList();
    void Stack();
    void Queue();
    /* manipulate:
        initialize
        add
        delete
        update
        search data
    */
public:
    void run();
};

void DataVisualization::CommonView() {
    float windowsizex = sf::VideoMode::getDesktopMode().width - 20;
    float windowsizey = sf::VideoMode::getDesktopMode().height - 80;
    sf::RenderWindow window(sf::VideoMode(windowsizex, windowsizey, 30), "SFML works!", sf::Style::Default);
    window.setPosition(sf::Vector2i(0, 0));
    // window.setFramerateLimit(60);
    // ::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Green);
    sf::Vector2f rectanglePosition(600, 350);

    rect.setPosition(rectanglePosition);
    rect.setSize(sf::Vector2f(100, 100));
    
    float xAcceleration = 0.0001;
    float yAcceleration = 0.0001;
    float xVelocity = 0.1;
    float yVelocity = 0.1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        // physics
        if (rectanglePosition.x < 0 || rectanglePosition.x + rect.getSize().x > windowsizex) xVelocity *= -1, xAcceleration *= -1;
        if (rectanglePosition.y < 0 || rectanglePosition.y + rect.getSize().y > windowsizey) yVelocity *= -1, yAcceleration *= -1;

        xVelocity += xAcceleration;
        yVelocity += yAcceleration;
        rectanglePosition.x += xVelocity;
        rectanglePosition.y += yVelocity;
        rect.setPosition(rectanglePosition);

        // render
        window.clear();
        window.draw(rect);
        window.display();
    }
    return;
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80, 30), "Window");
    window.setPosition(sf::Vector2i(0, 0));

    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
void DataVisualization::StaticArray() {}
void DataVisualization::DynamicArray() {}
void DataVisualization::LinkedList() {}
void DataVisualization::Stack() {}
void DataVisualization::Queue() {}

void DataVisualization::run() {
    CommonView();
}