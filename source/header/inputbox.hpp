#ifndef __inputbox_hpp__
#define __inputbox_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "style.hpp"
#include "button.hpp"

struct InputBox : Button {
private:
    bool active;

    // string
    std::string wordInput;

public:
    InputBox(sf::Vector2f coord, float width, float height, float sizeText, float thickness, bool view, bool keepActive, std::string textConst, sf::Font *font, Palette* palette);
    ~InputBox();
    
    void setWordInput(std::string wordInput);
    std::string getWordInput();

    void Add_Character(int keyboardType);
    void Del_Character();
    void update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    
    void refreshrender() override;
    void render(sf::RenderWindow* window) override;
};

#endif