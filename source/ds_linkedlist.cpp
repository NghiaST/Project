#include <SFML/Graphics.hpp>
#include <fstream>
#include "ds_linkedlist.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

StructLinkedList::StructLinkedList(sf::RenderWindow* window, bool active) 
    : StructDataStructure(window, active)
{
    this->maxsize = 11;
    this->sizeNode = 32;
    this->distance = 64;
    this->diffy = 5;
    for(int i = 0; i < this->maxsize; i++) {
        listNode.push_back(CircleNode(0, 0, this->sizeNode / 2, &this->font, "", 13, this->listColor));
    }
    for(int i = 0; i < this->maxsize; i++) {
        listArrow.push_back(ArrowNode(this->sizeNode));
    }
    this->updatePositionNode();
    this->refreshrender();
}

StructLinkedList::~StructLinkedList()
{
}

void StructLinkedList::run(int manipulate, int way, std::string str1, std::string str2) {
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

sf::Vector2i StructLinkedList::update(sf::Vector2f mousePos, int mouseType, int keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->sizearray; i++) {
        listNode[i].update(mousePos, mouseType, keyboardType);
        if (listNode[i].getStatus() == 2) 
            ret = sf::Vector2i(i, this->elements[i]);
    }
    this->updatePositionNode();
    return ret;
}

void StructLinkedList::updatePositionNode()
{
    sf::Vector2f velocity, coord;
    velocity.x = this->distance + this->sizeNode;
    velocity.y = this->diffy;

    coord.x = this->centerVisual.x - velocity.x / 2 * (this->sizearray - 1);
    coord.y = this->centerVisual.y - velocity.y / 2 * (this->sizearray - 1);

    for(int i = 0; i < this->sizearray; i++) {
        this->listNode[i].setXY(coord.x, coord.y);

        if (i) {
            this->listArrow[i - 1].setPoint(coord - velocity, coord);
        }

        coord += velocity;
    }
}

void StructLinkedList::refreshrender()
{
    for(int i = 0; i < this->sizearray; i++) {
        this->listNode[i].setWord(std::to_string(this->elements[i]));
    }
}
void StructLinkedList::render()
{
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < this->sizearray; i++)
        listNode[i].render(window);
    for(int i = 0; i < this->sizearray - 1; i++)
        listArrow[i].render(window);
}