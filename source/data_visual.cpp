#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "data_visual.hpp"
#include "struct_support.hpp"
#include "graphics_func.hpp"
#include "staticarray.hpp"
using namespace std;

// Private Functions
void DataVisualization::InitWindow() {
    sf::Vector2f windowsize = sf::Vector2f(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80);
    this->window = new sf::RenderWindow(sf::VideoMode(windowsize.x, windowsize.y, 30), "Le Huu Nghia 22125064 - Data Visualizations", sf::Style::Default);
    this->window.setPosition(sf::Vector2i(0, 0));
    // window.setFramerateLimit(60);
    // ::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
}

void DataVisualization::StaticArray() {
    /*int sizearray = 10;
    ViewSquareNode *staticarr = new ViewSquareNode[sizearray] ();

    sf::Vector2f coord = sf::Vector2f(250, 200);
    sf::Vector2f velocity = sf::Vector2f(32, 0);

    for(int i = 0; i < sizearray; i++) {
        staticarr[i].initialize(coord.x, coord.y, 30, inttochar(i));
        coord += velocity;
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();
        addwhitescreen(window);
        for(int i = 0; i < sizearray; i++) {
            staticarr[i].print(window);
        }
        window.display();
    }
    std::cout << "DEBUG static array 2\n";*/
}

void DataVisualization::DynamicArray() {}
void DataVisualization::LinkedList() {}
void DataVisualization::Stack() {}
void DataVisualization::Queue() {}

//// Initializations functions

// Constructors/Destructors
DataVisualization::DataVisualization()
{
}

DataVisualization::~DataVisualization()
{
}

// Functions
void DataVisualization::updateSFMLEvents()
{
}

void DataVisualization::update()
{
}

void DataVisualization::render()
{
}

void DataVisualization::run() 
{
    InitWindow();
    // CommonView();
    // StaticArray();
    StructStaticArray stat(window);
    stat.run();
}