#include <SFML/Graphics.hpp>
#include <fstream>
#include "ds_linkedlist.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

StructLinkedList::StructLinkedList(sf::RenderWindow* window, bool active) 
    : StructDataStructure(window, active)
{
    this->speed = 3;
    this->maxsize = 14;
    this->sizeNode = 30;
    this->distance = 48;
    this->diffy = 10;

    this->sizearray = 0;
    this->elements = std::vector<int>(maxsize, 0);
    this->printElements = this->elements;

    for(int i = 0; i < this->maxsize; i++) {
        listNode.push_back(CircleNode(0, 0, this->sizeNode / 2, &this->font, "", 13, this->listColor));
    }
    for(int i = 0; i < this->maxsize; i++) {
        listArrow.push_back(ArrowNode(this->sizeNode));
    }
    listPoint = std::vector<sf::Vector2f>(this->maxsize, sf::Vector2f(0, 0));
    nodeAnimation = std::vector<Manipulate_Animation_ArrayNode> (this->maxsize, Manipulate_Animation_ArrayNode());
    for(int i = 0; i < this->maxsize; i++) {
        nodeAnimation.push_back(Manipulate_Animation_ArrayNode());
        arrowAnimation.push_back(Manipulate_Animation_ArrayArrow());
    }

    if (this->active)
        turn_on();
}
StructLinkedList::~StructLinkedList()
{
}

void StructLinkedList::turn_on()
{
    this->active = true;
    this->run(0, 1, "", ""); // Initialize_Random
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

void StructLinkedList::run(int manipulate, int way, std::string str1, std::string str2)
{
    double time = clock.getElapsedTime().asSeconds() * speed;
    if (this->running == true && (time > this->totaltime || manipulate != -1))
        stopAnimation();
    // this->Manipulate = manipulate;
    // this->Way = way;

    /* debug */ 
    if (this->active == false) {
        std::cout << "Error StructLinkedList::run\n";
        exit(2);
    }
    if (manipulate == -1) return;

    this->preSize = this->sizearray;
    // this->printElements = elements;
    this->Str1 = str1;
    this->Str2 = str2;
    
    clock.restart();

    if (manipulate == 0) {
        this->Animation_Initialize(way);
    }
    if (manipulate == 1) {
        if (way == 0) this->Animation_Insert_First();
        if (way == 1) this->Animation_Insert_Last();
        if (way == 2) this->Animation_Insert_Manual();
    }
    if (manipulate == 2) {
        if (way == 0) this->Animation_Del_First();
        if (way == 1) this->Animation_Del_Last();
        if (way == 2) this->Animation_Del_Manual();
    }
    if (manipulate == 3) {
        Animation_Update();
    }
    if (manipulate == 4) {
        Animation_Search();
    }
}

void StructLinkedList::activeAnimation()
{
    this->running = true;
    clock.restart();
}

void StructLinkedList::stopAnimation()
{
    this->running = false;
    this->totaltime = 0;
    for(int i = 0; i < this->count_nodePrint; i++) {
        listNode[i].stopAnimation();
        listArrow[i].setStatusAnimation(0);

        nodeAnimation[i].clearStep();
        arrowAnimation[i].clearStep();
    }
    this->count_nodePrint = this->sizearray;
    this->printElements = this->elements;
    refreshNode();
}

sf::Vector2i StructLinkedList::updateKBM(sf::Vector2f mousePos, int mouseType, int keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->sizearray; i++) {
        listNode[i].update(mousePos, mouseType, keyboardType);
        if (listNode[i].getRunning() == false && listNode[i].getStatus() == 2) 
            ret = sf::Vector2i(i, this->elements[i]);
    }
    return ret;
}

void StructLinkedList::refreshNode()
{
    std::vector<sf::Vector2f> listP = this->getPosition(this->sizearray);
    for(int i = 0; i < this->sizearray; i++) {
        this->listNode[i].setXY(listP[i]);
        if (i)
            this->listArrow[i - 1].setPoint(listP[i - 1], listP[i]);
        this->listNode[i].setWord(std::to_string(this->elements[i]));
    }
}

void StructLinkedList::refreshrender()
{
    double time = clock.getElapsedTime().asSeconds() * speed;
    if (this->running == true && time > this->totaltime)
        stopAnimation();

    if (this->running == true)
    {
        for(int i = 0; i < this->count_nodePrint; i++)
        {
            nodeAnimation[i].runTime(time);
            if (i < count_nodePrint - 1) 
                arrowAnimation[i].runTime(time);
        }
    }
}

void StructLinkedList::render()
{
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < count_nodePrint - 1; i++) {
        listArrow[i].render(window);
    }
    for(int i = 0; i < count_nodePrint; i++)
        listNode[i].render(window);
}

void StructLinkedList::Animation_Insert_First()
{
    Insert_First(string_to_int(this->Str2));
    this->printElements = this->elements;
    if (this->preSize == this->maxsize)
    {
        std::cout << "Error. The size of linked list is maximum. Can't add\n";
        // Manipulate = -1;
        // Way = -1;
        return;
    }
    count_nodePrint = preSize + 1;
    activeAnimation();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pEnd = getPosition(preSize + 1);

    sf::Vector2f newPosition;
    if (this->preSize == 0)
        newPosition = pEnd[0] + sf::Vector2f(0, 200);
    else 
        newPosition = pStart[0] + sf::Vector2f(0, 200);
    pStart.insert(pStart.begin(), newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], false);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false);
        }
        else if (i > 0) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
        }
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == 0)
        {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_SKIP);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else if (i == 1)
        {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].addStep(NOD_SKIP);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].addStep(NOD_NORMAL);
            nodeAnimation[i].addStep(NOD_SKIP);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }

    for(int i = 0; i < count_nodePrint - 1; i++)
    {
        if (i == 0) {
            arrowAnimation[i].addStep(AR_NOPE);
            arrowAnimation[i].addStep(AR_CREATE);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
        else {
            arrowAnimation[i].skipMultiStep(2);
            arrowAnimation[i].addStep(AR_NORMAL, pEnd[i], pEnd[i + 1]);
        }
    }
    this->totaltime = nodeAnimation[0].getTotaltime();
}
void StructLinkedList::Animation_Insert_Last()
{
    Insert_Last(string_to_int(Str2));
    this->printElements = this->elements;
    if (this->preSize == this->maxsize)
    {
        std::cout << "Error. The size of linked list is maximum. Can't add\n";
        // Manipulate = -1;
        // Way = -1;
        return;
    }
    count_nodePrint = preSize + 1;
    activeAnimation();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pEnd = getPosition(preSize + 1);

    sf::Vector2f newPosition;
    if (this->preSize == 0)
        newPosition = pEnd.back() + sf::Vector2f(0, 200);
    else 
        newPosition = pStart.back() + sf::Vector2f(0, 200);
    pStart.push_back(newPosition);

    // build step
    int pos = count_nodePrint - 1;
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < pos - 1) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
        }
        else if (i == pos - 1) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false);
        }
        else if (i == pos) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], false);
        }
    }

    // setup step to step
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos) {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_SKIP);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else if (i == pos - 1) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].addStep(NOD_SKIP);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].addStep(NOD_NORMAL);
            nodeAnimation[i].addStep(NOD_SKIP);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }

    for(int i = 0; i < count_nodePrint - 1; i++)
    {
        if (i == pos - 1) {
            arrowAnimation[i].addStep(AR_NOPE);
            arrowAnimation[i].addStep(AR_CREATE);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
        else {
            arrowAnimation[i].addStep(AR_NORMAL);
            arrowAnimation[i].addStep(AR_SKIP);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }   
    }
    this->totaltime = nodeAnimation[0].getTotaltime();
}
void StructLinkedList::Animation_Insert_Manual()
{
    int pos = string_to_int(this->Str1);
    if (pos == 0) return void(Animation_Insert_First());
    if (pos == this->sizearray) return void(Animation_Insert_Last());

    if (pos >= this->sizearray) {
        std::cout << "Error. The position must be in range [1, N - 1]\n";
        return;
    }
    Insert_Manual(pos, string_to_int(this->Str2));
    this->printElements = this->elements;
    if (this->preSize == this->maxsize)
    {
        std::cout << "Error. The size of linked list is maximum. Can't add\n";
        // Manipulate = -1;
        // Way = -1;
        return;
    }
    clock.restart();
    this->running = true;
    count_nodePrint = preSize + 1;

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pEnd = getPosition(preSize + 1);

    sf::Vector2f newPosition;
    if (this->preSize == 0)
        newPosition = pEnd.back() + sf::Vector2f(0, 200);
    else 
        newPosition = pStart[pos] + sf::Vector2f(0, 200);
    pStart.insert(pStart.begin() + pos, newPosition);

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == pos - 1) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 2], true);
        }
        else if (i == pos) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], false);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
        }
    }

    for(int ipos = 0; ipos < pos - 1; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);

                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_COLOR_TO);
            }
            else {
                nodeAnimation[i].skipMultiStep(2);
                arrowAnimation[i].skipMultiStep(2);
            }
        }
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos - 1)
        {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(1);

            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_COLOR_TO);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
            arrowAnimation[i].skipMultiStep(2);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos) {
            nodeAnimation[i].addStep(NOD_NOPE);
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else if (i == pos + 1) {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].skipMultiStep(3);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].skipMultiStep(4);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }
    for(int i = 0; i < count_nodePrint - 1; i++)
    {
        if (i == pos - 1) {
            arrowAnimation[i].skipMultiStep(3);
            arrowAnimation[i].addStep(AR_MOVE, pStart[i], pStart[i + 1]);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
        else if (i == pos) {
            arrowAnimation[i].skipMultiStep(2);
            arrowAnimation[i].addStep(AR_CREATE);
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
        else {
            arrowAnimation[i].skipMultiStep(4);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
    }
    this->totaltime = nodeAnimation[0].getTotaltime() + Delay * 10;
}

void StructLinkedList::Animation_Del_First()
{
    this->printElements = this->elements;
    Del_First();
    if (this->preSize == 0)
    {
        std::cout << "Error. The size of linked list is none. Can't remove\n";
        // Manipulate = -1;
        // Way = -1;
        return;
    }
    
    count_nodePrint = preSize;
    activeAnimation();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);
    std::vector<sf::Vector2f> pEnd = getPosition(count_nodePrint - 1);

    sf::Vector2f newPosition = pStart[0];
    pEnd.insert(pEnd.begin(), newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == 0) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else if (i == 1) {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }

    for(int i = 0; i < count_nodePrint - 1; i++)
    {
        if (i == 0) {
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_COLOR_TO);
            arrowAnimation[i].addStep(AR_DEL);
            arrowAnimation[i].skipMultiStep(1);
        }
        else {
            arrowAnimation[i].skipMultiStep(3);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
    }
    this->totaltime = nodeAnimation[0].getTotaltime();
}
void StructLinkedList::Animation_Del_Last()
{
    this->printElements = this->elements;
    Del_Last();
    if (this->preSize == 0)
    {
        std::cout << "Error. The size of linked list is none. Can't remove\n";
        // Manipulate = -1;
        // Way = -1;
        return;
    }

    count_nodePrint = preSize;
    activeAnimation();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);
    std::vector<sf::Vector2f> pEnd = getPosition(count_nodePrint - 1);

    sf::Vector2f newPosition = pStart.back();
    pEnd.push_back(newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
    }

    int pos = count_nodePrint - 1;
    for(int ipos = 0; ipos < pos; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);

                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_COLOR_TO);
            } 
            else if (i == ipos - 1) {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].addStep(NOD_UNSHOW);

                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_COLOR_TO);
            }
            else {
                nodeAnimation[i].skipMultiStep(2);
                arrowAnimation[i].skipMultiStep(2);
            }
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos) {
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else if (i == pos - 1) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }
    for(int i = 0; i < count_nodePrint - 1; i++)
    {
        if (i == pos - 1) {
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_DEL);
            arrowAnimation[i].skipMultiStep(2);
        }
        else {
            arrowAnimation[i].skipMultiStep(3);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
    }
    this->totaltime = nodeAnimation[0].getTotaltime();
}
void StructLinkedList::Animation_Del_Manual()
{
    this->printElements = this->elements;
    int pos = string_to_int(this->Str1);
    if (pos <= 0) return void(Animation_Del_First());
    if (pos >= this->sizearray) return void(Animation_Del_Last());

    Del_Manual(pos);
    clock.restart();
    this->running = true;
    count_nodePrint = preSize;

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);
    std::vector<sf::Vector2f> pEnd = getPosition(count_nodePrint - 1);

    sf::Vector2f newPosition = pStart[pos] + sf::Vector2f(0, 200);
    pEnd.insert(pEnd.begin() + pos, newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
    }

    for(int ipos = 0; ipos < pos - 1; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);

                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_COLOR_TO);
            }
            else {
                nodeAnimation[i].skipMultiStep(2);
                arrowAnimation[i].skipMultiStep(2);
            }
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos - 1) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(1);

            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_COLOR_TO);
        } 
        else if (i == pos) {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_ACTIVE);

            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_COLOR_TO);
        }
        else if (i == pos + 1) {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_SOLVE);

            arrowAnimation[i].skipMultiStep(2);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
            arrowAnimation[i].skipMultiStep(2);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos) {
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }
    for(int i = 0; i < count_nodePrint - 1; i++)
    {
        if (i == pos) {
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pStart[i + 1]);
            arrowAnimation[i].addStep(AR_DEL);
            arrowAnimation[i].skipMultiStep(2);
        }
        else if (i == pos - 1) {
            arrowAnimation[i].addStep(AR_MOVE, pStart[i], pEnd[i + 1]);
            arrowAnimation[i].addStep(AR_MOVE, pStart[i], pStart[i + 2]);
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 2]);
        }
        else {
            arrowAnimation[i].skipMultiStep(3);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
    }
    this->totaltime = nodeAnimation[0].getTotaltime();
}

void StructLinkedList::Animation_Initialize(int way)
{
    if (way == 0) this->Initialize_Empty();
    if (way == 1) this->Initialize_Random();
    if (way == 2) this->Initialize_Manual(string_to_array(this->Str1));
    if (way == 3) this->Initialize_ExternalFile(this->Str2);
    this->printElements = this->elements;

    clock.restart();
    this->running = true;
    this->count_nodePrint = this->sizearray;

    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], false);
        nodeAnimation[i].addStep(NOD_APPEAR);
        if (i < count_nodePrint - 1) {
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false);
            arrowAnimation[i].addStep(AR_CREATE);
        }
    }
    this->totaltime = nodeAnimation[0].getTotaltime();
}

void StructLinkedList::Animation_Update()
{
    this->printElements = this->elements;
    int pos = string_to_int(this->Str1);
    int value = string_to_int(this->Str2);
    if (pos < 0) pos = 0; 
    if (pos >= this->sizearray) pos = this->sizearray - 1;
    this->Update(pos, value);
    count_nodePrint = this->sizearray;
    activeAnimation();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
    }

    for(int ipos = 0; ipos < pos; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);

                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_COLOR_TO);
            }
            else {
                nodeAnimation[i].skipMultiStep(2);
                arrowAnimation[i].skipMultiStep(2);
            }
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos)
        {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[pos].setWord(value);
            nodeAnimation[i].addStep(NOD_APPEAR);

            arrowAnimation[i].skipMultiStep(3);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
            arrowAnimation[i].skipMultiStep(3);
        }
    }

    this->totaltime = nodeAnimation[0].getTotaltime();
}

void StructLinkedList::Animation_Search()
{
    this->printElements = this->elements;
    int pos = Search(string_to_int(this->Str1));
    if (pos == -1) pos = this->sizearray;
    count_nodePrint = this->sizearray;
    activeAnimation();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true);
    }

    for(int ipos = 0; ipos < pos; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);

                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_COLOR_TO);
            }
            else {
                nodeAnimation[i].skipMultiStep(2);
                arrowAnimation[i].skipMultiStep(2);
            }
        }
    }
    if (pos != count_nodePrint)
    {
        for(int istep = 0; istep < 9; istep++)
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == pos)
            {
                nodeAnimation[i].addStep(istep & 1 ? NOD_DEL : NOD_APPEAR);
                arrowAnimation[i].skipMultiStep(1);
            }
            else {
                nodeAnimation[i].skipMultiStep(1);
                arrowAnimation[i].skipMultiStep(1);
            }
        }
    }

    this->totaltime = nodeAnimation[0].getTotaltime();
}
