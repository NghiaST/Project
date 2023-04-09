#include "data_visualization.hpp"

// Initializations
void DataVisualization::InitWindow() 
{
    // sf::Vector2f windowsize = sf::Vector2f(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80);
    sf::Vector2f windowsize = sf::Vector2f(1346, 688);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    this->window = new sf::RenderWindow(sf::VideoMode(windowsize.x, windowsize.y, 30), "Le Huu Nghia 22125064 - Data Visualizations", sf::Style::Default, settings);
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
    this->ds_present = DS_STATICARRAY;
    this->StaticArray  = new StructStaticArray(window, true);
    this->DynamicArray = new StructDynamicArray(window, false);
    this->LinkedList   = new StructLinkedList(window, false);
    this->Stack        = new StructStack(window, false);
    this->Queue        = new StructQueue(window, false);

    this->Light = sf::Color(220, 220, 220);
    this->Dark = sf::Color(150, 150, 150);
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
    sf::Vector2i DataNode;
    switch (ds_present) {
        case DS_STATICARRAY  : DataNode = StaticArray ->update(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_DYNAMICARRAY : DataNode = DynamicArray->update(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_LINKEDLIST   : DataNode = LinkedList  ->update(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_STACK        : DataNode = Stack       ->update(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_QUEUE        : DataNode = Queue       ->update(this->mousePosView, this->mouseType, this->keyboardType); break;
        default: exit(2);
    }
    //sf::Vector2i DataNode = get_DS(ds_present)->update(this->mousePosView, this->mouseType, this->keyboardType);
    if (DataNode.x != -1)
        this->states->updateInputBox(DataNode.x, DataNode.y);
    sf::Vector2i typePress = this->states->update(this->mouseType, this->keyboardType);

    if (typePress.x != -1) {
        std::cout << "Press " << typePress.x << ' ' << typePress.y << '\n';
        if (typePress.x < 5) {
            switch (ds_present) {
                case DS_STATICARRAY  : StaticArray ->turn_off(); break;
                case DS_DYNAMICARRAY : DynamicArray->turn_off(); break;
                case DS_LINKEDLIST   : LinkedList  ->turn_off(); break;
                case DS_STACK        : Stack       ->turn_off(); break;
                case DS_QUEUE        : Queue       ->turn_off(); break;
                default: exit(2);
            }
            //get_DS(ds_present)->turn_off();
            ds_present = static_cast<DATA_STRUCTURE>(typePress.x);
            switch (ds_present) {
                case DS_STATICARRAY  : StaticArray ->turn_on(); break;
                case DS_DYNAMICARRAY : DynamicArray->turn_on(); break;
                case DS_LINKEDLIST   : LinkedList  ->turn_on(); break;
                case DS_STACK        : Stack       ->turn_on(); break;
                case DS_QUEUE        : Queue       ->turn_on(); break;
                default: exit(2);
            }
            //get_DS(ds_present)->turn_on();
        }
        else if (typePress.x > 4) {
            typePress.x -= 5;
            std::string str1 = states->getValueButton(typePress.x, 0);
            std::string str2 = states->getValueButton(typePress.x, 1);
            switch (ds_present) {
                case DS_STATICARRAY  : StaticArray ->run(typePress.x, typePress.y, str1, str2); break;
                case DS_DYNAMICARRAY : DynamicArray->run(typePress.x, typePress.y, str1, str2); break;
                case DS_LINKEDLIST   : LinkedList  ->run(typePress.x, typePress.y, str1, str2); break;
                case DS_STACK        : Stack       ->run(typePress.x, typePress.y, str1, str2); break;
                case DS_QUEUE        : Queue       ->run(typePress.x, typePress.y, str1, str2); break;
                default: exit(2);
            }
            //get_DS(ds_present)->run(typePress.x, typePress.y, str1, str2);
        }
    }
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    this->window->clear(this->Light);

    switch (ds_present) {
        case DS_STATICARRAY  : StaticArray ->render(); break;
        case DS_DYNAMICARRAY : DynamicArray->render(); break;
        case DS_LINKEDLIST   : LinkedList  ->render(); break;
        case DS_STACK        : Stack       ->render(); break;
        case DS_QUEUE        : Queue       ->render(); break;
        default: exit(2);
    }
    //get_DS(ds_present)->render();

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