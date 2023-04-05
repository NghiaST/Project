#include "state.hpp"

State::State(sf::RenderWindow *window)
{
    // setup text
    this->window = window;
    if (!this->font.loadFromFile("dat/roboto/Roboto-Black.ttf")) {
        std::cout << "Error Load Font\n";
    }

    // setup std::vector<Button> buttonCategory
    std::vector<std::string> strarray = {"StaticArray", "DynamicArray", "LinkedList", "Stack", "Queue"};
    sf::Vector2f coord = sf::Vector2f(5, 5);
    sf::Vector2f velocity = sf::Vector2f(150, 0);

    for(std::string strname : strarray) {
        buttonCategory.push_back(Button(coord.x, coord.y, velocity.x - 2, 50, &this->font, strname, 15, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
        coord += velocity;
    }

    strarray = {"Init", "Add", "Delete", "Update", "Search"};
    coord = sf::Vector2f(5, 400);
    velocity = sf::Vector2f(0, 50);

    for(std::string strname : strarray) {
        buttonManipulate.push_back(Button(coord.x, coord.y, 100, velocity.y - 2, &this->font, strname, 15, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
        coord += velocity;
    }

    // setup std::vector<Button> childbutton[5]
    std::vector<std::vector<std::string>> vec2dstr = {
        {"Empty", "Random", "User Defined List", "External File"},
        {"Insert to the first", "Insert to the last", "Insert to the middle"},
        {"Delete at the first", "Delete at the last", "Delete at the middle"},
        {"Update"},
        {"Search"}
    };
    coord = sf::Vector2f(155, 410);
    velocity = sf::Vector2f(200, 50);
    for(int i = 0; i < 5; i++) {
        sf::Vector2f coord2 = coord;
        for(std::string strname : vec2dstr[i]) {
            subbuttonManipulate[i].push_back(Button(coord2.x, coord2.y, velocity.x - 2, 30, &this->font, strname, 12, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }

    // debug
    box = new InputBox(800, 500, 100, 100, &font);

    // state of button
    this->typeCategory = 0; // StaticArray
    this->typeManipulate = -1;
    this->typesubManipulate = -1;

    // Box
   // box = new InputBox(800, 500, 100, 100, &font);
}

State::~State()
{
}

const bool &State::getQuit() const
{
    return this->quit;
}

void State::checkforQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
        this->quit = true;
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::endState()
{
    std::cout << "End State\n";
}

sf::Vector2i State::update()
{
    this->updateMousePositions();
    this->checkforQuit();
    if (this->getQuit()) return sf::Vector2i(-1, -1);

    sf::Vector2i ret = sf::Vector2i(-1, -1);

    int cnt = 0;
    for(Button& butt : this->buttonCategory) {
        butt.update(this->mousePosView);
        if (butt.isPressed()) {
            ret.x = cnt;
            ret.y = -1;

            // update state of button
            // this->typeManipulate = NONE;
            // this->typesubManipulate = -1;
        }
        cnt++;
    }
    for(Button& butt : this->buttonManipulate) {
        butt.update(this->mousePosView);
        if (butt.isPressed()) {
            ret.x = cnt;
            ret.y = -1;
        }
        cnt++;
    }
    for(int i = 0; i < 5; i++)
    {
        if (this->activeManipulate[i] == false) continue;
        int cnt2 = 0;
        for(Button& butt : subbuttonManipulate[i]) {
            butt.update(this->mousePosView);
            if (butt.isPressed()) {
                ret.x = i + 5;
                ret.y = cnt2;
            }
            cnt2++;
        }
    }
    // update state of button
    if (ret.x != -1 && ret.y == -1) {
        if (ret.x < 5) {
            if (ret.x != this->typeCategory) {
                this->typeCategory = ret.x;
                this->typeManipulate = -1;
                this->typesubManipulate = -1;
            }
            else {
                ret.x = -1;
            }
        }
        else {
            this->activeManipulate[ret.x - 5] ^= 1;
        }
    }
    else if (ret.y != -1) {
        if (ret.x - 5 == this->typeManipulate && ret.y == this->typesubManipulate) {
            /*ret.x = -1;
            ret.y = -1;
            this->typeManipulate = -1;
            this->typesubManipulate = -1;*/
        }
        else {
            this->typeManipulate = ret.x - 5;
            this->typesubManipulate = ret.y;
        }
    }
    
    std::cout << ret.x << ' ' << ret.y << " W2\n";
    return ret;
}

void State::render()
{
    if (this->getQuit()) return;
    for(Button& butt : buttonCategory)
        butt.render(window);
    for(Button& butt : buttonManipulate)
        butt.render(window);
    for(int i = 0; i < 5; i++) {
        if (this->activeManipulate[i] == true) {
            for(Button& butt : subbuttonManipulate[i])
                butt.render(window);
        }
    }
    
    box->render(window);
}

// void State::Input_Add_InsertTheMiddle() {}
// void State::Input_Delete_DeleteAtTheMiddle() {}
// void State::Input_Update_Update() {}
// void State::Input_Search_Search() {}
// void State::Build_Input() {}