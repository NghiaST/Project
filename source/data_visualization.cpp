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
    for(int i = 0; i < 30; i++)
    {
        sf::Texture& texture = const_cast<sf::Texture&>(font.getTexture(i));
        texture.setSmooth(false);
        sf::Texture& texture2 = const_cast<sf::Texture&>(fontNode.getTexture(i));
        texture2.setSmooth(false);
    }
}

void DataVisualization::InitThemes()
{
    Themes* LightMode = new Themes();
    Themes* DarkMode = new Themes();

    LightMode->setBackground(sf::Color(220, 220, 220));
    LightMode->setNode(Palette(
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::Black),
        ElementColor(sf::Color::White        , sf::Color(255, 79, 5)   , sf::Color(255, 79, 5)),
        ElementColor(sf::Color(255, 100, 0)  , sf::Color::White        , sf::Color(255, 100, 0)),
        ElementColor(sf::Color::Cyan         , sf::Color::Blue         , sf::Color(39, 154, 248)),
        ElementColor(sf::Color::Green        , sf::Color::Red          , sf::Color::Green)
    ));
    LightMode->setArrow(Palette(
        ElementColor(sf::Color::Black        , sf::Color::Transparent  , sf::Color::Black),
        ElementColor(sf::Color(255, 165, 0)  , sf::Color::Transparent  , sf::Color(255, 165, 0)),
        ElementColor(sf::Color::White        , sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::Transparent  , sf::Color::Transparent  , sf::Color::Transparent)
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
        ElementColor(sf::Color(15, 234, 108) , sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color(34, 137, 221) , sf::Color::Black        , sf::Color::Black),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black),
        ElementColor(sf::Color::Transparent  , sf::Color::Blue         , sf::Color::Black)
    )); /// should be change

    DarkMode->setBackground(sf::Color(40, 40, 40));
    DarkMode->setNode(Palette(
        ElementColor(sf::Color::Black        , sf::Color::White          , sf::Color::White),
        ElementColor(sf::Color::White        , sf::Color(255, 79, 5)   , sf::Color(255, 79, 5)),
        ElementColor(sf::Color(255, 100, 0)  , sf::Color::White        , sf::Color(255, 100, 0)),
        ElementColor(sf::Color::Cyan         , sf::Color::Blue         , sf::Color(39, 154, 248)),
        ElementColor(sf::Color::Green        , sf::Color::Red          , sf::Color::Green)
    ));
    DarkMode->setArrow(Palette(
        ElementColor(sf::Color::White        , sf::Color::Transparent  , sf::Color::White),
        ElementColor(sf::Color(128, 255, 0)  , sf::Color::Transparent  , sf::Color(128, 255, 0)),
        ElementColor(sf::Color::White        , sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::White        , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::Transparent  , sf::Color::Transparent  , sf::Color::Transparent)
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
        ElementColor(sf::Color(57, 72, 103)  , sf::Color::White        , sf::Color::White),
        ElementColor(sf::Color::Green        , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::Blue         , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::Blue         , sf::Color::Red          , sf::Color::White),
        ElementColor(sf::Color::Blue         , sf::Color::Red          , sf::Color::White)
    )); /// should be change

    listTheme.push_back(LightMode);
    listTheme.push_back(DarkMode);

    typetheme = 0;
    theme = new Themes();
    theme->setTheme(listTheme[typetheme]);
}

void DataVisualization::InitSpeed()
{
    listSpeed = {0.1, 0.25, 0.5, 1, 2, 3, 4, 8, 16, 32};
    typespeed = 5;
    speed = listSpeed[typespeed];
}
//// Initializations functions
// Constructors/Destructors
DataVisualization::DataVisualization()
{
    this->active = true;
    this->InitWindow();
    this->InitThemes(); // LightMode, DarkMode
    this->InitFont();
    this->InitSpeed();
    this->settings = new VisualizationSettings(window, &font, &fontNode, theme, &speed);

    this->states = new State(settings);
    theme->setTheme(listTheme[typetheme]);
    this->ds_present = DS_STATICARRAY;
    this->DataStructure = std::make_unique<StructStaticArray>(settings, true);
}

DataVisualization::~DataVisualization()
{
    delete this->window;
    delete this->states;
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
            keyboard = static_cast<KEYBOARD> (sfEvent.text.unicode);
    }
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
    sf::Vector2i DataNode = DataStructure->updateKBM(mousePosView, mouseType, keyboardType);
    if (DataNode.x != -1)
        states->updateInputBox(DataNode.x, DataNode.y);
    sf::Vector2i typePress = states->update(mouseType, keyboardType);

    if (typePress.x != -1) {
        std::cout << "Press " << typePress.x << ' ' << typePress.y << '\n';
        if (0 <= typePress.x && typePress.x < 100) {
            ds_present = static_cast<DATA_STRUCTURE>(typePress.x);
            switch(ds_present) {
                case DS_STATICARRAY        : DataStructure = std::make_unique<StructStaticArray>(settings, true); break;
                case DS_DYNAMICARRAY       : DataStructure = std::make_unique<StructDynamicArray>(settings, true); break;
                case DS_SIMPLYLINKEDLIST   : DataStructure = std::make_unique<StructSimplyLinkedList>(settings, true); break;
                case DS_DOUBLYLINKEDLIST   : DataStructure = std::make_unique<StructDoublyLinkedList>(settings, true); break;
                case DS_CIRCULARLINKEDLIST : DataStructure = std::make_unique<StructCircularLinkedList>(settings, true); break;
                case DS_STACK              : DataStructure = std::make_unique<StructStack>(settings, true); break;
                case DS_QUEUE              : DataStructure = std::make_unique<StructQueue>(settings, true); break;
                default : break;
            }
        }
        else if (100 <= typePress.x && typePress.x < 200) {
            typePress.x -= 100;
            std::vector<std::string> vecStr = states->getInputBox(typePress.x);
            DataStructure->run(typePress.x, typePress.y, vecStr);

            int Manipulate = DataStructure->getManipulate();
            int subManipulate = DataStructure->getsubManipulate();

            states->updateBtnCode(Manipulate, subManipulate);
        }
        else if (typePress.x == 200) {
            typetheme = typePress.y;
            settings->setTheme(listTheme[typetheme]);
        }
        else if (typePress.x == 300) {
            DataStructure->updateTypeAnimation(typePress.y);
        }
        else if (typePress.x == 400) {
            if (typePress.y == 1) typespeed = std::min(typespeed + 1, (int)listSpeed.size() - 1);
            else typespeed = std::max(typespeed - 1, 0);
            settings->setSpeed(listSpeed[typespeed]);
        }
    }

    int step;
    step = DataStructure->update();
    states->updateBtnStep(step);
}

void DataVisualization::render()
{
    if (!window->isOpen()) return;
    this->window->clear(*this->theme->getBackground());

    DataStructure->render();
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