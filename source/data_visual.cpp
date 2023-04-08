#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <vector>

#include "data_visual.hpp"
#include "struct_support.hpp"

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
    this->active = true;
    this->InitWindow();
    this->InitStates();
    this->page_present = PAGE_STATICARRAY;
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
    sf::Event sfEvent;
    int keyboard = 0, mouse = 0;
    while (this->window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) this->window->close();
        if (sfEvent.type == sf::Event::TextEntered)
            keyboard = sfEvent.text.unicode;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window->close();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouse = 1;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) mouse = 2;

    this->keyboardType = keyboard;
    switch (mouse)
    {
        case MSE_NONE : // none
            this->mouseType = 0;
            break;
        case MSE_LEFTCLICK : 
            if (this->mouseType == MSE_LEFTCLICK || this->mouseType == MSE_LEFTHOLD)
                this->mouseType = MSE_LEFTHOLD;
            else this->mouseType = MSE_LEFTCLICK;
            break;
        case MSE_RIGHTCLICK : 
            if (this->mouseType == MSE_RIGHTCLICK || this->mouseType == MSE_RIGHTHOLD)
                this->mouseType = MSE_RIGHTHOLD;
            else this->mouseType = MSE_RIGHTCLICK;
            break;
        default :
            this->mouseType = 0;
            break;
    }
}

void DataVisualization::update()
{   
    if (!window->isOpen()) return;
    sf::Vector2i typeButton = this->states->update(this->mouseType, this->keyboardType);
    // Code here
    if (typeButton.x != -1) {
        std::cout << "Press " << typeButton.x << ' ' << typeButton.y << '\n';
        if (typeButton.x < 5) {
            if (page_present == PAGE_STATICARRAY)  StaticArray->turn_off();
            if (page_present == PAGE_DYNAMICARRAY) DynamicArray->turn_off();
            if (page_present == PAGE_LINKEDLIST)   LinkedList->turn_off();
            if (page_present == PAGE_STACK)        Stack->turn_off();
            if (page_present == PAGE_QUEUE)        Queue->turn_off();

            page_present = static_cast<PAGE>(typeButton.x);
            
            if (page_present == PAGE_STATICARRAY)  StaticArray->turn_on();
            if (page_present == PAGE_DYNAMICARRAY) DynamicArray->turn_on();
            if (page_present == PAGE_LINKEDLIST)   LinkedList->turn_on();
            if (page_present == PAGE_STACK)        Stack->turn_on();
            if (page_present == PAGE_QUEUE)        Queue->turn_on();
        }
        if (typeButton.x > 4) {
            if (page_present == PAGE_STATICARRAY)  StaticArray->run(typeButton.x - 5, typeButton.y);
            if (page_present == PAGE_DYNAMICARRAY) DynamicArray->run(typeButton.x - 5, typeButton.y);
            if (page_present == PAGE_LINKEDLIST)   LinkedList->run(typeButton.x - 5, typeButton.y);
            if (page_present == PAGE_STACK)        Stack->run(typeButton.x - 5, typeButton.y);
            if (page_present == PAGE_QUEUE)        Queue->run(typeButton.x - 5, typeButton.y);
        }
    }
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    this->window->clear(sf::Color(235, 235, 235));

    if (page_present == PAGE_STATICARRAY)  StaticArray->render();
    if (page_present == PAGE_DYNAMICARRAY) DynamicArray->render();
    if (page_present == PAGE_LINKEDLIST)   LinkedList->render();
    if (page_present == PAGE_STACK)        Stack->render();
    if (page_present == PAGE_QUEUE)        Queue->render();

    this->states->render();
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