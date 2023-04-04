#ifndef __state_h__
#define __state_h__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class State {
private:
    sf::RenderWindow* window;
    std::vector<sf::Texture> textures;
    bool quit;

public:
    State(sf::RenderWindow* window);
    virtual ~State();

    const bool& getQuit() const;
    void checkforQuit();

    void endState();
    void update();
    void render();
};

#endif