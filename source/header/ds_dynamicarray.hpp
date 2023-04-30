#ifndef __ds_dynamicarray_hpp__
#define __ds_dynamicarray_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"
#include "mouseKey.hpp"

struct StructDynamicArray : StructDataStructure {
public:
    StructDynamicArray(VisualizationSettings* settings, bool active);
    ~StructDynamicArray();

    void run(int manipulate, int way, std::string str1, std::string str2);

    // render
    void updatePositionNode();
    sf::Vector2i updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);
    void refreshrender();
    void render();
};

#endif