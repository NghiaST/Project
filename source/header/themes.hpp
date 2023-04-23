#ifndef __themes_hpp__
#define __themes_hpp__
#include <SFML/Graphics.hpp>
#include "ElementColor.hpp"
#include <vector>

struct Themes;

struct Palette {
private :
    std::vector<ElementColor> listColor;
public :
    Palette() {}
    Palette(ElementColor ecolor0, ElementColor ecolor1, ElementColor ecolor2, ElementColor ecolor3, ElementColor ecolor4);
    Palette(std::vector<ElementColor> listColor);
    ElementColor getColor(int status);
};

struct Themes {
private:
    sf::Color background;
    Palette node;
    Palette arrow;
    Palette button_ds;
    Palette button_manipulate;
    Palette button_submanipulate;
    Palette button_inputbox;
    Palette button_step;
public :
    Themes() {};
    Themes(sf::Color background, Palette node, Palette arrow, Palette button_ds,
           Palette button_manipulate, Palette button_submanipulate, Palette button_inputbox,
           Palette button_step);
    void setTheme(Themes* theme);
    
    void setBackground(sf::Color newBackground);
    void setNode(Palette newNode);
    void setArrow(Palette newArrow);
    void setButtonDs(Palette newButtonDs);
    void setButtonManipulate(Palette newButtonManipulate);
    void setButtonSubmanipulate(Palette newButtonSubmanipulate);
    void setButtonInputbox(Palette newButtonInputbox);
    void setButtonStep(Palette newButtonStep);

    sf::Color* getBackground();
    Palette* getNode();
    Palette* getArrow();
    Palette* getButtonDS();
    Palette* getButtonManipulate();
    Palette* getButtonSubmanipulate();
    Palette* getButtonInputbox();
    Palette* getButtonStep();
};

#endif