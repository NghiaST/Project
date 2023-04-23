#ifndef __ds_stack_hpp__
#define __ds_stack_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"
#include "arrow.hpp"

struct StructStack : StructDataStructure {
protected:
    // value
    std::vector<CircleNode> listNode;
    std::vector<ArrowNode> listArrow;

public:
    StructStack(VisualizationSettings* settings, bool active);
    ~StructStack();
    void run(int manipulate, int way, std::string str1, std::string str2);

    void Peek();
    void Push(int value);
    void Pop();
    // render
    void updatePositionNode();
    sf::Vector2i updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);
    void refreshrender();
    void render();
};

#endif