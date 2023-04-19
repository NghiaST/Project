#ifndef __state_hpp__
#define __state_hpp__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include "button.hpp"
#include "inputbox.hpp"
#include "ElementColor.hpp"
#include "themes.hpp"
#include "StateCategory.hpp"
#include "enum.hpp"

struct State {
private:    
    // value
    sf::RenderWindow* window;
    PublicThemes* theme;
    sf::Font font;
    // std::vector<sf::Texture> textures;
    bool quit;
    int cntManipulate;
    
    // mouse
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    std::vector<StateCategory> sCategory;
    std::vector<Button> btnTheme;

    // state of button
    int typeCategory;
    
public:
    // Init
    State(sf::RenderWindow* window, PublicThemes* theme);
    ~State();

    void checkforQuit();
    // setvalue
    void updateInputBox(int pos, int value);
    // getvalue
    const bool& getQuit() const;
    std::string getValueButton(int typeManipulate, int id);

    // Mouse
    void updateMousePositions();

    // Accessors
    sf::Vector2i update(int mouseType, int keyboardType);
    void render();
};

#endif