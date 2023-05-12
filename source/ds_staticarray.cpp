#include "ds_staticarray.hpp"
#include <fstream>

StructStaticArray::StructStaticArray(VisualizationSettings* settings, bool active) 
    : StructDataStructure(settings, active)
{
    this->maxsize = 15;
    this->sizeText = 13;
    this->sizeNode = 40;
    this->diffx = 6;
    this->diffy = 0;
    this->distance = this->sizeNode + this->diffx;
    this->thickness = 3;

    this->elements = std::vector<int>(maxsize, 0);
    listNode = std::vector<std::unique_ptr<Node>> (this->maxsize);
    for(auto &ptr : listNode)
        ptr = std::make_unique<RectangleNode>(sf::Vector2f(0, 0), this->sizeNode, this->sizeText, this->thickness, "", this->font, this->theme->getNode());
    listPoint = std::vector<sf::Vector2f> (this->maxsize, sf::Vector2f(0, 0));
    nodeAnimation = std::vector<Manipulate_Animation_ArrayNode> (this->maxsize, Manipulate_Animation_ArrayNode());
    
    if (this->active)
        turn_on();
}
StructStaticArray::~StructStaticArray()
{
}

void StructStaticArray::refreshAnimation()
{
    std::vector<sf::Vector2f> listP = this->getPosition(this->size_fixed);
    count_nodePrint = this->size_fixed;
    count_arrowPrint = 0;
    for(int i = 0; i < this->count_nodePrint; i++) {
        this->listNode[i]->setXY(listP[i]);
        this->listNode[i]->setWord(i < sizearray ? std::to_string(this->elements[i]) : "?");
    }
}
void StructStaticArray::run(int manipulate, int way, std::vector<std::string> vecStr)
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
        this->Animation_Update();
    }
    if (manipulate == 4) {
        if (way == 0) this->Animation_Access();
        if (way == 1) this->Animation_Search();
    }
}

// build init
void StructStaticArray::Initialize_Empty_Fixedsize(int size_fixed) 
{
    this->size_fixed = std::min(size_fixed, maxsize);
    this->sizearray = 0;
}
void StructStaticArray::Initialize_Random_Unfixedsize()
{
    this->size_fixed = Rand(5, this->maxsize);
    this->sizearray = Rand(2, this->size_fixed - 1);
    for(int i = 0; i < this->sizearray; i++) elements[i] = Rand(0, 999);
}
void StructStaticArray::Initialize_Manual_Fixedsize(int size_fixed, std::vector<int> arr)
{
    this->size_fixed = std::min(size_fixed, maxsize);
    this->sizearray = (arr.size() < this->size_fixed ? arr.size() : this->size_fixed);
    for(int i = 0; i < this->sizearray; i++) 
        this->elements[i] = arr[i];
}
int StructStaticArray::Initialize_ExternalFile_Fixedsize(std::string filename)
{
    filename = ".\\fileinput\\" + filename;
    std::fstream file(filename, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Failed Opening File\n";
        return -1;
    }
    std::string content;
    std::string line;

    while (std::getline(file, line))
        content += line + ' ';
    file.close();

    std::vector<int> arr = string_to_array(content);
    if (arr.size() < 2) {
        std::cout << "Input is Invalid\n";
        return -1;
    }
    int size_fixed = arr[0];
    arr.erase(arr.begin());
    arr.erase(arr.begin());
    this->Initialize_Manual_Fixedsize(size_fixed, arr);
    for(int i : arr) std::cout << i << ' '; std::cout << '\n';
    return 0;
}

// build insert
int StructStaticArray::Insert_First(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "Limited Data. Can't add more\n";
        return -1;
    }
    for(int i = sizearray - 1; i >= 0; i--) {
        elements[i + 1] = elements[i];
    }
    elements[0] = value;
    sizearray++;
    return 0;
}
int StructStaticArray::Insert_Last(int value)
{
    if (sizearray == maxsize) {
        std::cout << "Limited Data. Can't add more\n";
        return -1;
    }
    elements[sizearray++] = value;
    return 0;
}
int StructStaticArray::Insert_Manual(int pos, int value) 
{
    if (sizearray == maxsize) {
        std::cout << "Limited Data. Can't add more\n";
        return -1;
    }
    sizearray++;
    for(int i = sizearray - 2; i >= pos; i--) {
        elements[i + 1] = elements[i];
    }
    elements[pos] = value;
    return 0;
}

// build Delete
void StructStaticArray::Del_First()
{
    if (sizearray == 0) return;
    std::rotate(elements.begin(), elements.begin() + 1, elements.begin() + sizearray);
    sizearray--;
}
void StructStaticArray::Del_Last()
{
    if (sizearray == 0) return;
    sizearray--;
}
int StructStaticArray::Del_Manual(int pos)
{
    if (sizearray <= pos) return -1;
    if (sizearray == 0) return 0;
    std::rotate(elements.begin() + pos, elements.begin() + pos + 1, elements.begin() + sizearray);
    sizearray--;
    return 0;
}

// build Update
int StructStaticArray::Update(int pos, int value) 
{
    if (pos < 0 || pos >= maxsize)
    {
        std::cout << "Input must be in range [0, N - 1]\n";
        return -1;
    }
    this->elements[pos] = value;
    return 0;
}

// build Access
int StructStaticArray::Access(int pos)
{
    if (pos < 0 || pos >= maxsize)
    {
        std::cout << "Input must be in range [0, N - 1]\n";
        return -1;
    }
    return 0;
}

// build Search
int StructStaticArray::Search(int value) 
{
    for(int i = 0; i < sizearray; i++)
    {
        if (this->elements[i] == value)
        {
            std::cout << "Find value at element " << i << '\n';
            return i;
        }
    }
    return sizearray;
}

void StructStaticArray::Animation_Initialize(int way)
{
    if (way == 0) this->Initialize_Empty_Fixedsize(string_to_int(vecStr[0]));
    if (way == 1) this->Initialize_Random_Unfixedsize();
    if (way == 2) this->Initialize_Manual_Fixedsize(string_to_int(vecStr[0]), string_to_array(vecStr[2]));
    if (way == 3) {
        if (this->Initialize_ExternalFile_Fixedsize(vecStr[1]) == -1)
            return;
    }
    this->printElements = this->elements;

    count_nodePrint = size_fixed;
    count_arrowPrint = 0;
    Manipulate = 0; subManipulate = way;
    startAnimationDS();

    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < sizearray ? std::to_string(printElements[i]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, false);
        nodeAnimation[i].addStep(NOD_APPEAR);
    }
    this->listStep = std::vector<int>{0};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructStaticArray::Animation_Insert_First()
{
    if (sizearray == size_fixed || Insert_First(string_to_int(vecStr[4])) == -1)
        return;
    this->printElements = this->elements;

    count_nodePrint = size_fixed;
    count_arrowPrint = 0;
    Manipulate = 1; subManipulate = 0;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < preSize ? std::to_string(printElements[i + 1]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord(0);
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
        }
    }
    listStep.push_back(1);
    listStep.push_back(1);
    listStep.push_back(1);

    for(int ipos = preSize - 1; ipos >= 0; ipos--)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == ipos + 1)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(printElements[i]);
                nodeAnimation[i].addStep(NOD_SOLVE);
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
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == 0)
        {
            nodeAnimation[i].addStep(NOD_ACTIVE);
            nodeAnimation[i].setWord(printElements[i]);
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }

    listStep.push_back(4);
    listStep.push_back(4);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructStaticArray::Animation_Insert_Last()
{
    if (sizearray == size_fixed || Insert_Last(string_to_int(vecStr[4])) == -1)
        return;
    this->printElements = this->elements;

    count_nodePrint = size_fixed;
    count_arrowPrint = 0;
    Manipulate = 1; subManipulate = 1;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < preSize ? std::to_string(printElements[i + 1]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }
    
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord(printElements[i]);
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }

    this->listStep = {1, 2};
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructStaticArray::Animation_Insert_Manual()
{
    int pos = string_to_int(vecStr[3]);
    if (pos == 0) return void(Animation_Insert_First());
    if (pos == this->sizearray) return void(Animation_Insert_Last());
    if (sizearray == size_fixed || Insert_Manual(pos, string_to_int(vecStr[4])) == -1)
        return;

    this->printElements = this->elements;
    count_nodePrint = size_fixed;
    count_arrowPrint = 0;
    Manipulate = 1; subManipulate = 2;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < preSize ? i < pos ? std::to_string(printElements[i]) : std::to_string(printElements[i + 1]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord(0);
            nodeAnimation[i].addStep(NOD_APPEAR);
            nodeAnimation[i].addStep(NOD_NORMAL);
        }
        else {
            nodeAnimation[i].skipMultiStep(3);
        }
    }
    listStep.push_back(1);
    listStep.push_back(1);
    listStep.push_back(1);

    for(int ipos = preSize - 1; ipos >= pos; ipos--)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == ipos + 1)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(printElements[i]);
                nodeAnimation[i].addStep(NOD_SOLVE);
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
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == pos)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord(printElements[i]);
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }

    listStep.push_back(4);
    listStep.push_back(4);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructStaticArray::Animation_Del_First()
{
    this->printElements = this->elements;
    Del_First();    
    count_nodePrint = size_fixed;
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
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < preSize ? std::to_string(printElements[i]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    for(int ipos = 1; ipos < preSize; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos - 1)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(printElements[i + 1]);
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(1);
        listStep.push_back(2);
        listStep.push_back(2);
    }
    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize - 1)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord("?");
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }
    
    listStep.push_back(3);
    listStep.push_back(3);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructStaticArray::Animation_Del_Last()
{
    this->printElements = this->elements;
    Del_Last();

    count_nodePrint = size_fixed;
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
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < preSize ? std::to_string(printElements[i]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize - 1)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord("?");
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }
    
    listStep.push_back(1);
    listStep.push_back(1);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}
void StructStaticArray::Animation_Del_Manual()
{
    this->printElements = this->elements;
    int pos = string_to_int(vecStr[3]);
    if (pos <= 0) return void(Animation_Del_First());
    if (Del_Manual(pos) == -1) 
        return;

    if (preSize == 0)
    {
        listStep.push_back(0);
        this->totaltime = 0;
        this->step_total = 0;
        return;
    }
    
    count_nodePrint = size_fixed;
    count_arrowPrint = 0;
    Manipulate = 2; subManipulate = 2;
    startAnimationDS();

    // setup position
    std::vector<sf::Vector2f> pStart = getPosition(count_nodePrint);

    // build step
    for(int i = 0; i < count_nodePrint; i++) {
        std::string word = (i < preSize ? std::to_string(printElements[i]) : "?");
        nodeAnimation[i].setup(&listNode[i], pStart[i], word, true);
    }

    for(int ipos = pos + 1; ipos < preSize; ipos++)
    {
        for(int i = 0; i < count_nodePrint; i++)
        {
            if (i == ipos - 1)
            {
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].setWord(printElements[i + 1]);
                nodeAnimation[i].addStep(NOD_SOLVE);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else if (i == ipos)
            {
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_SHOW);
                nodeAnimation[i].addStep(NOD_UNSHOW);
            }
            else {
                nodeAnimation[i].skipMultiStep(3);
            }
        }
        listStep.push_back(1);
        listStep.push_back(2);
        listStep.push_back(2);
    }

    for(int i = 0; i < count_nodePrint; i++)
    {
        if (i == preSize - 1)
        {
            nodeAnimation[i].addStep(NOD_SOLVE);
            nodeAnimation[i].setWord("?");
            nodeAnimation[i].addStep(NOD_APPEAR);
        }
        else {
            nodeAnimation[i].skipMultiStep(2);
        }
    }
    
    listStep.push_back(3);
    listStep.push_back(3);
    this->totaltime = nodeAnimation[0].getTotaltime();
    this->step_total = nodeAnimation[0].getTotalstep();
}

void StructStaticArray::Animation_Update()
{
    this->printElements = this->elements;
    int pos = string_to_int(vecStr[3]);
    int value = string_to_int(vecStr[4]);
    if (this->Update(pos, value) == -1) 
        return;
    count_nodePrint = size_fixed;
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

void StructStaticArray::Animation_Access()
{
    this->printElements = this->elements;
    int pos = string_to_int(vecStr[3]);
    int value = string_to_int(vecStr[4]);
    if (this->Access(pos) == -1) 
        return;
    count_nodePrint = size_fixed;
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

void StructStaticArray::Animation_Search()
{
    this->printElements = this->elements;
    int pos = Search(string_to_int(vecStr[4]));
    count_nodePrint = size_fixed;
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
