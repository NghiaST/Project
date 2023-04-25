#include <SFML/Graphics.hpp>
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

// Initialize
void StructDataStructure::Initialize_Empty() 
{
    this->sizearray = 0;
}
void StructDataStructure::Initialize_Random()
{
    this->sizearray = Rand(2, this->maxsize);
    for(int i = 0; i < this->sizearray; i++) elements[i] = Rand(0, 999);
}
void StructDataStructure::Initialize_Manual(std::vector<int> arr) 
{
    this->sizearray = (arr.size() < this->maxsize ? arr.size() : this->maxsize);
    for(int i = 0; i < this->sizearray; i++) 
        this->elements[i] = arr[i];
}
void StructDataStructure::Initialize_ExternalFile(std::string filename) 
{
    // haven't know
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return;
    }
    std::string content;
    std::string line;

    while (std::getline(file, line))
    {
        content += line + ' ';
    }
    file.close();
    // debug
    std::cout << "Debug External file\n";

    this->Initialize_Manual(string_to_array(content));
}

// Insert
void StructDataStructure::Insert_First(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't Insert new elements\n";
        return;
    }
    for(int i = sizearray - 1; i >= 0; i--) {
        elements[i + 1] = elements[i];
    }
    elements[0] = value;
    sizearray++;
}
void StructDataStructure::Insert_Last(int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't Insert new elements\n";
        return;
    }
    elements[sizearray++] = value;
}
void StructDataStructure::Insert_Manual(int pos, int value) 
{
    if (sizearray == maxsize) {
        std::cout << "The array has full of elements. Can't Insert new elements\n";
        return;
    }
    sizearray++;
    for(int i = sizearray - 2; i >= pos; i--) {
        elements[i + 1] = elements[i];
    }
    elements[pos] = value;
}

// Delete
void StructDataStructure::Del_First()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    std::rotate(elements.begin(), elements.begin() + 1, elements.begin() + sizearray);
    sizearray--;
}
void StructDataStructure::Del_Last()
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    sizearray--;
}
void StructDataStructure::Del_Manual(int pos)
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't delete elements\n";
        return;
    }
    std::rotate(elements.begin() + pos, elements.begin() + pos + 1, elements.begin() + sizearray);
    sizearray--;
}

// Update
void StructDataStructure::Update(int pos, int value) 
{
    if (sizearray == 0) {
        std::cout << "The array has no elements. Can't update elements\n";
        return;
    }
    if (pos < 0) pos = 0;
    if (pos >= maxsize) pos = maxsize - 1;
    this->elements[pos] = value;
}

// Search
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
    std::cout << "Can't find value\n";
    return -1;
}

void StructDataStructure::turn_on()
{
    this->active = true;
    this->run(0, 1, "", ""); // Initialize_Random
}

void StructDataStructure::turn_off()
{
    this->active = false;
}

const bool &StructDataStructure::isActive() const
{
    return this->active;
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

void StructDataStructure::activeAnimation()
{
    this->running = true;
    this->time = 0;
    this->type_running = ANIMATION_PLAY;
    this->step_present = 0;
    clock.restart();
}