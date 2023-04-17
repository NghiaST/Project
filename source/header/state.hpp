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

enum MOUSE{MSE_NONE = 0, MSE_LEFTCLICK, MSE_RIGHTCLICK, MSE_LEFTHOLD, MSE_RIGHTHOLD};

struct State {
private:    
    // value
    sf::RenderWindow* window;
    sf::Font font;
    Themes* theme;
    // std::vector<sf::Texture> textures;
    bool quit;
    int cntManipulate;
    
    // mouse
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // state of button
    int typeCategory;
    int typeManipulate;
    int typesubManipulate;

    std::vector<Button> buttonCategory;
    std::vector<Button> buttonManipulate;
    std::vector<std::vector<Button>> subbuttonManipulate;
    std::vector<std::vector<InputBox>> boxarr;
    
public:
    // Init
    State(sf::RenderWindow* window, Themes* theme);
    ~State();

    void setNewDS(int ds_new);
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

    // Box
    // void Input_Add_InsertTheMiddle();
    // void Input_Delete_DeleteAtTheMiddle();
    // void Input_Update_Update();
    // void Input_Search_Search();
    // void Build_Input();
};

#endif