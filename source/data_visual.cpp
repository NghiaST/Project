#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <vector>

#include "data_visual.hpp"
#include "struct_support.hpp"
#include "graphics_func.hpp"

// Initializations
void DataVisualization::InitWindow() 
{
    sf::Vector2f windowsize = sf::Vector2f(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80);
    this->window = new sf::RenderWindow(sf::VideoMode(windowsize.x, windowsize.y, 30), "Le Huu Nghia 22125064 - Data Visualizations", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(0, 0));
    // this->window->setFramerateLimit(60);
    // ::ShowWindow(this->window->getSystemHandle(), SW_MAXIMIZE);
}

void DataVisualization::InitStates()
{
    this->states.push(new State(this->window));
}

void DataVisualization::Initialize()
{
    this->InitWindow();
    this->InitStates();
    page_present = STATIC_ARRAY;
    stat = new StructStaticArray(window, true);
}

void DataVisualization::StaticArray() {
    int sizearray = 10;
    ViewSquareNode *staticarr = new ViewSquareNode[sizearray] ();

    sf::Vector2f coord = sf::Vector2f(250, 200);
    sf::Vector2f velocity = sf::Vector2f(32, 0);

    for(int i = 0; i < sizearray; i++) {
        staticarr[i].initialize(coord.x, coord.y, 30, inttochar(i));
        coord += velocity;
    }
    addwhitescreen(*this->window);
    for(int i = 0; i < sizearray; i++) {
        staticarr[i].print(window);
    }
}

void DataVisualization::DynamicArray() {}
void DataVisualization::LinkedList() {}
void DataVisualization::Stack() {}
void DataVisualization::Queue() {}

//// Initializations functions

// Constructors/Destructors
DataVisualization::DataVisualization()
{
    Initialize();
}

DataVisualization::~DataVisualization()
{
    delete this->window;
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
    if (stat != nullptr)
        delete stat;
}

int cnt;
// Functions
void DataVisualization::processEvents()
{
    while (this->window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) this->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window->close();
        // std::cout << "Events " << ++cnt << '\n';
    }
}

void DataVisualization::update()
{   
    if (!window->isOpen()) return;
    if (!this->states.empty()) {
        // Code here
        if (this->states.top()->listbutton[iSTATIC].isPressed()) {
            stat->run();
        }
        if (this->states.top()->listbutton[iINIT].isPressed()) {
            stat->Initialize();
        }

        this->states.top()->update();

        if (this->states.top()->getQuit())
        {
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->window->close();
    }
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    this->window->clear(sf::Color(235, 235, 235));
    
    this->stat->print();
    
    if (!this->states.empty())
        this->states.top()->render();
    this->window->display();

}

void DataVisualization::run()
{
    while (this->window->isOpen()) {
        processEvents();
        update();
        render();
    }
}