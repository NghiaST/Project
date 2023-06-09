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
#include "mouseKey.hpp"
#include "settings.hpp"
#include "buttonspeed.hpp"
#include "buttonstep.hpp"

struct State {
private:
    // value
    VisualizationSettings* settings;
    sf::RenderWindow* window;
    Themes* theme;
    sf::Font* font;
    bool quit;
    int cntManipulate;
    
    // mouse
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    std::vector<StateCategory> sCategory;
    std::vector<Button> btnTheme;
    std::vector<Button> btnAnimation;
    ButtonSpeed* sBtnSpeed;
    ButtonStep* sBtnStep;

    // state of button
    int typeCategory;
    
public:
    // Init
    State(VisualizationSettings* settings);
    ~State();
    void InitAllButton();

    void checkforQuit();
    // setvalue
    void updateInputBox(int pos, int value);
    // getvalue
    const bool& getQuit() const;
    std::vector<std::string> getInputBox(int typeManipulate);

    // Mouse
    void updateMousePositions();

    // Accessors
    sf::Vector2i update(MOUSE mouseType, KEYBOARD keyboardType);
    void updateBtnCode(int Manipulate, int subManipulate);
    void updateBtnStep(int step);
    void render();
};

#endif