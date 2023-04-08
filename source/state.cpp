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
        buttonCategory.push_back(Button(coord.x, coord.y, velocity.x - 5, 50, &this->font, true, true, strname, 15, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow, sf::Color::Blue));
        coord += velocity;
    }
    buttonCategory[0].setStatus(3);

    strarray = {"Init", "Add", "Delete", "Update", "Search"};
    coord = sf::Vector2f(5, 400);
    velocity = sf::Vector2f(0, 50);

    for(std::string strname : strarray) {
        buttonManipulate.push_back(Button(coord.x, coord.y, 100, velocity.y - 5, &this->font, true, false, strname, 15, sf::Color(220, 220, 220, 255), sf::Color::Green, sf::Color::Yellow, sf::Color::Blue));
        coord += velocity;
    }

    // setup std::vector<Button> subbuttonManipulate[5]
    std::vector<std::vector<std::string>> vec2dstr = {
        {"Empty", "Random", "Manual", "External File"},
        {"First", "Last", "Manual"},
        {"First", "Last", "Manual"},
        {"Manual"},
        {"Manual"}
    };
    coord = sf::Vector2f(155, 410);
    velocity = sf::Vector2f(120, 50);
    for(int i = 0; i < 5; i++) {
        sf::Vector2f coord2 = coord;
        for(std::string strname : vec2dstr[i]) {
            subbuttonManipulate[i].push_back(Button(coord2.x, coord2.y, velocity.x - 5, 30, &this->font, false, false, strname, 12, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow, sf::Color::Blue));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }

    // std::vector<std::vector<InputBox>>
    std::vector<std::vector<std::string>> nameInputBox = {
        {"Array="},
        {"Pos=", "Value="},
        {"Pos="},
        {"Pos=", "Value="},
        {"Value="}
    };
    boxarr.resize(5);
    coord = sf::Vector2f(750, 410);
    velocity = sf::Vector2f(150, 50);
    for(int i = 0; i < 5; i++) {
        sf::Vector2f coord2 = coord;
        for(std::string nameBox : nameInputBox[i]) {
            boxarr[i].push_back(InputBox(coord2.x, coord2.y, velocity.x - 5, 30, &this->font, false, nameBox));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }

    // debug
    //box = new InputBox(800, 500, 100, 100, &font, "text = ");

    // state of button
    this->typeCategory = 0; // StaticArray
    this->typeManipulate = -1;
    this->typesubManipulate = -1;
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

sf::Vector2i State::update(int mouseType, int keyboardType)
{
    this->updateMousePositions();
    if (this->getQuit()) return sf::Vector2i(-1, -1);

    sf::Vector2i ret = sf::Vector2i(-1, -1);
    int cnt = 0;
    for(Button& btn : this->buttonCategory) {
        btn.update(this->mousePosView, mouseType);
        if (btn.isPressed()) {
            ret.x = cnt;
            ret.y = -1;
        }
        cnt++;
    }
    
    for(Button& btn : this->buttonManipulate) {
        btn.update(this->mousePosView, mouseType);
        if (btn.isPressed()) {
            ret.x = cnt;
            ret.y = -1;
        }
        cnt++;
    }
    for(int i = 0; i < 5; i++)
    {
        int cnt2 = 0;
        for(Button& btn : subbuttonManipulate[i]) {
            btn.update(this->mousePosView, mouseType);
            if (btn.isPressed()) {
                ret.x = i + 5;
                ret.y = cnt2;
            }
            cnt2++;
        }
        for(InputBox& box : boxarr[i])
            box.update(this->mousePosView, mouseType, keyboardType);
    }
    // update state of button
    if (mouseType != MSE_LEFTCLICK) ret = sf::Vector2i(-1, -1);
    if (ret.x != -1 && ret.y == -1) {
        if (ret.x < 5) {
            if (ret.x != this->typeCategory) {
                this->buttonCategory[this->typeCategory].setStatus(0);
                this->typeCategory = ret.x;
                this->typeManipulate = -1;
                this->typesubManipulate = -1;
            }
            else {
                ret.x = -1;
            }
        }
        else {
            for(Button& btn : subbuttonManipulate[ret.x - 5])
                btn.changeView();
            for(InputBox& box : boxarr[ret.x - 5])
                box.changeView();
        }
        ret = sf::Vector2i(-1, -1);
    }
    else if (ret.y != -1) {
        this->typeManipulate = ret.x - 5;
        this->typesubManipulate = ret.y;
    }
    
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
        for(Button& butt : subbuttonManipulate[i])
            butt.render(window);
        for(InputBox& box : boxarr[i])
            box.render(window);
    }
}

// void State::Input_Add_InsertTheMiddle() {}
// void State::Input_Delete_DeleteAtTheMiddle() {}
// void State::Input_Update_Update() {}
// void State::Input_Search_Search() {}
// void State::Build_Input() {}