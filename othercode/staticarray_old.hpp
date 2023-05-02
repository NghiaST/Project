#include <SFML/Graphics.hpp>
#include <fstream>
#include "tmpstaticarray.hpp"
#include "struct_support.hpp"
#include "struct_visual.hpp"

StructStaticArray2::StructStaticArray2(sf::RenderWindow* window, bool active) 
    : StructDataStructure(window, active)
{
    for(int i = 0; i < this->maxsize; i++) {
        listNode[i]->push_back(RectangleNode(0, 0, this->sizeNode, this->sizeNode, this->font "", 15, this->Color[0], this->Color[1], this->Color[2], this->Color[3], this->Color[4]));
    }
    this->updatePositionNode();
    this->refreshrender();
}

StructStaticArray2::~StructStaticArray2()
{
}

void StructStaticArray2::run(int manipulate, int way, std::vector<std::string> vecStr) {
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

    this->updatePositionNode();
}

sf::Vector2i StructStaticArray2::update(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->maxsize; i++) {
        listNode[i]->updateKBM(mousePos, mouseType, keyboardType);
        if (i < this->sizearray && listNode[i]->getStatus() == 2) 
            ret = sf::Vector2i(i, this->elements[i]);
    }
    return ret;
}

void StructStaticArray2::updatePositionNode()
{
    sf::Vector2f velocity, coord;
    velocity.x = this->distance + this->sizeNode;
    velocity.y = this->diffy;

    coord.x = this->centerVisual.x - velocity.x / 2 * (maxsize - 1);
    coord.y = this->centerVisual.y - velocity.y / 2 * (maxsize - 1);


    for(int i = 0; i < this->maxsize; i++) {
        this->listNode[i]->setXY(coord.x, coord.y);
        coord += velocity;
    }
}

void StructStaticArray2::refreshrender()
{
    for(int i = 0; i < this->maxsize; i++) {
        if (i < sizearray)
            this->listNode[i]->setWord(std::to_string(this->elements[i]));
        else
            this->listNode[i]->setWord("");
    }
}
void StructStaticArray2::render()
{
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < maxsize; i++)
        listNode[i]->render(window);
}