#include "data_visualization.hpp"

int main()
{
    DataVisualization* NewVisual = new DataVisualization();
    NewVisual->run();
    delete NewVisual;
}
/* 
categories:
    void StaticArray();
    void DynamicArray();
    void LinkedList(); // simply, doubly, circular
    void Stack();
    void Queue();

manipulations:
    initialize
    add
    delete
    update
    search data
*/
/*
#include <SFML/Graphics.hpp>
#include "data_visualization.hpp"
#include "button.hpp"

int main()
{
    sf::Font font;
    Button xyz = Button(10, 10, 10, 10, &font, 1, 1, "ww", 12, ElementColor(sf::Color(255, 192, 203)), ElementColor(sf::Color::Green), ElementColor(sf::Color::Yellow), ElementColor(sf::Color::Blue), ElementColor(sf::Color::Blue));

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
        xyz.render(&window);
        window.display();
    }

    return 0;
}*/