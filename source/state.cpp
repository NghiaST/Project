#include "state.hpp"

State::State(sf::RenderWindow *window)
{
    // setup text
    this->window = window;
    if (!this->font.loadFromFile("dat/roboto/Roboto-Medium.ttf")) {
        std::cout << "Error Load Font\n";
    }

    // setup std::vector<Button> buttonCategory
    std::vector<std::string> strarray = {"StaticArray", "DynamicArray", "LinkedList", "Stack", "Queue"};
    sf::Vector2f coord = sf::Vector2f(5, 5);
    sf::Vector2f velocity = sf::Vector2f(0, 55);
    sf::Vector2f sizeRec = sf::Vector2f(120, velocity.y - 5);

    for(std::string strname : strarray) {
        buttonCategory.push_back(Button(coord.x, coord.y, sizeRec.x, sizeRec.y, &this->font, true, true, strname, 14, TripleColor(sf::Color(255, 192, 203)), TripleColor(sf::Color::Green), TripleColor(sf::Color::Yellow), TripleColor(sf::Color::Blue), TripleColor(sf::Color::Blue)));
        coord += velocity;
    }
    setNewDS(0);
}
State::~State()
{
}

void State::setNewDS(int ds_new)
{
    buttonManipulate.clear();
    for(auto& vec : subbuttonManipulate) vec.clear();
    subbuttonManipulate.clear();
    for(auto& vec : boxarr) vec.clear();
    boxarr.clear();

    std::vector<std::string> strManipulate;
    std::vector<std::vector<std::string>> strsubManipulate;
    std::vector<std::vector<std::string>> strInputBox;

    switch (ds_new) {
        case 0 : case 1 : case 2 :
            strManipulate = {"Initialize", "Insert", "Remove", "Update", "Search"};
            strsubManipulate = {
                {"Empty", "Random", "Manual", "File"},
                {"First", "Last", "Manual"},
                {"First", "Last", "Manual"},
                {"Manual"},
                {"Manual"}
            };
            strInputBox = {
                {"Array=", "FileName="},
                {"Pos=", "Value="},
                {"Pos="},
                {"Pos=", "Value="},
                {"Value="}
            };
            this->cntManipulate = 5;
            break;
        case 3 :
            strManipulate = {"Initialize", "Peek", "Push", "Pop"};
            strsubManipulate = {
                {"Empty", "Random", "Manual", "File"},
                {"Peek"},
                {"Push"},
                {"Pop"},
            };
            strInputBox = {
                {"Array=", "FileName="},
                {},
                {"Value="},
                {}
            };
            this->cntManipulate = 4;
            break;
        case 4 :
            strManipulate = {"Initialize", "Peek", "Enqueue", "Dequeue"};
            strsubManipulate = {
                {"Empty", "Random", "Manual", "File"},
                {"Front", "Back"},
                {"Enqueue"},
                {"Dequeue"}
            };
            strInputBox = {
                {"Array=", "FileName="},
                {},
                {"Value="},
                {}
            };
            this->cntManipulate = 4;
            break;
        default :
            exit(1);
    }
       
    buttonCategory[ds_new].setStatus(2);
    subbuttonManipulate.resize(this->cntManipulate);
    boxarr.resize(this->cntManipulate);

    sf::Vector2f coord, velocity, sizeRec;

    // update manipulate: create, insert, remove, etc
    coord = sf::Vector2f(5, 500);
    velocity = sf::Vector2f(0, 35);
    sizeRec = sf::Vector2f(80, velocity.y - 5);
    for(std::string strname : strManipulate) 
    {
        buttonManipulate.push_back(Button(coord.x, coord.y, sizeRec.x, sizeRec.y, &this->font, true, false, strname, 14, TripleColor(sf::Color(255, 255, 153)), TripleColor(sf::Color::Green), TripleColor(sf::Color::Yellow), TripleColor(sf::Color::Blue), TripleColor(sf::Color::Blue)));
        coord += velocity;
    }

    // update submanipulate: create_empty, create_random, etc
    coord = sf::Vector2f(105, 502);
    velocity = sf::Vector2f(80, 35);
    sizeRec = sf::Vector2f(velocity.x - 5, 26);
    for(int i = 0; i < this->cntManipulate; i++)
    {
        sf::Vector2f coord2 = coord;
        for(std::string strname : strsubManipulate[i]) {
            subbuttonManipulate[i].push_back(Button(coord2.x, coord2.y, sizeRec.x, sizeRec.y, &this->font, false, false, strname, 12, TripleColor(sf::Color(220, 220, 220)), TripleColor(sf::Color::Green), TripleColor(sf::Color::Yellow), TripleColor(sf::Color::Blue), TripleColor(sf::Color::Blue)));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }
    
    // update inputBox
    coord = sf::Vector2f(450, 502);
    velocity = sf::Vector2f(200, 35);
    sizeRec = sf::Vector2f(velocity.x - 5, 26);
    for(int i = 0; i < this->cntManipulate; i++)
    {
        sf::Vector2f coord2 = coord;
        for(std::string nameBox : strInputBox[i]) {
            boxarr[i].push_back(InputBox(coord2.x, coord2.y, sizeRec.x, sizeRec.y, &this->font, false, nameBox));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }

    this->typeCategory = ds_new;
    this->typeManipulate = -1;
    this->typesubManipulate = -1;
}

void State::checkforQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
        this->quit = true;
}

// setvalue
void State::updateInputBox(int pos, int value)
{
    std::string strpos = std::to_string(pos);
    std::string strvalue = std::to_string(value);
    switch (this->typeCategory)
    {
        case 0 : case 1 : case 2 :
            boxarr[1][0].setWordInput(strpos);
            boxarr[2][0].setWordInput(strpos);
            boxarr[3][0].setWordInput(strpos);
            boxarr[4][0].setWordInput(strvalue);
            break;
        case 3 :
            break;
        case 4 :
            break;
    }
}

// getvalue
const bool &State::getQuit() const
{
    return this->quit;
}
std::string State::getValueButton(int typeManipulate, int id)
{
    if (this->boxarr[typeManipulate].size() <= id) 
        return "";
    return this->boxarr[typeManipulate][id].getTextInput();
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
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
    for(int i = 0; i < this->cntManipulate; i++)
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
                setNewDS(ret.x);
            }
            else {
                ret = sf::Vector2i(-1, -1);
            }
        }
        else { // 5 <= ret.x < 10
            for(Button& btn : subbuttonManipulate[ret.x - 5])
                btn.swapView();
            for(InputBox& box : boxarr[ret.x - 5])
                box.swapView();
            ret = sf::Vector2i(-1, -1);
        }
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
    for(int i = 0; i < cntManipulate; i++) {
        for(Button& butt : subbuttonManipulate[i])
            butt.render(window);
        for(InputBox& box : boxarr[i])
            box.render(window);
    }
}
