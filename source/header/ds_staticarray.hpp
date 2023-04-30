#ifndef __ds_staticarray_hpp__
#define __ds_staticarray_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

struct StructStaticArray : StructDataStructure {
public:
    StructStaticArray(VisualizationSettings* settings, bool active);
    ~StructStaticArray();

    void run(int manipulate, int way, std::string str1, std::string str2);

    // render
    void updatePositionNode();
    sf::Vector2i updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);
    void refreshrender();
    void render();
};

#endif