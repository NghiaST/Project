#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

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
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        
    }


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