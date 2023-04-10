#ifndef __support_function_hpp__
#define __support_function_hpp__
#include <SFML/Graphics.hpp>
#include <cstring>

sf::Vector2f operator * (const sf::Vector2f& vector, const int& div);
sf::Vector2f operator / (const sf::Vector2f& vector, const int& div);
int Rand(int l, int r);

int string_to_int(std::string str);
std::vector<int> string_to_array(std::string str);

#endif