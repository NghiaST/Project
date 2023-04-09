#include <SFML/Graphics.hpp>
#include <fstream>
#include "struct_ds.hpp"

StructDataStructure::StructDataStructure(sf::RenderWindow* window, bool active) 
{
    // window
    this->window = window;
    this->active = active;

    // font
    if (!this->font.loadFromFile("dat/arial_bold.ttf")) {
        std::cout << "Error Load Font\n";
    }

    // point
    this->centerVisual = sf::Vector2f(this->window->getSize().x / 2, 130);

    // check which manipulate is activating
    this->type1 = -1;
    this->type2 = -1;

    // list
    this->maxsize = 12;
    this->sizearray = 0;
    this->elements = std::vector<int>(maxsize, 0);

    Color = std::vector<TripleColor>(5, TripleColor());
    Color[0] = TripleColor(sf::Color::White);
    Color[1] = TripleColor(sf::Color::Cyan);
    Color[2] = TripleColor(sf::Color::Green);
    Color[3] = TripleColor(sf::Color::Yellow);
    Color[4] = TripleColor(sf::Color::Red);
    
    Initialize_Random();
}

StructDataStructure::~StructDataStructure()
{
}

// Initialize
void StructDataStructure::Initialize_Empty() 
{
    this->sizearray = 0;
}
void StructDataStructure::Initialize_Random()
{
    this->sizearray = Rand(1, this->maxsize);
    for(int i = 0; i < this->sizearray; i++) elements[i] = Rand(0, 999);
}
void StructDataStructure::Initialize_Manual(std::vector<int> arr) 
{
    this->sizearray = (arr.size() < this->maxsize ? arr.size() : this->maxsize);
    for(int i = 0; i < this->sizearray; i++) 
        this->elements[i] = arr[i];
}
void StructDataStructure::Initialize_ExternalFile(std::string filename) 
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
void StructDataStructure::Add_First(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    for(int i = sizearray - 1; i >= 0; i--) {
        elements[i + 1] = elements[i];
    }
    elements[0] = value;
    sizearray++;
}
void StructDataStructure::Add_Last(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    elements[sizearray++] = value;
}
void StructDataStructure::Add_Manual(int pos, int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't add new elements\n";
        return;
    }
    sizearray++;
    for(int i = sizearray - 2; i >= pos; i--) {
        elements[i + 1] = elements[i];
    }
    elements[pos] = value;
}

// Delete
void StructDataStructure::Del_First()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    for(int i = 1; i < sizearray; i++)
        this->elements[i - 1] = this->elements[i];
    sizearray--;
}
void StructDataStructure::Del_Last()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    sizearray--;
}
void StructDataStructure::Del_Manual(int pos)
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    for(int i = pos + 1; i < sizearray; i++)
        this->elements[i - 1] = this->elements[i];
    sizearray--;
}

// Update
void StructDataStructure::Update(int pos, int value) 
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't update elements\n";
        return;
    }
    if (pos < 0) pos = 0;
    if (pos >= maxsize) pos = maxsize - 1;
    this->elements[pos] = value;
}

// Search
void StructDataStructure::Search(int value) 
{
    bool found = false;
    for(int i = 0; i < sizearray; i++)
    {
        if (this->elements[i] == value)
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

void StructDataStructure::turn_off() {
    this->active = false;
}
void StructDataStructure::turn_on() {
    if (this->isActive()) return;
    this->active = true;
    this->Initialize_Random();
}

const bool &StructDataStructure::isActive() const
{
    return this->active;
}
/*
void StructDataStructure::run(int manipulate, int way, std::string str1, std::string str2) {
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
}*/
/*
void StructDataStructure::refreshrender()
{
    sf::Vector2f coord;
    coord.x = centerVisual.x - this->distance / 2 * sizearray;
    coord.y = centerVisual.y;
    sf::Vector2f coord = sf::Vector2f(250, 100);
    sf::Vector2f velocity = sf::Vector2f(52, 0);
    for(int i = 0; i < sizearray; i++) {
        staticelements[i].setWord(std::to_string(this->elements[i]));
    }
    for(int i = sizearray; i < maxsize; i++) {
        staticelements[i].setWord("");
    }
}
void StructDataStructure::render() {
    if (this->active == false) return;
    this->refreshrender();
    for(int i = 0; i < maxsize; i++)
        staticelements[i].render(window);
}*/