#include <SFML/Graphics.hpp>
#include "settings.hpp"


VisualizationSettings::VisualizationSettings(sf::RenderWindow* window, sf::Font* font, sf::Font* fontNode, Themes* theme, double* speed) {
    this->window = window;
    this->font = font;
    this->fontNode = fontNode;
    this->theme = theme;
    this->speed = speed;
}

VisualizationSettings::~VisualizationSettings() {}

void VisualizationSettings::setWindow(sf::RenderWindow* window) {
    this->window = window;
}

void VisualizationSettings::setTheme(Themes* theme) {
    *this->theme = *theme;
}

void VisualizationSettings::setFont(sf::Font* font) {
    *this->font = *font;
}

void VisualizationSettings::setFontNode(sf::Font* fontNode) {
    *this->fontNode = *fontNode;
}

void VisualizationSettings::setSpeed(double* speed)
{
    this->speed = speed;
}

sf::RenderWindow* VisualizationSettings::getWindow() {
    return window;
}

Themes* VisualizationSettings::getTheme() {
    return theme;
}

sf::Font* VisualizationSettings::getFont() {
    return font;
}

sf::Font* VisualizationSettings::getFontNode() {
    return fontNode;
}

double* VisualizationSettings::getSpeed() {
    return speed;
}