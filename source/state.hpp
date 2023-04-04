#ifndef __state_h__
#define __state_h__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "button.hpp"
#include "inputbox.hpp"

struct State {
private:
    sf::RenderWindow* window;
    sf::Font font;
    std::vector<sf::Texture> textures;
    bool quit;
    
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

public:
    std::vector<Button> listbutton;
    std::vector<Button> childbutton[5];
    InputBox* box;
    
public:
    // Init
    State(sf::RenderWindow* window);
    virtual ~State();

    const bool& getQuit() const;
    void checkforQuit();

    // Mouse
    void updateMousePositions();

    void endState();
    void update();
    void render();
};

#endif