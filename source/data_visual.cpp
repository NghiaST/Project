#include "data_visual.hpp"

// Initializations
void DataVisualization::InitWindow() 
{
    // sf::Vector2f windowsize = sf::Vector2f(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80);
    sf::Vector2f windowsize = sf::Vector2f(1346, 688);
    this->window = new sf::RenderWindow(sf::VideoMode(windowsize.x, windowsize.y, 30), "Le Huu Nghia 22125064 - Data Visualizations", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(0, 0));
    // this->window->setFramerateLimit(60);
    // ::ShowWindow(this->window->getSystemHandle(), SW_MAXIMIZE);
}

void DataVisualization::InitStates()
{
    this->states = new State(this->window);
}

//// Initializations functions

// Constructors/Destructors
DataVisualization::DataVisualization()
{
    this->active = true;
    this->InitWindow();
    this->InitStates();
    this->page_present = PAGE_STATICARRAY;
    this->StaticArray  = new StructStaticArray(window, true);
    this->DynamicArray = new StructDynamicArray(window, false);
    this->LinkedList   = new StructStaticArray(window, false);
    this->Stack        = new StructStaticArray(window, false);
    this->Queue        = new StructStaticArray(window, false);
}

DataVisualization::~DataVisualization()
{
    delete this->window;
    delete this->states;
    delete this->StaticArray;
    delete this->DynamicArray;
    delete this->LinkedList;
    delete this->Stack;
    delete this->Queue;
}

int cnt;
// Functions
void DataVisualization::processEvents()
{
    sf::Event sfEvent;
    int keyboard = 0, mouse = 0;
    while (this->window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) this->window->close();
        if (sfEvent.type == sf::Event::TextEntered)
            keyboard = sfEvent.text.unicode;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window->close();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouse = 1;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) mouse = 2;

    this->keyboardType = keyboard;
    switch (mouse)
    {
        case MSE_NONE : // none
            this->mouseType = 0;
            break;
        case MSE_LEFTCLICK : 
            if (this->mouseType == MSE_LEFTCLICK || this->mouseType == MSE_LEFTHOLD)
                this->mouseType = MSE_LEFTHOLD;
            else this->mouseType = MSE_LEFTCLICK;
            break;
        case MSE_RIGHTCLICK : 
            if (this->mouseType == MSE_RIGHTCLICK || this->mouseType == MSE_RIGHTHOLD)
                this->mouseType = MSE_RIGHTHOLD;
            else this->mouseType = MSE_RIGHTCLICK;
            break;
        default :
            this->mouseType = 0;
            break;
    }
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

}

void DataVisualization::update()
{   
    if (!window->isOpen()) return;
    #define get_PAGE(x) (x != 4 ? x != 3 ? x != 2 ? x != 1 ? StaticArray : DynamicArray : LinkedList : Stack : Queue)
    
    sf::Vector2i DataNode = get_PAGE(page_present)->update(this->mousePosView, this->mouseType, this->keyboardType);
    if (DataNode.x != -1)
        this->states->updateInputBox(DataNode.x, DataNode.y);
    sf::Vector2i typePress = this->states->update(this->mouseType, this->keyboardType);

    if (typePress.x != -1) {
        std::cout << "Press " << typePress.x << ' ' << typePress.y << '\n';
        if (typePress.x < 5) {
            get_PAGE(page_present)->turn_off();
            page_present = static_cast<PAGE>(typePress.x);
            get_PAGE(page_present)->turn_on();
        }
        else if (typePress.x > 4) {
            get_PAGE(page_present)->run(typePress.x - 5, typePress.y, states->getValueButton(typePress.x - 5, 0), states->getValueButton(typePress.x - 5, 1));
        }
    }
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    //this->window->clear(sf::Color(235, 235, 235));
    this->window->clear(sf::Color(150, 150, 150));

    if (page_present == PAGE_STATICARRAY)  StaticArray->render();
    if (page_present == PAGE_DYNAMICARRAY) DynamicArray->render();
    if (page_present == PAGE_LINKEDLIST)   LinkedList->render();
    if (page_present == PAGE_STACK)        Stack->render();
    if (page_present == PAGE_QUEUE)        Queue->render();

    this->states->render();
    this->window->display();
}

void DataVisualization::run()
{
    while (this->window->isOpen()) {
        processEvents();
        update();
        render();
    }
}