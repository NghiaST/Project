#include "struct_support.hpp"
#include <iostream>
#include <random>
#include <cstring>

sf::Vector2f operator / (const sf::Vector2f& vector, const int& div)
{
    return sf::Vector2f(vector.x / div, vector.y / div);
}

int Rand(int l, int r)
{
    if (l > r) return l;
    return rand() % (r - l + 1) + l;
}

int string_to_int(std::string str)
{
    std::cout << str << '\n';
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
    bool isNext = 1;
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
