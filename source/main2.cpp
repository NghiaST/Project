#include <SFML/Graphics.hpp>
#include <cmath>
#include "support_function.hpp"
#include "node.hpp"
#include "triplecolor.hpp"
#include "struct_ds.hpp"
#include "ds_linkedlist.hpp"
#include "arrow.hpp"

void drawArrow(sf::RenderWindow& window, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Color color)
{
    // Calculate the direction vector and length
    sf::Vector2f direction = endPoint - startPoint;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Create the arrow shape
    sf::ConvexShape arrow;
    arrow.setPointCount(3); // Triangle shape for arrowhead
    arrow.setPoint(0, sf::Vector2f(length - 10.f, 0.f));
    arrow.setPoint(1, sf::Vector2f(length, 5.f));
    arrow.setPoint(2, sf::Vector2f(length, -5.f));
    arrow.setFillColor(color);
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(1.f);

    // Set the position and rotation of the arrow
    arrow.setPosition(startPoint);
    float angle = std::atan2(direction.y, direction.x) * 180.f / static_cast<float>(M_PI);
    arrow.setRotation(angle);

    // Draw the arrow to the window
    window.draw(arrow);
}

int main()
{
    // Create SFML window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Arrow Example");


    StructLinkedList* linkedlist = new StructLinkedList(&window, true);
    Arrow arrow;

    // Start and end points of the arrow
    sf::Vector2f startPoint(600.f, 300.f);
    sf::Vector2f endPoint(100.f, 500.f);
    // sf::Font font;
    // TripleColor Color();
    // CircleNode node(100, 100, 100, &font, "a", 10, Color, Color, Color, Color, Color);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw the arrow to the window
        arrow.setStartPoint(startPoint);
        arrow.setEndPoint(endPoint);
        arrow.render(&window);
        //drawArrow(window, startPoint, endPoint, sf::Color::Red);

        window.display();
    }

    return 0;
}/*


#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct Vertex {
    int x;
    int y;
    std::vector<int> edges; // Indices of vertices connected by edges
};

int main()
{
    // Create vertices of the graph
    std::vector<Vertex> vertices = {
        {100, 100, {1, 2, 3}},   // Vertex 0 with edges to vertices 1, 2, 3
        {200, 200, {0, 2}},      // Vertex 1 with edges to vertices 0, 2
        {300, 100, {0, 1}},      // Vertex 2 with edges to vertices 0, 1
        {400, 200, {0}}          // Vertex 3 with edge to vertex 0
    };

    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Edges", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw edges
        sf::VertexArray lines(sf::Lines);
        for (const Vertex& v : vertices) {
            int startX = v.x;
            int startY = v.y;
            for (int i : v.edges) {
                int endX = vertices[i].x;
                int endY = vertices[i].y;
                lines.append(sf::Vertex(sf::Vector2f(startX, startY), sf::Color::Black));
                lines.append(sf::Vertex(sf::Vector2f(endX, endY), sf::Color::Black));
            }
        }
        window.draw(lines);

        // Draw vertices
        for (const Vertex& v : vertices) {
            sf::CircleShape vertexShape(10);
            vertexShape.setPosition(v.x - 10, v.y - 10);
            vertexShape.setFillColor(sf::Color::Red);
            window.draw(vertexShape);
        }

        window.display();
    }

    return 0;
}
*/