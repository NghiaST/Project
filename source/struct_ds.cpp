#include <SFML/Graphics.hpp>
#include <fstream>
#include <algorithm>
#include "struct_ds.hpp"

StructDataStructure::StructDataStructure(sf::RenderWindow* window, PublicThemes* theme, bool active) 
{
    // window
    this->window = window;
    this->theme = theme;
    this->active = active;

    // font
    if (!this->font.loadFromFile("dat/arial_bold.ttf")) {
        std::cout << "Error Load Font haha\n";
    }

    // point
    this->centerVisual = sf::Vector2f(this->window->getSize().x / 2, 150);

    // check which manipulate is activating
    this->type1 = -1;
    this->type2 = -1;

    // list
    this->maxsize = 12;
    this->sizearray = 0;
    this->elements = std::vector<int>(maxsize, 0);
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

// Insert
void StructDataStructure::Insert_First(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't Insert new elements\n";
        return;
    }
    for(int i = sizearray - 1; i >= 0; i--) {
        elements[i + 1] = elements[i];
    }
    elements[0] = value;
    sizearray++;
}
void StructDataStructure::Insert_Last(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't Insert new elements\n";
        return;
    }
    elements[sizearray++] = value;
}
void StructDataStructure::Insert_Manual(int pos, int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't Insert new elements\n";
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
    std::rotate(elements.begin(), elements.begin() + 1, elements.begin() + sizearray);
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
    std::rotate(elements.begin() + pos, elements.begin() + pos + 1, elements.begin() + sizearray);
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
int StructDataStructure::Search(int value) 
{
    for(int i = 0; i < sizearray; i++)
    {
        if (this->elements[i] == value)
        {
            std::cout << "Find value at element " << i << '\n';
            return i;
        }
    }
    std::cout << "Can't find value\n";
    return -1;
}

void StructDataStructure::turn_on()
{
    this->active = true;
    this->run(0, 1, "", ""); // Initialize_Random
}

void StructDataStructure::turn_off()
{
    this->active = false;
}

const bool &StructDataStructure::isActive() const
{
    return this->active;
}