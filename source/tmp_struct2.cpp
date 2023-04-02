#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <unistd.h>
#include <windows.h>
using namespace std;

struct ViewSquaNode {
    sf::Vector2f coord;
    int length = 10;
    sf::Color Vcolor;
    sf::RectangleShape shape;
    ViewSquaNode(int _x = 0, int _y = 0, int _l = 10) {
        coord.x = _x;
        coord.y = _y;
        length = _l;
    }
    void setup() {
        shape = sf::RectangleShape(sf::Vector2f(length, length));
        shape.setFillColor(Vcolor);
        shape.setOutlineThickness(5);
        shape.setOutlineColor(sf::Color(0, 0, 0));
    }
};

struct ViewNode {
    sf::Vector2f coord;
    int radius = 10;
    sf::Color Vcolor;
    sf::CircleShape shape;
    ViewNode(int _x = 0, int _y = 0, int _r = 10) {
        coord.x = _x;
        coord.y = _y;
        radius = _r;
    }
    void setup() {
        shape = sf::CircleShape(radius);
        shape.setFillColor(Vcolor);
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
    sf::Vector2f windowsize = sf::Vector2f(sf::VideoMode::getDesktopMode().width - 20,
                              sf::VideoMode::getDesktopMode().height - 80);
    sf::RenderWindow window(sf::VideoMode(windowsize.x, windowsize.y, 30), "SFML works!", sf::Style::Default);
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

    // debug
    window.close();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        // physics
        if (rectanglePosition.x < 0 || rectanglePosition.x + rect.getSize().x > windowsize.x) xVelocity *= -1, xAcceleration *= -1;
        if (rectanglePosition.y < 0 || rectanglePosition.y + rect.getSize().y > windowsize.y) yVelocity *= -1, yAcceleration *= -1;

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

    //text
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80, 30), "Window");
    window.setPosition(sf::Vector2i(0, 0));

    sf::Font open_font;
    if (!open_font.loadFromFile("./dat/roboto/Roboto-Black.ttf"))
    {
        cout << "ERROR";
        return;
    }
    sf::Text my_text;
    my_text.setFont(open_font);
    my_text.setString("HENOWORLD");
    my_text.setCharacterSize(24);
    my_text.setFillColor(sf::Color::Green);
    my_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        //render
        window.clear();
        window.draw(my_text);
        window.display();
    }

    return;

    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80, 30), "Window");
    window.setPosition(sf::Vector2i(0, 0));

    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
}
void DataVisualization::StaticArray() {}
void DataVisualization::DynamicArray() {}
void DataVisualization::LinkedList() {}
void DataVisualization::Stack() {}
void DataVisualization::Queue() {}

void DataVisualization::run() {
    CommonView();
}