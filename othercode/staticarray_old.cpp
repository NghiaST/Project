#include <SFML/Graphics.hpp>
#include <fstream>
#include "staticarray.hpp"
#include "struct_support.hpp"

StructStaticArray::StructStaticArray(sf::RenderWindow* window, bool active) 
{
    this->window = window;
    this->centerVisual = sf::Vector2f(this->window->getSize().x / 2, 300);
    if (!this->font.loadFromFile("dat/roboto/Roboto-Regular.ttf")) {
        std::cout << "Error Load Font\n";
    }

    this->maxsize = 12;

    this->type1 = -1;
    this->type2 = -1;
    this->active = active;
    arr.resize(maxsize);

    sf::Vector2f coord = sf::Vector2f(250, 100);
    sf::Vector2f velocity = sf::Vector2f(52, 0);

    TripleColor idleColor(sf::Color::White);
    TripleColor hoverColor(sf::Color::Cyan);
    TripleColor activeColor(sf::Color::Green);

    for(int i = 0; i < maxsize; i++) {
        staticarr.push_back(RectangleNode(coord.x, coord.y, velocity.x - 2, velocity.x - 2, this->font "", 15, idleColor, hoverColor, activeColor, TripleColor(), TripleColor()));
        coord += velocity;
    }
    Initialize_Random();
    this->refreshrender();
}

StructStaticArray::~StructStaticArray()
{
}

// Initialize
void StructStaticArray::Initialize_Empty() 
{
    this->sizearray = 0;
}
void StructStaticArray::Initialize_Random()
{
    this->sizearray = Rand(1, this->maxsize);
    for(int i = 0; i < this->sizearray; i++) arr[i] = Rand(0, 999);
}
void StructStaticArray::Initialize_Manual(std::vector<int> arr) 
{
    sizearray = (arr.size() < this->maxsize ? arr.size() : this->maxsize);
    for(int i = 0; i < this->sizearray; i++) 
        this->arr[i] = arr[i];
}
void StructStaticArray::Initialize_ExternalFile(std::string filename) 
{
    // haven't know
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return;
    }
    std::string content;
    std::string line;

    while (std::getline(file, line))
    {
        content += line + ' ';
    }
    file.close();
    // debug
    std::cout << "Debug External file\n";

    this->Initialize_Manual(string_to_array(content));
}

// Add
void StructStaticArray::Add_First(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    for(int i = sizearray - 1; i >= 0; i--) {
        arr[i + 1] = arr[i];
    }
    arr[0] = value;
    sizearray++;
}
void StructStaticArray::Add_Last(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    arr[sizearray++] = value;
}
void StructStaticArray::Add_Manual(int pos, int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    sizearray++;
    for(int i = sizearray - 2; i >= pos; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos] = value;
}

// Delete
void StructStaticArray::Del_First()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    for(int i = 1; i < sizearray; i++)
        this->arr[i - 1] = this->arr[i];
    sizearray--;
}
void StructStaticArray::Del_Last()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    sizearray--;
}
void StructStaticArray::Del_Manual(int pos)
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    for(int i = pos + 1; i < sizearray; i++)
        this->arr[i - 1] = this->arr[i];
    sizearray--;
}

// Update
void StructStaticArray::Update(int pos, int value) 
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't update elements\n";
        return;
    }
    if (pos < 0) pos = 0;
    if (pos >= maxsize) pos = maxsize - 1;
    this->arr[pos] = value;
}

// Search
void StructStaticArray::Search(int value) 
{
    bool found = false;
    for(int i = 0; i < sizearray; i++)
    {
        if (this->arr[i] == value)
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

void StructStaticArray::turn_off() {
    this->active = false;
}

const bool &StructStaticArray::isActive() const
{
    return this->active;
}

void StructStaticArray::run(int manipulate, int way, std::string str1, std::string str2) {
    if (!this->active) 
        exit(2);
    if (manipulate == -1) return;
    if (manipulate == 0) {
        if (way == 0) this->Initialize_Empty();
        if (way == 1) this->Initialize_Random();
        if (way == 2) this->Initialize_Manual(string_to_array(str1));
        if (way == 3) this->Initialize_ExternalFile(str2);
    }
    if (manipulate == 1) {
        if (way == 0) this->Add_First(string_to_int(str2));
        if (way == 1) this->Add_Last(string_to_int(str2));
        if (way == 2) this->Add_Manual(string_to_int(str1), string_to_int(str2));
    }
    if (manipulate == 2) {
        if (way == 0) this->Del_First();
        if (way == 1) this->Del_Last();
        if (way == 2) this->Del_Manual(string_to_int(str1));
    }
    if (manipulate == 3) {
        this->Update(string_to_int(str1), string_to_int(str2));
    }
    if (manipulate == 4) {
        this->Search(string_to_int(str1));
    }
}

sf::Vector2i StructStaticArray::update(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->maxsize; i++) {
        staticarr[i].update(mousePos, mouseType, keyboardType);
        if (i < this->sizearray && staticarr[i].getStatus() == 2) 
            ret = sf::Vector2i(i, this->arr[i]);
    }
    return ret;
}

void StructStaticArray::refreshrender()
{
    sf::Vector2f coord = sf::Vector2f(250, 100);
    sf::Vector2f velocity = sf::Vector2f(52, 0);
    for(int i = 0; i < sizearray; i++) {
        staticarr[i].setWord(std::to_string(this->arr[i]));
    }
    for(int i = sizearray; i < maxsize; i++) {
        staticarr[i].setWord("");
    }
}
void StructStaticArray::render() {
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < maxsize; i++)
        staticarr[i].render(window);
}