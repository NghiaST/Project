#include <SFML/Graphics.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include "staticarray.hpp"
#include "graphics_func.hpp"
#include "struct_support.hpp"

//void StructStaticArray::Initialize() {}
void StructStaticArray::Add() {}
void StructStaticArray::Delete() {}
void StructStaticArray::Update() {}
void StructStaticArray::SearchData() {}

StructStaticArray::StructStaticArray(sf::RenderWindow* window) {
    this->window = window;
    type = INIT;
    active = false;
    Initialize();
}

void StructStaticArray::Initialize() {
    sizearray = 5;
    staticarr = new ViewSquareNode[maxsize] ();
    for(int i = 0; i < sizearray; i++) arr[i] = Rand(0, 99);

    sf::Vector2f coord = sf::Vector2f(250, 200);
    sf::Vector2f velocity = sf::Vector2f(32, 0);

    for(int i = 0; i < sizearray; i++) {
        staticarr[i].initialize(coord.x, coord.y, 30, inttochar(arr[i]));
        coord += velocity;
    }
    for(int i = sizearray; i < maxsize; i++) {
        staticarr[i].initialize(coord.x, coord.y, 30, "");
        coord += velocity;
    }
}

void StructStaticArray::print() {
    for(int i = 0; i < maxsize; i++)
        staticarr[i].print(window);
}