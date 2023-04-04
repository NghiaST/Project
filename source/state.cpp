#include "state.hpp"

State::State(sf::RenderWindow *window)
{
    this->window = window;
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

void endState()
{
    std::cout << "End State\n";
}

void State::update()
{
    this->checkforQuit();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        std::cout << "A\n";
    }
}

void State::render()
{
    /*for(sf::Texture text : textures)
        this->window->draw(text);*/
    std::cout << "HELLO\n";
}