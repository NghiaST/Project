#ifndef __ds_linkedlist_hpp__
#define __ds_linkedlist_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"
#include "arrow.hpp"

struct StructLinkedList : StructDataStructure {
protected:
    // value
    std::vector<CircleNode> listNode;
    std::vector<ArrowNode> listArrow;

public:
    StructLinkedList(sf::RenderWindow* window, bool active);
    ~StructLinkedList();

    void run(int manipulate, int way, std::string str1, std::string str2);

    // render
    void updatePositionNode();
    sf::Vector2i update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render();
};
#endif