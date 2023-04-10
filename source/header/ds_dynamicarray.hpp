#ifndef __ds_dynamicarray_hpp__
#define __ds_dynamicarray_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

struct StructDynamicArray : StructDataStructure {
protected:
    // value
    std::vector<RectangleNode> listNode;

public:
    StructDynamicArray(sf::RenderWindow* window, bool active);
    ~StructDynamicArray();

    void turn_on();
    void run(int manipulate, int way, std::string str1, std::string str2);

    // render
    void updatePositionNode();
    sf::Vector2i update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render();
};

#endif