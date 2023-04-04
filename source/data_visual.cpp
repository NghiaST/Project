#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <vector>

#include "data_visual.hpp"
#include "struct_support.hpp"
#include "graphics_func.hpp"
#include "staticarray.hpp"
#include "state.hpp"
#include "button.hpp"

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

void DataVisualization::InitButton()
{
    listbutton.push_back(Button(100, 200, 250, 250, &this->font, "Hello", sf::Color::Blue, sf::Color::Green, sf::Color::Yellow));
}

void DataVisualization::Initialize()
{
    if (!this->font.loadFromFile("dat/roboto/Roboto-Black.ttf")) {
        std::cout << "Error Load Font\n";
    }

    this->InitWindow();
    this->InitStates();
    this->InitButton();
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
}

void DataVisualization::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

// Functions
void DataVisualization::processEvents()
{
    while (this->window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) this->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window->close();
    }
}

void DataVisualization::update()
{   
    if (!window->isOpen()) return;
    this->updateMousePositions();
    for(Button& but : listbutton) {
        but.update(this->mousePosView);
    }
    /*if (!this->states.empty()) {
        this->states.top()->update();

        if (this->states.top()->getQuit())
        {
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->window->close();
    }*/
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    this->window->clear(sf::Color(235, 235, 235));
    for(Button but : listbutton) {
        but.render(window);
    }

    /*if (!this->states.empty())
        this->states.top()->render();*/
    // Render items
    /*for(int i = 0; i < maxsize; i++) {
        staticarr[i].print(window);
    }*/
    this->window->display();

}

void DataVisualization::run() 
{
    //Initialize();
    while (this->window->isOpen()) {
        processEvents();
        update();
        render();
    }
    /*StructStaticArray stat(window);
    stat.run();*/
}