#include "themes.hpp"
#include <iostream>

Palette::Palette(ElementColor color0, ElementColor color1, ElementColor color2, ElementColor color3, ElementColor color4)
{
    listColor = {color0, color1, color2, color3, color4};
}

Palette::Palette(std::vector<ElementColor> listColor)
{
    if (listColor.size() < 5)
    {
        std::cout << "error themes.cpp : lack of color in vector<ElementColor> \n";
        exit(1);
    }
    this->listColor = listColor;
}

Themes::Themes(sf::Color background, Palette node, Palette arrow, Palette button_ds,
               Palette button_manipulate, Palette button_submanipulate, Palette button_inputbox,
               Palette button_step)
          : background(background),
            node(node),
            arrow(arrow),
            button_ds(button_ds),
            button_manipulate(button_manipulate),
            button_submanipulate(button_submanipulate),
            button_inputbox(button_inputbox),
            button_step(button_step) {}

void Themes::setBackground(sf::Color newBackground) {
    background = newBackground;
    std::cout << "W " << (int)background.r << ' ' << (int)background.g << ' ' << (int) background.b << '\n';
}

void Themes::setNode(Palette newNode)
{
    node = newNode;
}

void Themes::setArrow(Palette newArrow) {
    arrow = newArrow;
}

void Themes::setButtonDs(Palette newButtonDs) {
    button_ds = newButtonDs;
}

void Themes::setButtonManipulate(Palette newButtonManipulate) {
    button_manipulate = newButtonManipulate;
}

void Themes::setButtonSubmanipulate(Palette newButtonSubmanipulate) {
    button_submanipulate = newButtonSubmanipulate;
}

void Themes::setButtonInputbox(Palette newButtonInputbox) {
    button_inputbox = newButtonInputbox;
}

void Themes::setButtonStep(Palette newButtonStep) {
    button_step = newButtonStep;
}

sf::Color Themes::getBackground() {
    return background;
}

Palette Themes::getNode() {
    return node;
}

Palette Themes::getArrow() {
    return arrow;
}

Palette Themes::getButtonDS() {
    return button_ds;
}

Palette Themes::getButtonManipulate() {
    return button_manipulate;
}

Palette Themes::getButtonSubmanipulate() {
    return button_submanipulate;
}

Palette Themes::getButtonInputbox() {
    return button_inputbox;
}

Palette Themes::getButtonStep() {
    return button_step;
}
