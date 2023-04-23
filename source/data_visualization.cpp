#include "data_visualization.hpp"

// Initializations
void DataVisualization::InitWindow() 
{
    sf::Vector2u windowsize = sf::Vector2u(1346, 688);
    unsigned int antialiasinglevel = 8;

    sf::ContextSettings cSettings;
    cSettings.antialiasingLevel = antialiasinglevel;

    this->window = new sf::RenderWindow(sf::VideoMode(windowsize.x, windowsize.y, 60), "Le Huu Nghia 22125064 - Data Visualization", sf::Style::Default, cSettings);
    this->window->setPosition(sf::Vector2i(0, 0));
    // sf::Vector2f windowsize = sf::Vector2f(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 80);
    // ::ShowWindow(this->window->getSystemHandle(), SW_MAXIMIZE);
}

void DataVisualization::InitFont()
{
    if (!this->font.loadFromFile("dat/roboto/Roboto-Medium.ttf"))
        std::cout << "Error Load Font\n";
    if (!this->fontNode.loadFromFile("dat/arial_bold.ttf"))
        std::cout << "Error Load Font 2\n";
}

void DataVisualization::InitThemes()
{
    Themes* LightMode = new Themes();
    Themes* DarkMode = new Themes();

    LightMode->setBackground(sf::Color(220, 220, 220));

    LightMode->setNode(Palette(
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::Black),
        ElementColor(sf::Color(247, 239, 159), sf::Color(255, 109, 96) , sf::Color::Black),
        ElementColor(sf::Color(255, 109, 96) , sf::Color(243, 239, 159), sf::Color::Black),
        ElementColor(sf::Color::Cyan         , sf::Color::Blue         , sf::Color(39, 154, 248)),
        ElementColor(sf::Color(126, 244, 19) , sf::Color(210, 19, 18)  , sf::Color(210, 19, 18))
    ));
    LightMode->setArrow(Palette(
        ElementColor(sf::Color::Black        , sf::Color::Transparent  , sf::Color::Black),
        ElementColor(sf::Color(255, 165, 0)  , sf::Color::Transparent  , sf::Color(255, 165, 0)),
        ElementColor(sf::Color::White        , sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::White)
    ));
    LightMode->setButtonDs(Palette(
        ElementColor(sf::Color(255, 255, 153), sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color(34, 137, 221) , sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color::Yellow       , sf::Color::Black        , sf::Color::Red),
        ElementColor(sf::Color(34, 137, 221) , sf::Color::Black        , sf::Color::Red),
        ElementColor(sf::Color(34, 137, 221)  , sf::Color::Black        , sf::Color::Black)
    ));
    LightMode->setButtonManipulate(Palette(
        ElementColor(sf::Color(112, 214, 252), sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color(34, 137, 221) , sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color::Yellow       , sf::Color::Black        , sf::Color::Red),
        ElementColor(sf::Color::Blue         , sf::Color::Black        , sf::Color::Red),
        ElementColor(sf::Color::Blue         , sf::Color::Black        , sf::Color::Black)
    ));
    LightMode->setButtonSubmanipulate(Palette(
        ElementColor(sf::Color(220, 220, 220), sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color(34, 137, 221) , sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color::Yellow       , sf::Color::Black        , sf::Color::Red),
        ElementColor(sf::Color::Blue         , sf::Color::Black        , sf::Color::Red),
        ElementColor(sf::Color::Blue         , sf::Color::Black        , sf::Color::Black)
    ));
    LightMode->setButtonInputbox(Palette(
        ElementColor(sf::Color(255, 171, 171), sf::Color::Black , sf::Color::Black),
        ElementColor(sf::Color(34, 137, 221) , sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color(255, 109, 96) , sf::Color(243, 239, 159), sf::Color::Red),
        ElementColor(sf::Color(245, 194, 117), sf::Color::Red          , sf::Color(210, 19, 18)),
        ElementColor(sf::Color(126, 244, 19) , sf::Color::Red          , sf::Color::Black)
    ));
    LightMode->setButtonStep(Palette(
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black)
    )); /// should be change

    DarkMode->setBackground(sf::Color(40, 40, 40));
    DarkMode->setNode(Palette(
        ElementColor(sf::Color::Black        , sf::Color::White          , sf::Color::White),
        ElementColor(sf::Color(247, 239, 159), sf::Color(255, 109, 96) , sf::Color::Black),
        ElementColor(sf::Color(255, 109, 96) , sf::Color(243, 239, 159), sf::Color::Black),
        ElementColor(sf::Color::Cyan         , sf::Color::Blue         , sf::Color(39, 154, 248)),
        ElementColor(sf::Color(126, 244, 19) , sf::Color(210, 19, 18)  , sf::Color(210, 19, 18))
    ));
    DarkMode->setArrow(Palette(
        ElementColor(sf::Color::White        , sf::Color::Transparent  , sf::Color::White),
        ElementColor(sf::Color(128, 255, 0)  , sf::Color::Transparent  , sf::Color(128, 255, 0)),
        ElementColor(sf::Color::White        , sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::White)  
    ));
    DarkMode->setButtonDs(Palette(
        ElementColor(sf::Color(183, 30, 56), sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White),
        ElementColor(sf::Color::Yellow       , sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White)
    ));
    DarkMode->setButtonManipulate(Palette(
        ElementColor(sf::Color(57, 24, 188), sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White),
        ElementColor(sf::Color::Yellow       , sf::Color::Red        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White)
    ));
    DarkMode->setButtonSubmanipulate(Palette(
        ElementColor(sf::Color(40, 40, 40), sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White),
        ElementColor(sf::Color::Yellow       , sf::Color::Black        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Black        , sf::Color::White),
        ElementColor(sf::Color::Blue         , sf::Color::Black        , sf::Color::White)
    ));
    DarkMode->setButtonInputbox(Palette(
        ElementColor(sf::Color::Black        , sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red        , sf::Color::White),
        ElementColor(sf::Color(255, 109, 96) , sf::Color(243, 239, 159), sf::Color::White),
        ElementColor(sf::Color(245, 194, 117), sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color(126, 244, 19) , sf::Color::Red          , sf::Color::White)
    ));
    DarkMode->setButtonStep(Palette(
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::White),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::White),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::White)
    )); /// should be change

    listTheme.push_back(LightMode);
    listTheme.push_back(DarkMode);

    typetheme = 0;
    theme = new Themes();
    theme->setTheme(listTheme[typetheme]);
}

//// Initializations functions
// Constructors/Destructors
DataVisualization::DataVisualization()
{
    this->active = true;
    this->InitWindow();
    this->InitThemes(); // LightMode, DarkMode
    this->InitFont();
    this->speed = 1;
    this->settings = new VisualizationSettings(window, &font, &fontNode, theme, &speed);

    this->states = new State(settings);
    theme->setTheme(listTheme[typetheme]);
    this->ds_present = DS_STATICARRAY;
    this->StaticArray  = new StructStaticArray(settings, true);
    this->DynamicArray = new StructDynamicArray(settings, false);
    this->LinkedList   = new StructLinkedList(settings, false);
    this->Stack        = new StructStack(settings, false);
    this->Queue        = new StructQueue(settings, false);
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
    for(Themes *theme : this->listTheme)
        delete theme;
}

// Functions
void DataVisualization::processEvents()
{
    sf::Event sfEvent;
    KEYBOARD keyboard = KBD_NONE;
    MOUSE mouse = MSE_NONE;
    while (this->window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) this->window->close();
        if (sfEvent.type == sf::Event::TextEntered)
            // keyboard = static_cast<MOUSE> (sfEvent.text.unicode);
            keyboard = static_cast<KEYBOARD> (sfEvent.text.unicode);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->window->close();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouse = MSE_LEFTCLICK;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) mouse = MSE_LEFTHOLD;

    this->keyboardType = keyboard;
    if (keyboardType != KBD_NONE) std::cout << keyboardType << '\n';
    switch (mouse)
    {
        case MSE_NONE :
            this->mouseType = MSE_NONE;
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
            this->mouseType = MSE_NONE;
            break;
    }
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void DataVisualization::update()
{
    if (!window->isOpen()) return;
    sf::Vector2i DataNode;
    switch (ds_present) {
        case DS_STATICARRAY  : DataNode = StaticArray ->updateKBM(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_DYNAMICARRAY : DataNode = DynamicArray->updateKBM(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_LINKEDLIST   : DataNode = LinkedList  ->updateKBM(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_STACK        : DataNode = Stack       ->updateKBM(this->mousePosView, this->mouseType, this->keyboardType); break;
        case DS_QUEUE        : DataNode = Queue       ->updateKBM(this->mousePosView, this->mouseType, this->keyboardType); break;
        default: exit(2);
    }
    //sf::Vector2i DataNode = get_DS(ds_present)->update(this->mousePosView, this->mouseType, this->keyboardType);
    if (DataNode.x != -1)
        this->states->updateInputBox(DataNode.x, DataNode.y);
    sf::Vector2i typePress = this->states->update(this->mouseType, this->keyboardType);

    if (typePress.x != -1) {
        std::cout << "Press " << typePress.x << ' ' << typePress.y << '\n';
        if (0 <= typePress.x && typePress.x < 100) {
            switch (ds_present) {
                case DS_STATICARRAY  : StaticArray ->turn_off(); break;
                case DS_DYNAMICARRAY : DynamicArray->turn_off(); break;
                case DS_LINKEDLIST   : LinkedList  ->turn_off(); break;
                case DS_STACK        : Stack       ->turn_off(); break;
                case DS_QUEUE        : Queue       ->turn_off(); break;
                default: std::cout << "Error datavisualization 1 \n"; exit(2);
            }
            //get_DS(ds_present)->turn_off();
            ds_present = static_cast<DATA_STRUCTURE>(typePress.x);
            switch (ds_present) {
                case DS_STATICARRAY  : StaticArray ->turn_on(); break;
                case DS_DYNAMICARRAY : DynamicArray->turn_on(); break;
                case DS_LINKEDLIST   : LinkedList  ->turn_on(); break;
                case DS_STACK        : Stack       ->turn_on(); break;
                case DS_QUEUE        : Queue       ->turn_on(); break;
                default: std::cout << "Error datavisualization 2 \n"; exit(2);
            }
            //get_DS(ds_present)->turn_on();
        }
        else if (100 <= typePress.x && typePress.x < 200) {
            typePress.x -= 100;
            std::string str1 = states->getValueButton(typePress.x, 0);
            std::string str2 = states->getValueButton(typePress.x, 1);
            switch (ds_present) {
                case DS_STATICARRAY  : StaticArray ->run(typePress.x, typePress.y, str1, str2); break;
                case DS_DYNAMICARRAY : DynamicArray->run(typePress.x, typePress.y, str1, str2); break;
                case DS_LINKEDLIST   : LinkedList  ->run(typePress.x, typePress.y, str1, str2); break;
                case DS_STACK        : Stack       ->run(typePress.x, typePress.y, str1, str2); break;
                case DS_QUEUE        : Queue       ->run(typePress.x, typePress.y, str1, str2); break;
                default: std::cout << "Error datavisualization 3 \n"; exit(2);
            }
            //get_DS(ds_present)->run(typePress.x, typePress.y, str1, str2);
        }
        else if (200 <= typePress.x && typePress.x < 300) {
            typetheme = typePress.x - 200;
            theme->setTheme(listTheme[typetheme]);
        }
        else if (300 <= typePress.x && typePress.x < 400) {
            switch (ds_present) {
                case DS_STATICARRAY  : StaticArray ->updateTypeAnimation(typePress.x - 300); break;
                case DS_DYNAMICARRAY : DynamicArray->updateTypeAnimation(typePress.x - 300); break;
                case DS_LINKEDLIST   : LinkedList  ->updateTypeAnimation(typePress.x - 300); break;
                case DS_STACK        : Stack       ->updateTypeAnimation(typePress.x - 300); break;
                case DS_QUEUE        : Queue       ->updateTypeAnimation(typePress.x - 300); break;
                default: std::cout << "Error datavisualization 3 \n"; exit(2);
            }
        }
    }
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    this->window->clear(*this->theme->getBackground());

    switch (ds_present) {
        case DS_STATICARRAY  : StaticArray ->render(); break;
        case DS_DYNAMICARRAY : DynamicArray->render(); break;   
        case DS_LINKEDLIST   : LinkedList  ->render(); break;
        case DS_STACK        : Stack       ->render(); break;
        case DS_QUEUE        : Queue       ->render(); break;
        default: std::cout << "Error datavisualization 4 \n"; exit(2);
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