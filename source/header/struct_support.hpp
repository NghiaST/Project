#ifndef __struct_support_hpp__
#define __struct_support_hpp__
#include <SFML/Graphics.hpp>
#include <cstring>

sf::Vector2f operator / (const sf::Vector2f& vector, const int& div);
void settext(sf::Text& text, sf::Vector2f coord);
void settextrectangle(sf::Text& text, sf::Vector2f coord, sf::Vector2f rectsize);
void addwhitescreen(sf::RenderWindow& window);
char* strtochar(std::string str);
int Rand(int l, int r);

#endif