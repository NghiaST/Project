#include <SFML/Graphics.hpp>
#include <fstream>
#include "ds_linkedlist.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

StructLinkedList::StructLinkedList(sf::RenderWindow* window, bool active) 
    : StructDataStructure(window, active)
{
    this->speed = 1;
    this->maxsize = 14;
    this->sizeNode = 30;
    this->distance = 50;
    this->diffy = 2;

    this->sizearray = 0;
    this->elements = std::vector<int>(maxsize, 0);
    this->preElements = std::vector<int>(maxsize, 0);

    for(int i = 0; i < this->maxsize; i++) {
        listNode.push_back(CircleNode(0, 0, this->sizeNode / 2, &this->font, "", 13, this->listColor));
    }
    for(int i = 0; i < this->maxsize; i++) {
        listArrow.push_back(ArrowNode(this->sizeNode));
    }
    listPoint = std::vector<sf::Vector2f>(this->maxsize, sf::Vector2f(0, 0));
    
    this->updatePositionNode();
    this->refreshrender();
}

StructLinkedList::~StructLinkedList()
{
}

void StructLinkedList::turn_on()
{
    this->active = true;
    this->run(0, 1, "", ""); // Initialize_Random
    this->updatePositionNode();
}

void StructLinkedList::run(int manipulate, int way, std::string str1, std::string str2)
{ 
    // debug
    if (manipulate != -1 && this->Manipulate != -1)
    {
        this->running = false;
        for(int i = 0; i < this->count_nodePrint; i++) {
            listNode[i].stopAnimation();
            listArrow[i].setStatus(0);
        }
        Manipulate = -1;
        Way = -1;
        count_nodePrint = this->sizearray;
        updatePositionNode();
    }

    // >= 5 from animation
    if (manipulate == 1 && way == 1) // Insert_Last
    {
        this->Manipulate = manipulate;
        this->Way = way;
        this->Val = string_to_int(str2);
    }

    /* debug */ 
    if (this->active == false) exit(2);
    if (manipulate == -1) return;

    preSize = this->sizearray;
    preElements = elements;

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

    if (manipulate != 1 || way != 1)
        count_nodePrint = this->sizearray;
    updatePositionNode();
}

std::vector<sf::Vector2f> StructLinkedList::getPosition(int size)
{
    std::vector<sf::Vector2f> listP;

    sf::Vector2f velocity, coord;
    velocity.x = this->distance + this->sizeNode;
    velocity.y = this->diffy;

    coord.x = this->centerVisual.x - velocity.x / 2 * (size - 1);
    coord.y = this->centerVisual.y - velocity.y / 2 * (size - 1);

    for(int i = 0; i < size; i++) {
        listP.push_back(coord);
        coord += velocity;
    }
    return listP;
}

void StructLinkedList::Animation_Insert_Last()
{
    double time = clock.getElapsedTime().asSeconds() * speed;
    if (this->running == true && time > this->Time)
    {
        this->running = false;
        for(int i = 0; i < this->count_nodePrint; i++) {
            listNode[i].stopAnimation();
            listArrow[i].setStatus(0);
        }
        
        Manipulate = -1;
        Way = -1;
        count_nodePrint = this->sizearray;
        updatePositionNode();
        return;
    }
    if (this->running == false && this->Manipulate == -1)
        return;
    if (this->preSize == 0)
    {
        std::cout << "Error. This code hasn't add the last without any node\n";
        Manipulate = -1;
        Way = -1;
        return;
    }
    if (this->preSize == this->maxsize)
    {
        std::cout << "Error. The size of linked list is maximum. Can't add\n";
        Manipulate = -1;
        Way = -1;
        return;
    }
    if (this->running == false)
    {
        clock.restart();
        time = 0;
        this->running = true;
        this->Time = 1.2;
        count_nodePrint = preSize + 1;
    }
    
    // setup position
    std::vector<std::vector<float>> arr = std::vector<std::vector<float>> (20, std::vector<float>(20, 0));
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pEnd = getPosition(preSize + 1);

    sf::Vector2f velocity;
    velocity.x = this->distance + this->sizeNode;
    velocity.y = this->diffy;

    sf::Vector2f newPosition = pStart.back() + sf::Vector2f(0, 100);
    pStart.push_back(newPosition);
    for(int i = 0; i < preSize + 1; i++)
    {
        listNode[i].setXY(pStart[i]);
        if (i < count_nodePrint - 2) {
            listNode[i].prepareAnimation(pEnd[i], 1, 2);
        }
        else if (i == count_nodePrint - 2) {
            listNode[i].prepareAnimation(pEnd[i], 1, 1);
        }
        else {
            listNode[i].prepareAnimation(pEnd[i], 1, 3);
        }
        if (i < preSize) {
            listArrow[i].setAllPoint(pStart[i], pStart[i + 1], pEnd[i], pEnd[i + 1]);
            listArrow[i].setStatus(0);
        }
        if (i == preSize - 1) {
            listArrow[i].setStatus(1);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < count_nodePrint - 1)
            listNode[i].updateAnimation(time);
        else 
            listNode[i].updateAnimation(time);
        // listNode[i].renderAnimation(window, 2, time / 3);
        if (i != count_nodePrint - 1) 
            listArrow[i].setTime(time);
        // listArrow[i].renderStatusTime(window, 2, time / 3);
    }
}

sf::Vector2i StructLinkedList::update(sf::Vector2f mousePos, int mouseType, int keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->sizearray; i++) {
        listNode[i].update(mousePos, mouseType, keyboardType);
        if (listNode[i].getStatus() == 2) 
            ret = sf::Vector2i(i, this->elements[i]);
    }
    return ret;
}

void StructLinkedList::updateAnimation()
{
    if (this->Manipulate == 1 && this->Way == 1)
        Animation_Insert_Last();
}

void StructLinkedList::updatePositionNode()
{
    sf::Vector2f velocity, coord;
    velocity.x = this->distance + this->sizeNode;
    velocity.y = this->diffy;

    coord.x = this->centerVisual.x - velocity.x / 2 * (this->sizearray - 1);
    coord.y = this->centerVisual.y - velocity.y / 2 * (this->sizearray - 1);

    for(int i = 0; i < this->sizearray; i++) {
        this->listNode[i].setXY(coord);
        listPoint[i] = coord;

        if (i) {
            this->listArrow[i - 1].setPoint(coord - velocity, coord);
        }

        coord += velocity;
    }
}

void StructLinkedList::refreshrender()
{
    for(int i = 0; i < this->count_nodePrint; i++) {
        this->listNode[i].setWord(std::to_string(this->elements[i]));
    }
}

void StructLinkedList::render()
{
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < count_nodePrint; i++)
        listNode[i].render(window);
    for(int i = 0; i < count_nodePrint - 1; i++) {
        listArrow[i].render(window);
    }
}