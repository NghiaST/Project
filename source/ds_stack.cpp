#include "ds_stack.hpp"

StructStack::StructStack(VisualizationSettings* settings, bool active) 
    : StructDataStructure(settings, active)
{
    this->maxsize = 15;
    this->sizeText = 13;
    this->sizeNode = 35;
    this->diffx = 50;
    this->diffy = 0;
    this->distance = this->sizeNode + this->diffx;
    this->thickness = 3;

    this->elements = std::vector<int>(maxsize, 0);
    listNode = std::vector<std::unique_ptr<Node>> (this->maxsize);
    for(auto &ptr : listNode)
        ptr = std::make_unique<CircleNode>(sf::Vector2f(0, 0), this->sizeNode, this->sizeText, this->thickness, "", this->font, this->theme->getNode());
    listArrow = std::vector<ArrowNode> (this->maxsize, ArrowNode(this->sizeNode, this->theme->getArrow()));
    listPoint = std::vector<sf::Vector2f> (this->maxsize, sf::Vector2f(0, 0));
    nodeAnimation = std::vector<Manipulate_Animation_ArrayNode> (this->maxsize, Manipulate_Animation_ArrayNode());
    arrowAnimation = std::vector<Manipulate_Animation_ArrayArrow> (this->maxsize, Manipulate_Animation_ArrayArrow());
    
    if (this->active)
        turn_on();
}
StructStack::~StructStack()
{
}

void StructStack::refreshAnimation()
{
    std::vector<sf::Vector2f> listP = this->getPosition(this->sizearray);
    count_nodePrint = this->sizearray;
    count_arrowPrint = count_nodePrint - 1;
    for(int i = 0; i < this->count_nodePrint; i++) {
        this->listNode[i]->setXY(listP[i]);
        this->listNode[i]->setWord(std::to_string(this->elements[i]));
    }
    for(int i = 0; i < this->count_arrowPrint; i++)
        this->listArrow[i].setPoint(listP[i], listP[i + 1]);
}
void StructStack::run(int manipulate, int way, std::vector<std::string> vecStr) 
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
        this->Animation_Push();
    }
    if (manipulate == 2) {
        this->Animation_Pop();
    }
    if (manipulate == 3) {
        this->Animation_Peek();
    }
    if (manipulate == 4) {
        this->Animation_Clear();
    }
}

int StructStack::Push(int value)
{
    if (this->sizearray == this->maxsize)
    {
        std::cout << "Limited Data. Can't add more\n";
        return -1;
    }
    for(int i = sizearray - 1; i >= 0; i--)
        this->elements[i + 1] = this->elements[i];
    this->elements[0] = value;
    this->sizearray++;
    return 0;
}

void StructStack::Pop()
{
    if (this->sizearray == 0)
        return;
    for(int i = 1; i < this->sizearray; i++)
        this->elements[i - 1] = this->elements[i];
    sizearray--;
}

void StructStack::Clear()
{
    sizearray = 0;
}

void StructStack::Animation_Initialize(int way)
{
    if (way == 0) this->Initialize_Empty();
    if (way == 1) this->Initialize_Random();
    if (way == 2) this->Initialize_Manual(string_to_array(vecStr[1]));
    if (way == 3) {
        if (this->Initialize_ExternalFile(vecStr[0]) == -1)
            return;
    }
    this->preElements = this->elements;

    count_nodePrint = sizearray;
    count_arrowPrint = count_nodePrint - 1;
    Manipulate = 0; subManipulate = way;
    startAnimationDS();

    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], false);
        nodeAnimation[i].addStep(NOD_APPEAR);
        if (i < count_arrowPrint) {
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false, ARR_1);
            arrowAnimation[i].addStep(AR_CREATE);
        }
    }
    this->listStep = std::vector<int>{0};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructStack::Animation_Push()
{
    if (Push(string_to_int(vecStr[2])) == -1)
        return;
    this->preElements = this->elements;
    count_nodePrint = sizearray;
    count_arrowPrint = count_nodePrint - 1;
    Manipulate = 1; subManipulate = 0;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(sizearray - 1);
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    sf::Vector2f newPosition;
    if (this->count_nodePrint == 1)
        newPosition = pEnd[0] + sf::Vector2f(0, 200);
    else 
        newPosition = pStart[0] + sf::Vector2f(0, 200);
    pStart.insert(pStart.begin(), newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], false);
            if (i < count_arrowPrint)
                arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false, ARR_1);
        }
        else if (i > 0) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
            if (i < count_arrowPrint)
                arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
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

    for(int i = 0; i < count_arrowPrint; i++)
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
    
    this->listStep = std::vector<int>{0, 1, 2};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructStack::Animation_Pop()
{
    this->preElements = this->elements;
    Pop();  
    count_nodePrint = preSize;
    count_arrowPrint = count_nodePrint - 1;
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
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);
    std::vector<sf::Vector2f> pEnd = getPosition(count_arrowPrint);

    sf::Vector2f newPosition = pStart[0];
    pEnd.insert(pEnd.begin(), newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
        if (i < count_arrowPrint)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
    }

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);

        if (i < count_arrowPrint)
            arrowAnimation[i].skipMultiStep(1);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == 0) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else if (i == 1) {
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].skipMultiStep(4);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }

    for(int i = 0; i < count_arrowPrint; i++)
    {
        if (i == 0) {
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_COLOR_TO);
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_DEL);
            arrowAnimation[i].skipMultiStep(1);
        }
        else {
            arrowAnimation[i].skipMultiStep(4);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
    }
    
    this->listStep = std::vector<int>{1, 1, 2, 2, 3, 3};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructStack::Animation_Peek()
{
    this->preElements = this->elements;
    int pos = 0;
    count_nodePrint = this->sizearray;
    count_arrowPrint = count_nodePrint - 1;
    Manipulate = 3; subManipulate = 0;
    startAnimationDS();

    if (preSize == 0)
    {
        listStep.push_back(0);
        this->totaltime = 0;
        this->step_total = 0;
        return;
    }

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
        if (i < count_arrowPrint)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
    }


    for(int istep = 0; istep < 3; istep++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == pos)
            {
                nodeAnimation[i].addStep(NOD_ACTIVE);
            }
            else {
                nodeAnimation[i].skipMultiStep(1);
            }
            if (i < count_arrowPrint)
                arrowAnimation[i].skipMultiStep(1);
        }
        listStep.push_back(1);
    }
    
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructStack::Animation_Clear()
{
    this->preElements = this->elements;
    Clear();
    count_nodePrint = preSize;
    count_arrowPrint = count_nodePrint - 1;
    Manipulate = 4; subManipulate = 0;
    startAnimationDS();

    if (preSize == 0)
    {
        listStep.push_back(0);
        this->totaltime = 0;
        this->step_total = 0;
        return;
    }

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);
    std::vector<sf::Vector2f> pEnd = getPosition(count_arrowPrint);
    
    sf::Vector2f newPosition = pStart[0];
    pEnd.insert(pEnd.begin(), newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
        if (i < count_arrowPrint)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
    }

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);

        if (i < count_arrowPrint)
            arrowAnimation[i].skipMultiStep(1);
    }
    listStep.push_back(0);

    for(int isize = 0; isize < preSize; isize++)
    {
        pEnd = getPosition(preSize - isize - 1);
        pEnd.insert(pEnd.begin(), isize + 1, sf::Vector2f(0, 0));
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i < isize) {
                nodeAnimation[i].skipMultiStep(5);
            }
            else if (i == isize) {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].skipMultiStep(2);
                nodeAnimation[i].addStep(NOD_DEL);
                nodeAnimation[i].skipMultiStep(1);
            }
            else if (i == isize + 1) {
                nodeAnimation[i].skipMultiStep(2);
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].skipMultiStep(1);
                nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
            }
            else {
                nodeAnimation[i].skipMultiStep(4);
                nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
            }
        }

        for(int i = 0; i < count_arrowPrint; i++)
        {
            if (i < isize)
            {
                arrowAnimation[i].skipMultiStep(5);
            }
            else if (i == isize) {
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_COLOR_TO);
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_DEL);
                arrowAnimation[i].skipMultiStep(1);
            }
            else {
                arrowAnimation[i].skipMultiStep(4);
                arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
            }
        }
        listStep.push_back(1);
        listStep.push_back(2);
        listStep.push_back(2);
        listStep.push_back(3);
        listStep.push_back(3);
    }

    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
