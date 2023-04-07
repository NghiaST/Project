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
    this->states = new State(this->window);
}

//// Initializations functions

// Constructors/Destructors
DataVisualization::DataVisualization()
{
    this->running = true;
    this->InitWindow();
    this->InitStates();
    this->page_present = STATIC_ARRAY;
    this->StaticArray  = new StructStaticArray(window, true);
    this->DynamicArray = new StructStaticArray(window, false);
    this->LinkedList   = new StructStaticArray(window, false);
    this->Stack        = new StructStaticArray(window, false);
    this->Queue        = new StructStaticArray(window, false);
}

DataVisualization::~DataVisualization()
{
    delete this->window;
    delete this->states;
    delete this->StaticArray;
    delete this->DynamicArray;
    delete this->LinkedList;
    delete this->Stack;
    delete this->Queue;
}

int cnt;
// Functions
void DataVisualization::processEvents()
{
    keyboardType = 0;
    while (this->window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) this->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window->close();
        if (sfEvent.type == sf::Event::TextEntered)
            keyboardType = sfEvent.text.unicode;
    }
}

void DataVisualization::update()
{   
    if (!window->isOpen()) return;
    sf::Vector2i typeButton = this->states->update(keyboardType);
    // Code here
    if (typeButton.x != -1) {
        std::cout << "Press " << typeButton.x << ' ' << typeButton.y << '\n';
        if (typeButton.x < 5) {
            if (page_present == STATIC_ARRAY)  StaticArray->turn_off();
            if (page_present == DYNAMIC_ARRAY) DynamicArray->turn_off();
            if (page_present == LINKED_LIST)   LinkedList->turn_off();
            if (page_present == STACK)         Stack->turn_off();
            if (page_present == QUEUE)         Queue->turn_off();

            page_present = static_cast<PAGE>(typeButton.x);
            
            if (page_present == STATIC_ARRAY)  StaticArray->turn_on();
            if (page_present == DYNAMIC_ARRAY) DynamicArray->turn_on();
            if (page_present == LINKED_LIST)   LinkedList->turn_on();
            if (page_present == STACK)         Stack->turn_on();
            if (page_present == QUEUE)         Queue->turn_on();
        }
        if (typeButton.x > 4) {
            if (page_present == STATIC_ARRAY)  StaticArray->run(typeButton.x - 5, typeButton.y);
            if (page_present == DYNAMIC_ARRAY) DynamicArray->run(typeButton.x - 5, typeButton.y);
            if (page_present == LINKED_LIST)   LinkedList->run(typeButton.x - 5, typeButton.y);
            if (page_present == STACK)         Stack->run(typeButton.x - 5, typeButton.y);
            if (page_present == QUEUE)         Queue->run(typeButton.x - 5, typeButton.y);
        }
    }
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    this->window->clear(sf::Color(235, 235, 235));

    if (page_present == STATIC_ARRAY)  StaticArray->print();
    if (page_present == DYNAMIC_ARRAY) DynamicArray->print();
    if (page_present == LINKED_LIST)   LinkedList->print();
    if (page_present == STACK)         Stack->print();
    if (page_present == QUEUE)         Queue->print();

    this->states->render();
    this->window->display();
}

void DataVisualization::run()
{
    std::cout << "D1\n";
    while (this->window->isOpen()) {
        processEvents();
        update();
        render();
    }
}