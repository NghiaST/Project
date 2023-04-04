#include <SFML/Graphics.hpp>
#include <iostream>
#include "staticarray.hpp"
#include "struct_support.hpp"

void StructStaticArray::Update() {}
void StructStaticArray::Search() {}

StructStaticArray::StructStaticArray(sf::RenderWindow* window, bool active) {
    this->window = window;
    this->type = INIT;
    this->active = active;
    if (!this->font.loadFromFile("dat/roboto/Roboto-Black.ttf")) {
        std::cout << "Error Load Font\n";
    }
    staticarr = new ViewSquareNode[maxsize] ();
    Initialize();
}

StructStaticArray::~StructStaticArray()
{
    delete[] staticarr;
}

void StructStaticArray::Initialize() {
    this->sizearray = 8;
    for(int i = 0; i < this->sizearray; i++) arr[i] = Rand(0, 99);

    sf::Vector2f coord = sf::Vector2f(250, 200);
    sf::Vector2f velocity = sf::Vector2f(42, 0);
    this->refreshrender();
}

void StructStaticArray::refreshrender() {
    sf::Vector2f coord = sf::Vector2f(250, 200);
    sf::Vector2f velocity = sf::Vector2f(42, 0);
    for(int i = 0; i < sizearray; i++) {
        staticarr[i].initialize(font, coord.x, coord.y, 40, std::to_string(arr[i]));
        coord += velocity;
    }
    for(int i = sizearray; i < maxsize; i++) {
        staticarr[i].initialize(font, coord.x, coord.y, 40, "");
        coord += velocity;
    }
}

void StructStaticArray::turn_off() {
    this->active = false;
}

void StructStaticArray::turn_on() {
    if (this->isActive()) return;
    this->active = true;
    Initialize();
}

void StructStaticArray::run(/*int manipulate, int way*/) {
    /*if (!this->active) return;
    if (manipulate == -1) return;
    if (manipulate == 0) this->Initialize(way);
    if (manipulate == 1) this->Add(way);
    if (manipulate == 2) this->Delete(way);
    if (manipulate == 3) this->Update(way);
    if (manipulate == 4) this->Search(way);*/
}

void StructStaticArray::Add() {
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    arr[sizearray++] = Rand(0, 99);
    refreshrender();
}

void StructStaticArray::Delete() {
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    sizearray--;
    refreshrender();
}

void StructStaticArray::print() {
    if (!this->isActive()) return;
    for(int i = 0; i < maxsize; i++)
        staticarr[i].print(window);
}

const bool &StructStaticArray::isActive() const
{
    return this->active;
}