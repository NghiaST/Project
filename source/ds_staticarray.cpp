#include <SFML/Graphics.hpp>
#include <fstream>
#include "ds_staticarray.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

StructStaticArray::StructStaticArray(sf::RenderWindow* window, bool active) 
    : StructDataStructure(window, active)
{    
    this->maxsize = 12;
    this->sizeNode = 50;
    this->distance = 4;
    this->diffy = 2;

    for(int i = 0; i < this->maxsize; i++) {
        listNode.push_back(RectangleNode(0, 0, this->sizeNode, this->sizeNode, &this->font, "", 15, this->listColor));
    }
    this->updatePositionNode();
    this->refreshrender();
}

StructStaticArray::~StructStaticArray()
{
}

void StructStaticArray::run(int manipulate, int way, std::string str1, std::string str2) {
    if (!this->active) 
        exit(2);
    if (manipulate == -1) ;
    if (manipulate == 0) {
        if (way == 0) this->Initialize_Empty();
        if (way == 1) this->Initialize_Random();
        if (way == 2) this->Initialize_Manual(string_to_array(str1));
        if (way == 3) this->Initialize_ExternalFile(str2);
    }
    if (manipulate == 1) {
        if (way == 0) this->Insert_First(string_to_int(str2));
        if (way == 1) this->Insert_Last(string_to_int(str2));
        if (way == 2) this->Insert_Manual(string_to_int(str1), string_to_int(str2));
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

    this->updatePositionNode();
}

sf::Vector2i StructStaticArray::update(sf::Vector2f mousePos, int mouseType, int keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->maxsize; i++) {
        listNode[i].update(mousePos, mouseType, keyboardType);
        if (i < this->sizearray && listNode[i].getStatus() == 2) 
            ret = sf::Vector2i(i, this->elements[i]);
    }
    this->updatePositionNode();
    return ret;
}

void StructStaticArray::updatePositionNode()
{
    sf::Vector2f velocity, coord;
    velocity.x = this->distance + this->sizeNode;
    velocity.y = this->diffy;

    coord.x = this->centerVisual.x - velocity.x / 2 * (this->maxsize - 1);
    coord.y = this->centerVisual.y - velocity.y / 2 * (this->maxsize - 1);


    for(int i = 0; i < this->maxsize; i++) {
        this->listNode[i].setXY(coord.x, coord.y);
        coord += velocity;
    }
}

void StructStaticArray::refreshrender()
{
    for(int i = 0; i < this->maxsize; i++) {
        if (i < sizearray)
            this->listNode[i].setWord(std::to_string(this->elements[i]));
        else
            this->listNode[i].setWord("");
    }
}
void StructStaticArray::render()
{
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < maxsize; i++)
        listNode[i].render(window);
}