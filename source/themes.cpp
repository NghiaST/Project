#include "themes.hpp"
#include <iostream>

Palette::Palette(ElementColor ecolor0, ElementColor ecolor1, ElementColor ecolor2, ElementColor ecolor3, ElementColor ecolor4)
{
    listColor = {ecolor0, ecolor1, ecolor2, ecolor3, ecolor4};
}

Palette::Palette(std::vector<ElementColor> listColor)
{
    if (listColor.size() < 5)
    {
        std::cout << "error themes.cpp : lack of ecolor in vector<ElementColor> \n";
        exit(1);
    }
    this->listColor = listColor;
}

ElementColor Palette::getColor(int status)
{
    return this->listColor[status];
}

PublicThemes::PublicThemes(sf::Color background, Palette node, Palette arrow, Palette button_ds, Palette button_manipulate, Palette button_submanipulate, Palette button_inputbox, Palette button_step) 
    : background(background), node(node), arrow(arrow),
      button_ds(button_ds), button_manipulate(button_manipulate),
      button_submanipulate(button_submanipulate),
      button_inputbox(button_inputbox),
      button_step(button_step) {}

Themes::Themes(sf::Color background, Palette node, Palette arrow, Palette button_ds, Palette button_manipulate, Palette button_submanipulate, Palette button_inputbox, Palette button_step)
    : PublicThemes(background, node, arrow, button_ds, button_manipulate, button_submanipulate, button_inputbox, button_step) {}

void Themes::setBackground(sf::Color newBackground) {
    background = newBackground;
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

void PublicThemes::getThemes(Themes* theme)
{
    this->background = theme->getBackground();
    this->node = theme->getNode();
    this->arrow = theme->getArrow();
    this->button_ds = theme->getButtonDS();
    this->button_manipulate = theme->getButtonManipulate();
    this->button_submanipulate = theme->getButtonSubmanipulate();
    this->button_inputbox = theme->getButtonInputbox();
    this->button_step = theme->getButtonStep();
}
