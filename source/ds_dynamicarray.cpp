#include "ds_dynamicarray.hpp"

StructDynamicArray::StructDynamicArray(VisualizationSettings* settings, bool active) 
    : StructDataStructure(settings, active)
{
    this->maxsize = 15;
    this->sizeText = 13;
    this->sizeNode = 40;
    this->diffx = 4;
    this->diffy = 0;
    this->distance = this->sizeNode + this->diffx;
    this->thickness = 3;

    this->elements = std::vector<int>(maxsize, 0);
    listNode = std::vector<std::unique_ptr<Node>> (this->maxsize * 2);
    for(auto &ptr : listNode)
        ptr = std::make_unique<RectangleNode>(sf::Vector2f(0, 0), this->sizeNode, this->sizeText, this->thickness, "", this->font, this->theme->getNode());
    listPoint = std::vector<sf::Vector2f> (this->maxsize, sf::Vector2f(0, 0));
    nodeAnimation = std::vector<Manipulate_Animation_ArrayNode> (this->maxsize * 2, Manipulate_Animation_ArrayNode());
    
    if (this->active)
        turn_on();
}
StructDynamicArray::~StructDynamicArray()
{
}

void StructDynamicArray::refreshAnimation()
{
    std::vector<sf::Vector2f> listP = this->getPosition(this->sizearray);
    count_nodePrint = this->sizearray;
    count_arrowPrint = 0;
    for(int i = 0; i < this->count_nodePrint; i++) {
        this->listNode[i]->setXY(listP[i]);
        this->listNode[i]->setWord(std::to_string(this->elements[i]));
    }
}
void StructDynamicArray::run(int manipulate, int way, std::vector<std::string> vecStr)
{
    if (manipulate == -1) return;
    if (this->running == true && manipulate != -1)
        stopAnimationDS();

    if (this->active == false) {
        std::cout << "Error StructLinkedList::run\n";
        exit(2);
    }

    this->preSize = this->sizearray;
    this->vecStr = vecStr;

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
        if (way == 0) this->Animation_Update();
        if (way == 1) this->Animation_Allocate();
    }
    if (manipulate == 4) {
        if (way == 0) this->Animation_Access();
        if (way == 1) this->Animation_Search();
    }
}

void StructDynamicArray::Allocate(int size, int value)
{
    sizearray = std::min(size, maxsize);
    for(int i = 0; i < sizearray; i++)
        elements[i] = value;
}

void StructDynamicArray::Animation_Initialize(int way)
{
    if (way == 0) this->Initialize_Empty();
    if (way == 1) this->Initialize_Random();
    if (way == 2) this->Initialize_Manual(string_to_array(vecStr[1]));
    if (way == 3) {
        if (this->Initialize_ExternalFile(vecStr[0]) == -1)
            return;
    }
    this->printElements = this->elements;

    count_nodePrint = sizearray;
    count_arrowPrint = 0;
    Manipulate = 0; subManipulate = way;
    startAnimationDS();

    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], false);
        nodeAnimation[i].addStep(NOD_APPEAR);
    }
    this->listStep = std::vector<int>{0};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructDynamicArray::Animation_Insert_First()
{
    if (Insert_First(string_to_int(vecStr[3])) == -1)
        return;
    int pos = 0;
    this->printElements = this->elements;
    count_nodePrint = preSize + sizearray;
    count_arrowPrint = 0;
    Manipulate = 1; subManipulate = 0;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pNext = getPosition(sizearray);
    for(sf::Vector2f &coord : pNext)
        coord.y += 200;
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < preSize) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i + 1], true);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pNext[i - preSize], "?", false);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
            nodeAnimation[i].skipMultiStep(2);
        else {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
    }
    listStep.push_back(0);
    listStep.push_back(0);
    
    for(int ipos = 0, ipos2 = 0; ipos < preSize; ipos++, ipos2++)
    {
        if (ipos2 == pos) 
        {
            for(int i = 0; i < count_nodePrint; i++)
            {
                if (i == ipos)
                {
                    nodeAnimation[i].addStep(NOD_SHOW);
                    nodeAnimation[i].skipMultiStep(1);
                }
                else if (i == preSize + ipos2)
                {
                    nodeAnimation[i].addStep(NOD_SOLVE);
                    nodeAnimation[i].addStep(NOD_UNSHOW);
                }
                else {
                    nodeAnimation[i].skipMultiStep(2);
                }
            }
            ipos2++;
            listStep.push_back(1);
            listStep.push_back(2);
        }
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == preSize + ipos2)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(printElements[i - preSize]);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(1);
        listStep.push_back(3);
        listStep.push_back(3);
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize + pos)
        {
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[i].setWord(printElements[i - preSize]);
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_UNSHOW);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
        }
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
        {
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i - preSize]);
        }
    }    
    
    listStep.push_back(4);
    listStep.push_back(4);
    listStep.push_back(4);
    listStep.push_back(5);
    listStep.push_back(6);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructDynamicArray::Animation_Insert_Last()
{
    if (Insert_Last(string_to_int(vecStr[3])) == -1)
        return;
    int pos = sizearray - 1;
    this->printElements = this->elements;
    count_nodePrint = preSize + sizearray;
    count_arrowPrint = 0;
    Manipulate = 1; subManipulate = 1;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pNext = getPosition(sizearray);
    for(sf::Vector2f &coord : pNext)
        coord.y += 200;
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < preSize) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pNext[i - preSize], "?", false);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
            nodeAnimation[i].skipMultiStep(2);
        else {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
    }
    listStep.push_back(0);
    listStep.push_back(0);
    
    for(int ipos = 0, ipos2 = 0; ipos < preSize; ipos++, ipos2++)
    {
        if (ipos2 == pos) 
        {
            for(int i = 0; i < count_nodePrint; i++)
            {
                if (i == ipos)
                {
                    nodeAnimation[i].addStep(NOD_SHOW);
                    nodeAnimation[i].skipMultiStep(1);
                }
                else if (i == preSize + ipos2)
                {
                    nodeAnimation[i].addStep(NOD_SHOW);
                    nodeAnimation[i].addStep(NOD_UNSHOW);
                }
                else {
                    nodeAnimation[i].skipMultiStep(2);
                }
            }
            ipos2++;
            listStep.push_back(1);
            listStep.push_back(2);
        }
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == preSize + ipos2)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(printElements[i - preSize]);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(1);
        listStep.push_back(3);
        listStep.push_back(3);
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize + pos)
        {
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[i].setWord(printElements[i - preSize]);
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_UNSHOW);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
        }
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
        {
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i - preSize]);
        }
    }    
    
    listStep.push_back(4);
    listStep.push_back(4);
    listStep.push_back(4);
    listStep.push_back(5);
    listStep.push_back(6);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructDynamicArray::Animation_Insert_Manual()
{
    int pos = string_to_int(vecStr[2]);
    if (pos == 0) return void(Animation_Insert_First());
    if (pos == this->sizearray) return void(Animation_Insert_Last());
    if (Insert_Manual(pos, string_to_int(vecStr[3])) == -1)
        return;
    this->printElements = this->elements;
    count_nodePrint = preSize + sizearray;
    count_arrowPrint = 0;
    Manipulate = 1; subManipulate = 2;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pNext = getPosition(sizearray);
    for(sf::Vector2f &coord : pNext)
        coord.y += 200;
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < pos) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        }
        else if (i < preSize) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i + 1], true);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pNext[i - preSize], "?", false);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
            nodeAnimation[i].skipMultiStep(2);
        else {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
    }
    listStep.push_back(0);
    listStep.push_back(0);
    
    for(int ipos = 0, ipos2 = 0; ipos < preSize; ipos++, ipos2++)
    {
        if (ipos2 == pos) 
        {
            for(int i = 0; i < count_nodePrint; i++)
            {
                if (i == ipos)
                {
                    nodeAnimation[i].addStep(NOD_SHOW);
                    nodeAnimation[i].skipMultiStep(1);
                }
                else if (i == preSize + ipos2)
                {
                    nodeAnimation[i].addStep(NOD_SOLVE);
                    nodeAnimation[i].addStep(NOD_UNSHOW);
                }
                else {
                    nodeAnimation[i].skipMultiStep(2);
                }
            }
            ipos2++;
            listStep.push_back(1);
            listStep.push_back(2);
        }
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == preSize + ipos2)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(printElements[i - preSize]);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(1);
        listStep.push_back(3);
        listStep.push_back(3);
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize + pos)
        {
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[i].setWord(printElements[i - preSize]);
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_UNSHOW);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
        }
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
        {
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i - preSize]);
        }
    }    
    
    listStep.push_back(4);
    listStep.push_back(4);
    listStep.push_back(4);
    listStep.push_back(5);
    listStep.push_back(6);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructDynamicArray::Animation_Del_First()
{
    this->printElements = this->elements;
    Del_First();
    int pos = 0;
    count_nodePrint = preSize + sizearray;
    count_arrowPrint = 0;
    Manipulate = 2; subManipulate = 0;
    startAnimationDS();

    if (preSize == 0)
    {
        listStep.push_back(0);
        this->totaltime = 0;
        this->step_total = 0;
        return;
    }

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pNext = getPosition(sizearray);
    for(sf::Vector2f &coord : pNext)
        coord.y += 200;
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < preSize) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pNext[i - preSize], "?", false);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
            nodeAnimation[i].skipMultiStep(2);
        else {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
    }
    listStep.push_back(1);
    listStep.push_back(1);

    for(int ipos = 0, ipos2 = 0; ipos < preSize; ipos++, ipos2++)
    {
        if (ipos == pos) 
        {
            for(int i = 0; i < count_nodePrint; i++)
            {
                if (i == ipos)
                {
                    nodeAnimation[i].addStep(NOD_SHOW);
                    nodeAnimation[i].addStep(NOD_UNSHOW);
                }
                else if (i == preSize + ipos2)
                {
                    nodeAnimation[i].addStep(NOD_SOLVE);
                    nodeAnimation[i].skipMultiStep(1);
                }
                else {
                    nodeAnimation[i].skipMultiStep(2);
                }
            }
            ipos++;
            listStep.push_back(2);
            listStep.push_back(3);
        }
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == preSize + ipos2)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(elements[i - preSize]);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(2);
        listStep.push_back(4);
        listStep.push_back(4);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
        {
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i - preSize]);
        }
    }
    
    listStep.push_back(5);
    listStep.push_back(6);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructDynamicArray::Animation_Del_Last()
{
    this->printElements = this->elements;
    Del_Last();
    int pos = sizearray;
    count_nodePrint = preSize + sizearray;
    count_arrowPrint = 0;
    Manipulate = 2; subManipulate = 1;
    startAnimationDS();

    if (preSize == 0)
    {
        listStep.push_back(0);
        this->totaltime = 0;
        this->step_total = 0;
        return;
    }

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pNext = getPosition(sizearray);
    for(sf::Vector2f &coord : pNext)
        coord.y += 200;
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < preSize) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pNext[i - preSize], "?", false);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
            nodeAnimation[i].skipMultiStep(2);
        else {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
    }
    listStep.push_back(1);
    listStep.push_back(1);

    for(int ipos = 0, ipos2 = 0; ipos2 < sizearray; ipos++, ipos2++)
    {
        if (ipos == pos) 
        {
            for(int i = 0; i < count_nodePrint; i++)
            {
                if (i == ipos)
                {
                    nodeAnimation[i].addStep(NOD_SHOW);
                    nodeAnimation[i].addStep(NOD_UNSHOW);
                }
                else if (i == preSize + ipos2)
                {
                    nodeAnimation[i].addStep(NOD_SOLVE);
                    nodeAnimation[i].skipMultiStep(1);
                }
                else {
                    nodeAnimation[i].skipMultiStep(2);
                }
            }
            ipos++;
            listStep.push_back(2);
            listStep.push_back(3);
        }
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == preSize + ipos2)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(elements[i - preSize]);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(2);
        listStep.push_back(4);
        listStep.push_back(4);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
        {
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i - preSize]);
        }
    }
    
    listStep.push_back(5);
    listStep.push_back(6);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructDynamicArray::Animation_Del_Manual()
{
    this->printElements = this->elements;
    int pos = string_to_int(vecStr[2]);
    if (pos <= 0) return void(Animation_Del_First());
    if (Del_Manual(pos) == -1) 
        return;
    
    count_nodePrint = preSize + sizearray;
    count_arrowPrint = 0;
    Manipulate = 2; subManipulate = 2;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pNext = getPosition(sizearray);
    for(sf::Vector2f &coord : pNext)
        coord.y += 200;
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    sf::Vector2f newPosition = pStart[0];
    pEnd.insert(pEnd.begin(), newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < preSize) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pNext[i - preSize], "?", false);
        }
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
            nodeAnimation[i].skipMultiStep(2);
        else {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
    }
    listStep.push_back(1);
    listStep.push_back(1);

    for(int ipos = 0, ipos2 = 0; ipos < preSize; ipos++, ipos2++)
    {
        if (ipos == pos) 
        {
            for(int i = 0; i < count_nodePrint; i++)
            {
                if (i == ipos)
                {
                    nodeAnimation[i].addStep(NOD_SHOW);
                    nodeAnimation[i].addStep(NOD_UNSHOW);
                }
                else if (i == preSize + ipos2)
                {
                    nodeAnimation[i].addStep(NOD_SOLVE);
                    nodeAnimation[i].skipMultiStep(1);
                }
                else {
                    nodeAnimation[i].skipMultiStep(2);
                }
            }
            ipos++;
            listStep.push_back(2);
            listStep.push_back(3);
        }
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == preSize + ipos2)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(elements[i - preSize]);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(2);
        listStep.push_back(4);
        listStep.push_back(4);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize)
        {
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i - preSize]);
        }
    }
    
    listStep.push_back(5);
    listStep.push_back(6);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructDynamicArray::Animation_Update()
{
    this->printElements = this->elements;
    int pos = string_to_int(vecStr[2]);
    int value = string_to_int(vecStr[3]);
    if (this->Update(pos, value) == -1) 
        return;
    count_nodePrint = this->sizearray;
    count_arrowPrint = 0;
    Manipulate = 3; subManipulate = 0;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < sizearray ? std::to_string(printElements[i]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord(value);
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }

    this->listStep.push_back(0);
    this->listStep.push_back(0);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructDynamicArray::Animation_Allocate()
{
    this->printElements = this->elements;
    Allocate(string_to_int(vecStr[4]), string_to_int(vecStr[3]));
    count_nodePrint = preSize + sizearray;
    count_arrowPrint = 0;
    Manipulate = 3; subManipulate = 1;
    startAnimationDS();

    std::vector<sf::Vector2f> pStart = getPosition(preSize);
    std::vector<sf::Vector2f> pNext = getPosition(sizearray);

    // setup
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < preSize)
            nodeAnimation[i].setup(&listNode[i], pStart[i], printElements[i], true);
        else 
            nodeAnimation[i].setup(&listNode[i], pNext[i - preSize], "?", false);
    }

    if (preSize > 0)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i < preSize) 
                nodeAnimation[i].addStep(NOD_DEL);
            else 
                nodeAnimation[i].skipMultiStep(1);
        }
        listStep.push_back(0);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i < preSize) { 
            nodeAnimation[i].skipMultiStep(2);
        }
        else {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
    }
    listStep.push_back(1);
    listStep.push_back(1);
    
    for(int ipos = 0; ipos < sizearray; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == preSize + ipos) {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(elements[i - preSize]);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(2);
        listStep.push_back(3);
        listStep.push_back(3);
    }

    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructDynamicArray::Animation_Access()
{
    this->printElements = this->elements;
    int pos = string_to_int(vecStr[2]);
    int value = string_to_int(vecStr[3]);
    if (this->Access(pos) == -1) 
        return;
    count_nodePrint = sizearray;
    count_arrowPrint = 0;
    Manipulate = 4; subManipulate = 0;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < sizearray ? std::to_string(printElements[i]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }

    this->listStep.push_back(0);
    this->listStep.push_back(0);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructDynamicArray::Animation_Search()
{
    this->printElements = this->elements;
    int pos = Search(string_to_int(vecStr[3]));
    count_nodePrint = this->sizearray;
    count_arrowPrint = 0;
    Manipulate = 4; subManipulate = 1;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < sizearray ? std::to_string(printElements[i]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    for (int ipos = 0; ipos < pos; ipos++)
    {
        for (int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(2);
            }
        }
        listStep.push_back(0);
        listStep.push_back(1);
    }

    if (pos != sizearray)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == pos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].addStep(NOD_APPEAR);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(0);
        listStep.push_back(1);
        listStep.push_back(2);
    }
    else {
        for(int i = 0; i < count_nodePrint; i++)
            nodeAnimation[i].skipMultiStep(1);
        listStep.push_back(3);
    }
    
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}