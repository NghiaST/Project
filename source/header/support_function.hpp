#ifndef __support_function_hpp__
#define __support_function_hpp__
#include <SFML/Graphics.hpp>
#include <cstring>

sf::Vector2f operator * (const sf::Vector2f& vector, const double& multiply);
sf::Vector2f operator / (const sf::Vector2f& vector, const double& div);

sf::Color appearColor(const sf::Color& color, const double& multiply);
sf::Color convertColor(sf::Color colorStart, sf::Color colorStop, const double ratio);
int Rand(int l, int r);

int string_to_int(std::string str); 
std::vector<int> string_to_array(std::string str);

std::string Rand_Array();

#endif