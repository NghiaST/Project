#include "support_function.hpp"
#include <iostream>
#include <random>
#include <cstring>

sf::Vector2f operator*(const sf::Vector2f &vector, const double &multiply)
{
    return sf::Vector2f(vector.x * multiply, vector.y * multiply);
}

sf::Vector2f operator/(const sf::Vector2f &vector, const double &div)
{
    return sf::Vector2f(vector.x / div, vector.y / div);
}

sf::Color appearColor(const sf::Color &color, const double &multiply)
{
    return sf::Color(color.r, color.g, color.b, sf::Uint8(color.a * multiply));
}

sf::Color convertColor(sf::Color colorStart, sf::Color colorStop, const double ratio)
{
    return sf::Color(
        colorStart.r + ((int)colorStop.r - colorStart.r) * ratio,
        colorStart.g + ((int)colorStop.g - colorStart.g) * ratio,
        colorStart.b + ((int)colorStop.b - colorStart.b) * ratio,
        colorStart.a + ((int)colorStop.a - colorStart.a) * ratio
    );
}

int Rand(int l, int r)
{
    if (l > r) return l;
    return rand() % (r - l + 1) + l;
}

int string_to_int(std::string str)
{
    int number = 0;
    for(char c : str)
    {
        if (isdigit(c))
            number = number * 10 + c - '0';
        if (number >= 100)
            break;
    }
    return number;
}

std::vector<int> string_to_array(std::string str)
{
    std::vector<int> arr;
    int number = 0;
    bool isNext = 0;
    for(char c : str)
    {
        if (isdigit(c))
        {
            isNext = 1;
            number = number * 10 + c - '0';
            if (number >= 100)
            {
                arr.push_back(number);
                number = 0;
                isNext = 0;
            }
        }
        else {
            if (isNext == true)
            {
                arr.push_back(number);
                number = 0;
                isNext = 0;
            }
        }
    }
    if (isNext == 1)
        arr.push_back(number);
    return arr;
}
