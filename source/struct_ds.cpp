#include <fstream>
#include <algorithm>
#include "struct_ds.hpp"

StructDataStructure::StructDataStructure(VisualizationSettings* settings, bool active) 
{
    // window
    this->window = settings->getWindow();
    this->theme = settings->getTheme();
    this->speed = settings->getSpeed();
    this->active = active;
    
    // font
    this->font = settings->getFont();

    // point
    this->centerVisual = sf::Vector2f(this->window->getSize().x / 2, 150);

    // check which manipulate is activating
    this->type1 = -1;
    this->type2 = -1;

    // list
    this->maxsize = 12;
    this->sizearray = 0;
    this->elements = std::vector<int>(maxsize, 0);
}

StructDataStructure::~StructDataStructure()
{
}

// setup
void StructDataStructure::turn_on()
{
    this->active = true;
    this->sizearray = 0;
    this->run(0, 1, {}); // Initialize_Random
}
void StructDataStructure::turn_off()
{
    this->active = false;
}
void StructDataStructure::startAnimationDS()
{
    this->running = true;
    this->time = 0;
    this->type_running = ANIMATION_PLAY;
    this->step_present = 0;
    clock.restart();
}
void StructDataStructure::stopAnimationDS()
{
    this->running = false;
    this->type_running = ANIMATION_PAUSE;
    this->totaltime = 0;
    for(int i = 0; i < this->count_nodePrint; i++) {
        listNode[i]->stopAnimation();
        nodeAnimation[i].clearStep();
    }
    for(int i = 0; i < this->count_arrowPrint; i++) {
        listArrow[i].setStatusAnimation(0);
        arrowAnimation[i].clearStep();
    }
    this->count_nodePrint = this->sizearray;
    this->printElements = this->elements;
    this->listStep.clear();
    refreshAnimation();
}

// get
int StructDataStructure::getManipulate()
{
    return this->Manipulate;
}
int StructDataStructure::getsubManipulate()
{
    return this->subManipulate;
}
const bool &StructDataStructure::isActive() const
{
    return this->active;
}
std::vector<sf::Vector2f> StructDataStructure::getPosition(int size)
{
    std::vector<sf::Vector2f> listP;

    sf::Vector2f velocity, coord;
    velocity.x = this->distance;
    velocity.y = this->diffy;

    coord.x = this->centerVisual.x - velocity.x / 2 * (size - 1);
    coord.y = this->centerVisual.y - velocity.y / 2 * (size - 1);

    for(int i = 0; i < size; i++) {
        listP.push_back(coord);
        coord += velocity;
    }
    return listP;
}

// build Initialize
void StructDataStructure::Initialize_Empty() 
{
    this->sizearray = 0;
}
void StructDataStructure::Initialize_Random()
{
    this->sizearray = Rand(2, this->maxsize - 1);
    for(int i = 0; i < this->sizearray; i++) elements[i] = Rand(0, 999);
}
void StructDataStructure::Initialize_Manual(std::vector<int> arr) 
{
    this->sizearray = (arr.size() < this->maxsize ? arr.size() : this->maxsize);
    for(int i = 0; i < this->sizearray; i++) 
        this->elements[i] = arr[i];
}
int StructDataStructure::Initialize_ExternalFile(std::string filename) 
{
    // haven't know
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

    this->Initialize_Manual(string_to_array(content));
    return 0;
}

// build Insert
int StructDataStructure::Insert_First(int value) 
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
int StructDataStructure::Insert_Last(int value)
{
    if (sizearray == maxsize) {
        std::cout << "Limited Data. Can't add more\n";
        return -1;
    }
    elements[sizearray++] = value;
    return 0;
}
int StructDataStructure::Insert_Manual(int pos, int value) 
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
void StructDataStructure::Del_First()
{
    if (sizearray == 0) return;
    std::rotate(elements.begin(), elements.begin() + 1, elements.begin() + sizearray);
    sizearray--;
}
void StructDataStructure::Del_Last()
{
    if (sizearray == 0) return;
    sizearray--;
}
int StructDataStructure::Del_Manual(int pos)
{
    if (sizearray <= pos) return -1;
    if (sizearray == 0) return 0;
    std::rotate(elements.begin() + pos, elements.begin() + pos + 1, elements.begin() + sizearray);
    sizearray--;
    return 0;
}

// build Update
int StructDataStructure::Update(int pos, int value) 
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
int StructDataStructure::Access(int pos)
{
    if (pos < 0 || pos >= maxsize)
    {
        std::cout << "Input must be in range [0, N - 1]\n";
        return -1;
    }
    return 0;
}

// build Search
int StructDataStructure::Search(int value) 
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

// update
sf::Vector2i StructDataStructure::updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType)
{
    sf::Vector2i ret(-1, -1);
    for(int i = 0; i < this->sizearray; i++) {
        listNode[i]->updateKBM(mousePos, mouseType, keyboardType);
        if (listNode[i]->getRunning() == false && listNode[i]->getStatus() == 2) 
            ret = sf::Vector2i(i, this->elements[i]);
    }
    return ret;
}
void StructDataStructure::updateTypeAnimation(int newTypeRunning)
{
    /// 0, 1, 2, 3, 4, 5 : <<, <, ||, play, >, >>
    if (this->running == false)
        return;
    ANIMATION_TYPE type_next = static_cast<ANIMATION_TYPE>(newTypeRunning);
    switch (newTypeRunning)
    {
        case 0 : 
            this->time = 0;
            this->step_present = (int) ((time - 0.001) / steptime);
            this->type_running = ANIMATION_PAUSE;
            break;
        case 5 : 
            this->time = step_total * steptime;
            this->step_present = (int) ((time - 0.001) / steptime);
            this->type_running = ANIMATION_PAUSE;
            break;
        case 2 :
            this->step_present = (int) ((time - 0.001) / steptime);
            this->type_running = ANIMATION_PAUSE;
            break;
        case 3 :
            this->step_present = (int) ((time - 0.001) / steptime);
            this->type_running = ANIMATION_PLAY;
            break;
        case 1 :
            this->step_present = (int) ((time - 0.001) / steptime);
            if (this->type_running == ANIMATION_STEP_DOWN || this->type_running == ANIMATION_STEP_UP)
            {
                this->step_present = this->step_next;
                this->time = step_present * steptime;
            }
            this->step_next = std::max(step_present - 1, 0);
            this->type_running = ANIMATION_STEP_DOWN;
            break;
        case 4 :
            this->step_present = (int) ((time - 0.001) / steptime);
            if (this->type_running == ANIMATION_STEP_DOWN || this->type_running == ANIMATION_STEP_UP)
            {
                this->step_present = this->step_next;
                this->time = step_present * steptime;
            }
            this->step_next = std::min(step_present + 1, step_total);
            this->type_running = ANIMATION_STEP_UP;
            break;
    }
}

void StructDataStructure::updateTimeAnimation()
{
    double addTime = clock.getElapsedTime().asSeconds() * *speed;
    clock.restart();
    step_present = (int) ((time - 0.001) / steptime);

    switch (this->type_running)
    {
        case ANIMATION_PAUSE : break;
        case ANIMATION_PLAY :
            time = std::min(time + addTime, totaltime);
            break;
        case ANIMATION_STEP_DOWN : 
            time = std::max(step_next * steptime - 0.01, time - addTime);
            break;
        case ANIMATION_STEP_UP : 
            time = std::min(step_next * steptime - 0.01, time + addTime);
            break;
        default :
            std::cout << "Error struct_ds.hpp\n";
            exit(20);
    }
}
int StructDataStructure::update()
{
    if (this->running == false) return -1;
    updateTimeAnimation();
    return listStep[step_present];
}

// print
void StructDataStructure::refreshrender()
{
    if (this->running == true)
    {
        for(int i = 0; i < this->count_nodePrint; i++)
            nodeAnimation[i].runTime(time);
        for(int i = 0; i < count_arrowPrint; i++)
            arrowAnimation[i].runTime(time);
    }
}
void StructDataStructure::render()
{
    if (!this->isActive()) return;
    this->refreshrender();
    for(int i = 0; i < count_arrowPrint; i++) {
        listArrow[i].render(window);
    }
    for(int i = 0; i < count_nodePrint; i++)
        listNode[i]->render(window);
}