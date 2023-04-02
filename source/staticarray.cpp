#include <SFML/Graphics.hpp>
#include <iostream>
#include "staticarray.hpp"
#include "graphics_func.hpp"
#include "struct_support.hpp"

//void StructStaticArray::Initialize() {}
void StructStaticArray::Add() {}
void StructStaticArray::Delete() {}
void StructStaticArray::Update() {}
void StructStaticArray::SearchData() {}

StructStaticArray::StructStaticArray(sf::RenderWindow& _window) {
    //window = &_window;
    window.setActive(true);
}

void StructStaticArray::run() {
    Initialize();
}

void StructStaticArray::Initialize() {
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