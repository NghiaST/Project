#include "state.hpp"

State::State(sf::RenderWindow *window)
{
    this->window = window;
    if (!this->font.loadFromFile("dat/roboto/Roboto-Black.ttf")) {
        std::cout << "Error Load Font\n";
    }

    sf::Vector2f coord = sf::Vector2f(5, 5);
    sf::Vector2f velocity = sf::Vector2f(150, 0);
    std::vector<std::string> strarray = {"StaticArray", "DynamicArray", "LinkedList", "Stack", "Queue"};
    std::vector<std::string> strarray2 = {"Init", "Add", "Delete", "Update", "Search"};

    for(std::string strname : strarray) {
        listbutton.push_back(Button(coord.x, coord.y, velocity.x, 50, &this->font, strname, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
        coord += velocity;
    }
    coord = sf::Vector2f(5, 200);
    velocity = sf::Vector2f(0, 50);

    for(std::string strname : strarray2) {
        listbutton.push_back(Button(coord.x, coord.y, 100, velocity.y, &this->font, strname, sf::Color(220, 220, 220), sf::Color::Green, sf::Color::Yellow));
        coord += velocity;
    }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) 
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
}

void State::render()
{
    if (this->getQuit()) return;
    for(Button& butt : listbutton)
        butt.render(window);
}