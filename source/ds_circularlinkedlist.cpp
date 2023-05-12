#include "ds_circularlinkedlist.hpp"

StructCircularLinkedList::StructCircularLinkedList(VisualizationSettings* settings, bool active) 
    : StructDataStructure(settings, active)
{
    this->maxsize = 15;
    this->sizeText = 13;
    this->sizeNode = 35;
    this->diffx = 50;
    this->diffy = 0;
    this->distance = this->sizeNode + this->diffx;
    this->thickness = 3;

    this->elements = std::vector<int>(this->maxsize, 0);
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
StructCircularLinkedList::~StructCircularLinkedList()
{
}

void StructCircularLinkedList::refreshAnimation()
{
    std::vector<sf::Vector2f> listP = this->getPosition(this->sizearray);
    count_nodePrint = this->sizearray;
    count_arrowPrint = count_nodePrint;
    for(int i = 0; i < this->count_nodePrint; i++) {
        this->listNode[i]->setXY(listP[i]);
        this->listNode[i]->setWord(std::to_string(this->elements[i]));
    }
    for(int i = 0; i < this->count_arrowPrint; i++)
        this->listArrow[i].setPoint(listP[i], listP[i + 1]);
}
void StructCircularLinkedList::run(int manipulate, int way, std::vector<std::string> vecStr)
{
    if (manipulate == -1) return;
    if (this->running == true && manipulate != -1)
        stopAnimationDS();

    if (this->active == false) {
        std::cout << "Error StructCircularLinkedList::run\n";
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
        Animation_Update();
    }
    if (manipulate == 4) {
        Animation_Search();
    }
}

void StructCircularLinkedList::Animation_Initialize(int way)
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
    count_arrowPrint = count_nodePrint;
    Manipulate = 0; subManipulate = way;
    startAnimationDS();

    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], false);
        nodeAnimation[i].addStep(NOD_APPEAR);
        if (i < count_arrowPrint - 1)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false, ARR_1);
        else 
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], false, ARR_LOOP);
        arrowAnimation[i].addStep(AR_CREATE);
    }
    this->listStep = std::vector<int>{0};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructCircularLinkedList::Animation_Insert_First()
{
    if (Insert_First(string_to_int(vecStr[3])) == -1)
        return;
    this->preElements = this->elements;
    count_nodePrint = sizearray;
    count_arrowPrint = count_nodePrint;
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
            if (i < count_arrowPrint - 1)
                arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false, ARR_1);
            else
                arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], false, ARR_LOOP);
        }
        else if (i > 0) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
            if (i < count_arrowPrint - 1)
                arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
            else
                arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[1 % count_nodePrint], true, ARR_LOOP);
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
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_CREATE);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[(i + 1) % sizearray]);
        }
        else if (i == count_nodePrint - 1) {
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_NORMAL, pStart[i], pStart[0]);
            arrowAnimation[i].addStep(AR_NORMAL, pEnd[i], pEnd[0]);
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
void StructCircularLinkedList::Animation_Insert_Last()
{
    if (Insert_Last(string_to_int(vecStr[3])) == -1)
        return;
    this->preElements = this->elements;
    count_nodePrint = sizearray;
    count_arrowPrint = count_nodePrint;
    Manipulate = 1; subManipulate = 1;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(sizearray - 1);
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    sf::Vector2f newPosition;
    if (this->count_nodePrint == 1)
        newPosition = pEnd.back() + sf::Vector2f(0, 200);
    else 
        newPosition = pStart.back() + sf::Vector2f(0, 200);
    pStart.push_back(newPosition);

    // build step
    int pos = count_nodePrint - 1;
    for(int i = 0; i < count_nodePrint; i++) {
        if (i < pos - 1) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
        }
        else if (i == pos - 1) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false, ARR_1);
        }
        else if (i == pos && i > 0) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], false);
            arrowAnimation[i].setup(&listArrow[i], pStart[i - 1], pStart[0], true, ARR_LOOP);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], false);
            arrowAnimation[i].setup(&listArrow[i], pStart[0], pStart[0], false, ARR_LOOP);
        }
    }

    // setup step to step
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos) {
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else if (i == pos - 1) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].addStep(NOD_NORMAL);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }

    for(int i = 0; i < count_arrowPrint; i++)
    {
        if (i == pos - 1) {
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_CREATE);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
        else if (i == pos) {
            arrowAnimation[i].skipMultiStep(1);
            if (i == 0) 
                arrowAnimation[i].addStep(AR_CREATE);
            else 
                arrowAnimation[i].addStep(AR_MOVE, pStart[i], pStart[0]);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[0]);
        }
        else {
            arrowAnimation[i].skipMultiStep(2);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }   
    }
    
    this->listStep = std::vector<int>{0, 1, 2};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructCircularLinkedList::Animation_Insert_Manual()
{
    int pos = string_to_int(vecStr[2]);
    if (pos == 0) return void(Animation_Insert_First());
    if (pos == this->sizearray) return void(Animation_Insert_Last());
    if (Insert_Manual(pos, string_to_int(vecStr[3])) == -1)
        return;
    this->preElements = this->elements;
    count_nodePrint = sizearray;
    count_arrowPrint = count_nodePrint;
    Manipulate = 1; subManipulate = 2;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(sizearray - 1);
    std::vector<sf::Vector2f> pEnd = getPosition(sizearray);

    sf::Vector2f newPosition;
    if (this->count_nodePrint == 1)
        newPosition = pEnd.back() + sf::Vector2f(0, 200);
    else 
        newPosition = pStart[pos] + sf::Vector2f(0, 200);
    pStart.insert(pStart.begin() + pos, newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == pos - 1) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 2], true, ARR_1);
        }
        else if (i == pos) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], false);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], false, ARR_1);
        }
        else if (i < count_nodePrint - 1) {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
        }
        else {
            nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], true, ARR_LOOP);
        }
    }

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);

        if (i < count_arrowPrint)
            arrowAnimation[i].skipMultiStep(1);
    }
    listStep.push_back(0);
    
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
                if (i < count_arrowPrint) 
                    arrowAnimation[i].skipMultiStep(2);
            }
        }
        listStep.push_back(1);
        listStep.push_back(2);
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
            if (i < count_arrowPrint)
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
    for(int i = 0; i < count_arrowPrint; i++)
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
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[(i + 1) % count_nodePrint]);
        }
    }

    listStep.push_back(1);
    listStep.push_back(2);
    listStep.push_back(2);
    listStep.push_back(3);
    listStep.push_back(4);
    listStep.push_back(5);
    listStep.push_back(5);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructCircularLinkedList::Animation_Del_First()
{
    this->preElements = this->elements;
    Del_First();    
    count_nodePrint = preSize;
    count_arrowPrint = count_nodePrint;
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
    std::vector<sf::Vector2f> pEnd = getPosition(count_nodePrint - 1);

    sf::Vector2f newPosition = pStart[0];
    pEnd.insert(pEnd.begin(), newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
        if (i < count_arrowPrint - 1)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
        else 
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], true, ARR_LOOP);
    }

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);
        arrowAnimation[i].skipMultiStep(1);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == 0) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(3);
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else if (i == 1) {
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else if (i == count_arrowPrint - 1) {
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].skipMultiStep(5);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }

    for(int i = 0; i < count_arrowPrint; i++)
    {
        if (i == count_arrowPrint - 1) {
            if (i == 0) {
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_ACTIVE);
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_DEL);
                arrowAnimation[i].skipMultiStep(2);
            }
            else {
                arrowAnimation[i].skipMultiStep(2);
                arrowAnimation[i].addStep(AR_ACTIVE);
                arrowAnimation[i].addStep(AR_MOVE, pStart[i], pStart[1]);
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[1]);
            }
        }
        else if (i == 0) {
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_COLOR_TO);
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_DEL);
            arrowAnimation[i].skipMultiStep(2);
        }
        else {
            arrowAnimation[i].skipMultiStep(5);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
    }
    
    this->listStep = std::vector<int>{1, 1, 2, 2, 3, 4, 4};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructCircularLinkedList::Animation_Del_Last()
{
    this->preElements = this->elements;
    Del_Last();
    count_nodePrint = preSize;
    count_arrowPrint = count_nodePrint;
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
    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);
    std::vector<sf::Vector2f> pEnd = getPosition(count_nodePrint - 1);

    sf::Vector2f newPosition = pStart.back();
    pEnd.push_back(newPosition);

    // build step
    for (int i = 0; i < count_nodePrint; i++)
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
    for (int i = 0; i < count_arrowPrint; i++) {
        if (i < count_arrowPrint - 1)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
        else
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], true, ARR_LOOP);
    }
    
    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);
        arrowAnimation[i].skipMultiStep(1);
    }
    listStep.push_back(1);

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
        listStep.push_back(2);
        listStep.push_back(3);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_DEL);
            nodeAnimation[i].skipMultiStep(1);
        }
        else if (i == pos - 1) {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].skipMultiStep(3);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else if (i == 0) {
            nodeAnimation[i].skipMultiStep(1);
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
        else {
            nodeAnimation[i].skipMultiStep(4);
            nodeAnimation[i].addStep(NOD_MOVE, pEnd[i]);
        }
    }
    for(int i = 0; i < count_arrowPrint; i++)
    {
        if (i == pos - 1) {
            arrowAnimation[i].skipMultiStep(2);
            arrowAnimation[i].addStep(AR_DEL);
            arrowAnimation[i].skipMultiStep(2);
        }
        else if (i == pos) {
            if (i == 0) {
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_ACTIVE);
                arrowAnimation[i].addStep(AR_DEL);
                arrowAnimation[i].skipMultiStep(2);
            }
            else {
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_ACTIVE);
                arrowAnimation[i].addStep(AR_MOVE, pStart[i - 1], pStart[0]);
                arrowAnimation[i].skipMultiStep(1);
                arrowAnimation[i].addStep(AR_MOVE, pEnd[i - 1], pEnd[0]);
            }
        }
        else {
            arrowAnimation[i].skipMultiStep(4);
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[i + 1]);
        }
    }
    
    this->listStep.push_back(2);
    this->listStep.push_back(4);
    this->listStep.push_back(4);
    this->listStep.push_back(5);
    this->listStep.push_back(5);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructCircularLinkedList::Animation_Del_Manual()
{
    this->preElements = this->elements;
    int pos = string_to_int(vecStr[2]);
    if (pos == 0) return void(Animation_Del_First());
    if (Del_Manual(pos) == -1) 
        return;
    
    count_nodePrint = preSize;
    count_arrowPrint = count_nodePrint;
    Manipulate = 2; subManipulate = 2;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);
    std::vector<sf::Vector2f> pEnd = getPosition(count_nodePrint - 1);

    sf::Vector2f newPosition = pStart[pos] + sf::Vector2f(0, 200);
    pEnd.insert(pEnd.begin() + pos, newPosition);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
        if (i < count_arrowPrint - 1)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
        else 
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], true, ARR_LOOP);
    }

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);
        arrowAnimation[i].skipMultiStep(1);
    }
    listStep.push_back(0);

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
        listStep.push_back(1);
        listStep.push_back(2);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos - 1) {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].skipMultiStep(2);
            arrowAnimation[i].skipMultiStep(1);
            arrowAnimation[i].addStep(AR_COLOR_TO);
            arrowAnimation[i].skipMultiStep(1);
        } 
        else if (i == pos) {
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_ACTIVE);
            arrowAnimation[i].skipMultiStep(2);
            arrowAnimation[i].addStep(AR_ACTIVE);
        }
        else if (i == pos + 1) {
            nodeAnimation[i].skipMultiStep(2);
            nodeAnimation[i].addStep(NOD_SOLVE);
            arrowAnimation[i].skipMultiStep(3);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
            arrowAnimation[i].skipMultiStep(3);
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
    for(int i = 0; i < count_arrowPrint; i++)
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
            arrowAnimation[i].addStep(AR_MOVE, pEnd[i], pEnd[(i + 1) % count_arrowPrint]);
        }
    }
    
    this->listStep.push_back(3);
    this->listStep.push_back(3);
    this->listStep.push_back(3);
    this->listStep.push_back(3);
    this->listStep.push_back(4);
    this->listStep.push_back(5);
    this->listStep.push_back(5);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructCircularLinkedList::Animation_Update()
{
    this->preElements = this->elements;
    int pos = string_to_int(vecStr[2]);
    int value = string_to_int(vecStr[3]);
    if (this->Update(pos, value) == -1) 
        return;
    count_nodePrint = this->sizearray;
    count_arrowPrint = count_nodePrint;
    Manipulate = 3; subManipulate = 0;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
        if (i < count_arrowPrint - 1)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
        else
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], true, ARR_LOOP);
    }

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);
        arrowAnimation[i].skipMultiStep(1);
    }
    listStep.push_back(0);

    for(int ipos = 0; ipos < pos; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);

                if (i < count_arrowPrint) {
                    arrowAnimation[i].skipMultiStep(1);
                    arrowAnimation[i].addStep(AR_COLOR_TO);
                }
            }
            else {
                nodeAnimation[i].skipMultiStep(2);
                if (i < count_arrowPrint) {
                    arrowAnimation[i].skipMultiStep(2);
                }
            }
        }
        listStep.push_back(1);
        listStep.push_back(2);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos)
        {
            nodeAnimation[i].addStep(NOD_SHOW);
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[pos].setWord(value);
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
        }
        if (i < count_arrowPrint)
            arrowAnimation[i].skipMultiStep(3);
    }

    this->listStep.push_back(2);
    this->listStep.push_back(3);
    this->listStep.push_back(3);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructCircularLinkedList::Animation_Search()
{
    this->preElements = this->elements;
    int pos = Search(string_to_int(vecStr[3]));
    count_nodePrint = this->sizearray;
    count_arrowPrint = count_nodePrint;
    Manipulate = 4; subManipulate = 0;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        nodeAnimation[i].setup(&listNode[i], pStart[i], preElements[i], true);
        if (i < count_nodePrint - 1)
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[i + 1], true, ARR_1);
        else 
            arrowAnimation[i].setup(&listArrow[i], pStart[i], pStart[0], true, ARR_LOOP);
    }

    // step 1
    for(int i = 0; i < count_nodePrint; i++) {
        if (i == 0) nodeAnimation[i].addStep(NOD_ACTIVE);
        else nodeAnimation[i].skipMultiStep(1);
        arrowAnimation[i].skipMultiStep(1);
    }
    listStep.push_back(0);

    for (int ipos = 0; ipos < pos; ipos++)
    {
        for (int i = 0; i < count_nodePrint; i++)
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
        listStep.push_back(1);
        listStep.push_back(2);
    }

    if (pos != sizearray)
    {
        for(int istep = 0; istep < 3; istep++)
        {
            for(int i = 0; i < count_nodePrint; i++)
            {
                if (i == pos)
                {
                    nodeAnimation[i].addStep(NOD_APPEAR);
                }
                else {
                    nodeAnimation[i].skipMultiStep(1);
                }
                arrowAnimation[i].skipMultiStep(1);
            }
            listStep.push_back(4);
        }
    }
    else {
        for(int i = 0; i < count_nodePrint; i++)
            nodeAnimation[i].skipMultiStep(1);
        for(int i = 0; i < count_arrowPrint; i++)
            arrowAnimation[i].skipMultiStep(1);
        listStep.push_back(3);
    }
    
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
