#include <SFML/Graphics.hpp>
#include <iostream>
#include "staticarray.hpp"
#include "struct_support.hpp"

StructStaticArray::StructStaticArray(sf::RenderWindow* window, bool active) 
{
    this->window = window;
    this->type1 = NONE;
    this->type2 = -1;
    this->active = active;
    if (!this->font.loadFromFile("dat/roboto/Roboto-Black.ttf")) {
        std::cout << "Error Load Font\n";
    }
    staticarr = new ViewSquareNode[maxsize] ();
    Initialize_Random();
}

StructStaticArray::~StructStaticArray()
{
    delete[] staticarr;
}

// Initialize
void StructStaticArray::Initialize_Empty() 
{
    this->sizearray = 0;
    this->refreshrender();
}
void StructStaticArray::Initialize_Random() 
{
    this->sizearray = Rand(0, this->maxsize);
    for(int i = 0; i < this->sizearray; i++) arr[i] = Rand(0, 99);
    this->refreshrender();
}
void StructStaticArray::Initialize_UserDefinedList() 
{
    // haven't know
    this->sizearray = Rand(0, this->maxsize);
    for(int i = 0; i < this->sizearray; i++) arr[i] = Rand(0, 99);
    this->refreshrender();
}
void StructStaticArray::Initialize_ExternalFile() 
{
    // haven't know
    std::ifstream file("fileinput.txt");
    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return;
    }
    std::string content;
    std::string line;

    while (std::getline(file, line))
    {
        content += line;
    }
    std::cout << "Debug External file\n";

    this->sizearray = Rand(0, this->maxsize);
    for(int i = 0; i < this->sizearray; i++) arr[i] = Rand(0, 99);
    this->refreshrender();
}
void StructStaticArray::Initialize(int way) 
{
    if (way == 0) {
        this->Initialize_Empty();
    }
    if (way == 1) {
        this->Initialize_Random();
    }
    if (way == 2) {
        this->Initialize_UserDefinedList();
    }
    if (way == 3) {
        this->Initialize_ExternalFile();
    }
}

// Add
void StructStaticArray::Add_FromTheFirst() 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    for(int i = sizearray - 1; i >= 0; i--) {
        arr[i + 1] = arr[i];
    }
    arr[0] = Rand(0, 99);
    sizearray++;
}
void StructStaticArray::Add_FromTheLast() 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    arr[sizearray++] = Rand(0, 99);
}
void StructStaticArray::Add_FromTheMiddle() 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    int pos = Rand(0, sizearray);
    for(int i = sizearray - 1; i >= pos; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos] = Rand(0, 99);
    sizearray++;
}
void StructStaticArray::Add(int way) 
{
    if (way == 0) this->Add_FromTheFirst();
    if (way == 1) this->Add_FromTheLast();
    if (way == 2) this->Add_FromTheMiddle();
    refreshrender();
}

// Delete
void StructStaticArray::Del_AtTheFirst()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    for(int i = 1; i < sizearray; i++)
        this->arr[i - 1] = this->arr[i];
    sizearray--;
}
void StructStaticArray::Del_AtTheLast()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    sizearray--;
}
void StructStaticArray::Del_AtTheMiddle()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    int pos = Rand(0, sizearray - 1);
    for(int i = pos + 1; i < sizearray; i++)
        this->arr[i - 1] = this->arr[i];
    sizearray--;
}
void StructStaticArray::Delete(int way) 
{
    if (way == 0) this->Del_AtTheFirst();
    if (way == 1) this->Del_AtTheLast();
    if (way == 2) this->Del_AtTheMiddle();
    refreshrender();
}

// Update
void StructStaticArray::Update() 
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't update elements\n";
        return;
    }
    int pos = Rand(0, sizearray - 1);
    this->arr[pos] = Rand(0, 99);
}
void StructStaticArray::Update(int way) 
{
    if (way == 0) {
        this->Update();
    }
    refreshrender();
}

// Search
void StructStaticArray::Search() 
{
    bool found = false;
    int val = Rand(0, 99);
    for(int i = 0; i < sizearray; i++)
    {
        if (this->arr[i] == val)
        {
            // Debug
            std::cout << "Find value at element " << i << '\n';
            found = true;
            break;
        }
    }
    if (found == false)
    {
        std::cout << "Can't find value\n";
    }
}
void StructStaticArray::Search(int way) 
{
    if (way == 0) {
        this->Search();
    }
    refreshrender();
}

void StructStaticArray::refreshrender() {
    sf::Vector2f coord = sf::Vector2f(250, 100);
    sf::Vector2f velocity = sf::Vector2f(52, 0);
    for(int i = 0; i < sizearray; i++) {
        staticarr[i].initialize(font, coord.x, coord.y, velocity.x - 2, std::to_string(arr[i]));
        coord += velocity;
    }
    for(int i = sizearray; i < maxsize; i++) {
        staticarr[i].initialize(font, coord.x, coord.y, velocity.x - 2, "");
        coord += velocity;
    }
}

void StructStaticArray::turn_off() {
    this->active = false;
}

void StructStaticArray::turn_on() {
    if (this->isActive()) return;
    this->active = true;
    this->Initialize_Random();
}

void StructStaticArray::run(int manipulate, int way) {
    if (!this->active) return;
    if (manipulate == -1) return;
    if (manipulate == 0) this->Initialize(way);
    if (manipulate == 1) this->Add(way);
    if (manipulate == 2) this->Delete(way);
    if (manipulate == 3) this->Update(way);
    if (manipulate == 4) this->Search(way);
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