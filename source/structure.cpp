#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <unistd.h>
#include <windows.h>
#include "structure.hpp"
#include "struct_support.hpp"
#include "graphics_func.hpp"
using namespace std;

//void DataVisualization::StaticArray() {}
void DataVisualization::DynamicArray() {}
void DataVisualization::LinkedList() {}
void DataVisualization::Stack() {}
void DataVisualization::Queue() {}

void DataVisualization::Open() {
    sf::Vector2f windowsize = sf::Vector2f(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80);
    window.create(sf::VideoMode(windowsize.x, windowsize.y, 30), "SFML works!", sf::Style::Default);
    window.setPosition(sf::Vector2i(0, 0));
    // window.setFramerateLimit(60);
    // ::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
}
void DataVisualization::CommonView() {
    ViewSquareNode node(200, 101, 40, "1gab");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        //node.coord.y = rand() % 700;
        //node.setup();
        //Sleep(400);
        //render
        // window.clear();
        // window.draw(node.shape);
        // window.draw(my_text);
        // window.draw(node.text);
        window.clear();
        node.print(window);
        window.display();
    }
}

void DataVisualization::run() {
    Open();
    // CommonView();
    StaticArray();
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
    std::cout << "DEBUG static array 2\n";
}