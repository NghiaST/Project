#include "state.hpp"

State::State(sf::RenderWindow *window)
{
    // setup text
    this->window = window;
    if (!this->font.loadFromFile("dat/roboto/Roboto-Black.ttf")) {
        std::cout << "Error Load Font\n";
    }

    // setup std::vector<Button> listbutton
    std::vector<std::string> strarray = {"StaticArray", "DynamicArray", "LinkedList", "Stack", "Queue"};
    sf::Vector2f coord = sf::Vector2f(5, 5);
    sf::Vector2f velocity = sf::Vector2f(150, 0);

    for(std::string strname : strarray) {
        listbutton.push_back(Button(coord.x, coord.y, velocity.x - 2, 50, &this->font, strname, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
        coord += velocity;
    }

    strarray = {"Init", "Add", "Delete", "Update", "Search"};
    coord = sf::Vector2f(5, 400);
    velocity = sf::Vector2f(0, 50);

    for(std::string strname : strarray) {
        listbutton.push_back(Button(coord.x, coord.y, 100, velocity.y - 2, &this->font, strname, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
        coord += velocity;
    }

    /// setup std::vector<Button> childbutton[10]
    // setup childbutton[iINIT] = {empty, random, user defined list}
    std::vector<std::vector<std::string>> vec2dstr = {
        {"Empty", "Random", "User Defined List", "External File"},
        {"Insert to the first", "Insert to the last", "Insert to the middle"},
        {"Insert to the first", "Insert to the last", "Insert to the middle"},
        {"Update"},
        {"Search"}
    };
    coord = sf::Vector2f(155, 410);
    velocity = sf::Vector2f(200, 50);
    for(int i = 0; i < vec2dstr.size(); i++) {
        sf::Vector2f coord2 = coord;
        for(std::string strname : vec2dstr[i]) {
            childbutton[i].push_back(Button(coord2.x, coord2.y, velocity.x - 2, 30, &this->font, strname, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }

    // debug
    box = new InputBox(800, 500, 100, 100, &font);
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

void State::update()
{
    this->updateMousePositions();
    this->checkforQuit();
    if (this->getQuit()) return;

    for(Button& butt : this->listbutton)
        butt.update(this->mousePosView);
    
    for(int i = 0; i < 5; i++)
        for(Button& butt : childbutton[i])
            butt.update(this->mousePosView);
}

void State::render()
{
    if (this->getQuit()) return;
    for(Button& butt : listbutton)
        butt.render(window);
    for(int i = 0; i < 5; i++)
        for(Button& butt : childbutton[i])
            butt.render(window);
    box->render(window);
}