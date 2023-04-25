#ifndef __dashboard_hpp__
#define __dashboard_hpp__

#include <SFML/Graphics.hpp>
#include "themes.hpp"
#include "mouseKey.hpp"

struct VisualizationSettings {
private:
    sf::RenderWindow* window;
    sf::Font *font, *fontNode;
    Themes* theme;
    double* speed;
public:
    VisualizationSettings(sf::RenderWindow* window, sf::Font* font, sf::Font* fontNode, Themes* theme, double* speed);
    ~VisualizationSettings();
    void setWindow(sf::RenderWindow* window);
    void setTheme(Themes* theme);
    void setFont(sf::Font* font);
    void setFontNode(sf::Font* fontNode);
    void setSpeed(double speed);

    sf::RenderWindow* getWindow();
    Themes* getTheme();
    sf::Font* getFont();
    sf::Font* getFontNode();
    double* getSpeed();
};

#endif