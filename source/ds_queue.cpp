#include <SFML/Graphics.hpp>
#include <fstream>
#include "ds_queue.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

StructQueue::StructQueue(VisualizationSettings* settings, bool active) 
    : StructDataStructure(settings, active)
{
    this->maxsize = 12;
    this->sizeNode = 32;
    this->diffx = 30;
    this->diffy = 5;
    this->distance = this->sizeNode + this->diffx;

    this->elements = std::vector<int>(maxsize, 0);
    listNode = std::vector<std::unique_ptr<Node>> (this->maxsize);
    for(auto &ptr : listNode)
        ptr = std::make_unique<CircleNode>(sf::Vector2f(0, 0), this->sizeNode, this->sizeText, this->thickness, "", this->font, this->theme->getNode());
    listArrow = std::vector<ArrowNode> (this->maxsize, ArrowNode(this->sizeNode, this->theme->getArrow()));
    if (this->active)
        turn_on();
}

StructQueue::~StructQueue()
{
}

void StructQueue::run(int manipulate, int way, std::string str1, std::string str2)
{
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
        if (way == 0) this->Peek_Front();
        if (way == 1) this->Peek_Back();
    }
    if (manipulate == 2) {
        this->Enqueue(string_to_int(str1));
    }
    if (manipulate == 3) {
        this->Dequeue();
    }

    this->updatePositionNode();
}

void StructQueue::Peek_Front()
{
    if (this->sizearray == 0)
        return;
    this->listNode[0]->setStatus(3);
}

void StructQueue::Peek_Back()
{
    if (this->sizearray == 0)
        return;
    this->listNode[this->sizearray - 1]->setStatus(3);
}

void StructQueue::Enqueue(int value)
{
    if (this->sizearray == this->maxsize)
    {
        std::cout << "This visual can't contains more than " << this->maxsize << " elements. ";
        std::cout << "Your manipulation is rejected\n";
        return;
    }
    this->elements[this->sizearray++] = value;
}

void StructQueue::Dequeue()
{
    if (this->sizearray == 0) {
        std::cout << "The stack has no elements. Do nothing\n";
        return;
    }
    for(int i = 1; i < this->sizearray; i++)
        this->elements[i - 1] = this->elements[i];
    sizearray--;
}

sf::Vector2i StructQueue::updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->sizearray; i++) {
        listNode[i]->update(mousePos, mouseType, keyboardType);
        if (listNode[i]->getStatus() == 2) 
            ret = sf::Vector2i(i, this->elements[i]);
    }
    return ret;
}

void StructQueue::updatePositionNode()
{
    sf::Vector2f velocity, coord;
    velocity.x = this->distance + this->sizeNode;
    velocity.y = this->diffy;

    coord.x = this->centerVisual.x - velocity.x / 2 * (this->sizearray - 1);
    coord.y = this->centerVisual.y - velocity.y / 2 * (this->sizearray - 1);

    for(int i = 0; i < this->sizearray; i++) {
        this->listNode[i]->setXY(coord.x, coord.y);
        if (i) {
            this->listArrow[i - 1].setPoint(coord - velocity, coord);
        }
        coord += velocity;
    }
}

void StructQueue::refreshrender()
{
    for(int i = 0; i < this->sizearray; i++) {
        this->listNode[i]->setWord(std::to_string(this->elements[i]));
    }
}
void StructQueue::render()
{
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < this->sizearray; i++)
        listNode[i]->render(window);
    for(int i = 0; i < this->sizearray - 1; i++)
        listArrow[i].render(window);
}