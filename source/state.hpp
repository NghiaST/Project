#ifndef __state_h__
#define __state_h__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "button.hpp"
#include "inputbox.hpp"
#include <iterator>

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
    int mouseType;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // keyboard
    int keyboardType;

    // state of button
    int typeCategory;
    int typeManipulate;
    int typesubManipulate;
    bool activeManipulate[5];

    std::vector<Button> buttonCategory;
    std::vector<Button> buttonManipulate;
    std::vector<Button> subbuttonManipulate[5];

    std::vector<std::vector<InputBox>> boxarr; // (5, std::vector<int>);
    // InputBox* boxInit;
    // InputBox* boxAdd;
    // InputBox* boxDel;
    // InputBox* boxUpd;
    // InputBox* boxSearch;
public:
    
public:
    // Init
    State(sf::RenderWindow* window);
    virtual ~State();

    const bool& getQuit() const;
    void checkforQuit();

    // Mouse
    void updateMousePositions();

    void endState();
    sf::Vector2i update(int keyboardType);
    void render();

    // Box
    // void Input_Add_InsertTheMiddle();
    // void Input_Delete_DeleteAtTheMiddle();
    // void Input_Update_Update();
    // void Input_Search_Search();
    // void Build_Input();
};

#endif