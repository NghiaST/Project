#ifndef __state_h__
#define __state_h__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include "button.hpp"
#include "inputbox.hpp"

enum MOUSE{MSE_NONE = 0, MSE_LEFTCLICK, MSE_RIGHTCLICK, MSE_LEFTHOLD, MSE_RIGHTHOLD};

struct State {
private:
    // constant 
    // enum PRESENT {NONE = -1, INIT, ADD, DELETE, UPDATE, SEARCH};
    const int NONE = -1, INIT = 0, ADD = 1, DELETE = 2, UPDATE = 3, SEARCH = 4;
    
    // value
    sf::RenderWindow* window;
    sf::Font font;
    // std::vector<sf::Texture> textures;
    bool quit;
    
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
    std::vector<Button> subbuttonManipulate[5];

    std::vector<std::vector<InputBox>> boxarr; // (5, std::vector<int>);
    
public:
    // Init
    State(sf::RenderWindow* window);
    virtual ~State();

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