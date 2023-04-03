#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
sf::Vector2f operator / (const sf::Vector2f& vector, const int& div) {
    return sf::Vector2f(vector.x / div, vector.y / div);
}
void settext(sf::Text& text, sf::Vector2f coord) {
    text.setPosition(coord - sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) / 2 + sf::Vector2f(-1, -3));
    // std::cout << "Debug settext\n";
}

void settextrectangle(sf::Text& text, sf::Vector2f coord, sf::Vector2f rectsize) {
    settext(text, coord + rectsize / 2);
    // std::cout << "Debug settextrect\n";
}

char* inttochar(int number) {
    std::string strData = std::to_string(number);

    char* temp = new char[strData.length() + 1];
    std::strcpy(temp, strData.c_str());
    temp[strData.length()] = '\0';
    std::cout << temp << '\n';
    return temp;
}

void addwhitescreen(sf::RenderWindow& window) {
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(2000, 2000));
    shape.setPosition(0, 0);
    shape.setFillColor(sf::Color(235, 235, 235));
    window.draw(shape);
}

char* strtochar(std::string str) {
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

int Rand(int l, int r) {
    if (l > r) return l;
    return rand() % (r - l + 1) + l;
}