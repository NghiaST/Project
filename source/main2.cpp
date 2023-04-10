#include <SFML/Graphics.hpp>
#include <iostream>
#include "arrow.hpp"
#include "node.hpp"
#include "ds_stack.hpp"

const float NODE_SIZE = 20.0f; // Node size in pixels
const float VELOCITY = 100.0f; // Velocity of the nodes in pixels per second

int main()
{
    // Create a window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 2.0;
    sf::RenderWindow window(sf::VideoMode(1000, 700, 30), "Le Huu Nghia 22125064 - Data Visualizations", sf::Style::Default, settings);

    sf::Font font;
    font.loadFromFile("dat/arial.ttf");

    CircleNode Node(100, 100, 20, &font, "a", 15, {});
    CircleNode Node2(200, 500, 20, &font, "a", 15, {});
    ArrowNode arrow(20 * 2, Node.getXY(), Node2.getXY());

    // Create two nodes
    int status = 1;

    sf::Vector2f pos1(200, 000);
    sf::Vector2f pos2(200, 600);
    sf::Vector2f velocity1(30, 10); // pixel/s
    sf::Vector2f velocity2(24, -12);

    // Get the initial time
    sf::Clock clock;
    sf::Time elapsedTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the elapsed time since the last frame

        // Update the positions of the nodes based on velocity and elapsed time
        float seconds = clock.getElapsedTime().asSeconds();
        float distance = VELOCITY * seconds;
        sf::Vector2f point1;
        sf::Vector2f point2;
        point1.x = pos1.x + velocity1.x * seconds;
        point1.y = pos1.y + velocity1.y * seconds;

        point2.x = pos2.x + velocity2.x * seconds;
        point2.y = pos2.y + velocity2.y * seconds;

        Node.setXY(point1.x, point1.y);
        Node2.setXY(point2.x, point2.y);
        arrow.setPoint(Node.getXY(), Node2.getXY());
        if (seconds > 1.1) {
            pos1 = point1;
            pos2 = point2;
            clock.restart();
            status = (status + 1) % 5;
        }

        // Clear the window
        arrow.setStatus(status);
        arrow.setTime(seconds);
        window.clear(sf::Color::White);

        Node.render(&window);
        Node2.render(&window);
        arrow.render(&window);
        //arrow.renderStatusTime(&window, status, seconds);

        // Display the window
        window.display();

    }

    return 0;
}
