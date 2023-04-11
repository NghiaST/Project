#ifndef __ds_queue_hpp__
#define __ds_queue_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"
#include "arrow.hpp"

struct StructQueue : StructDataStructure {
protected:
    // value
    std::vector<CircleNode> listNode;
    std::vector<ArrowNode> listArrow;

public:
    StructQueue(sf::RenderWindow* window, bool active);
    ~StructQueue();

    void turn_on();
    void run(int manipulate, int way, std::string str1, std::string str2);

    void Peek_Front();
    void Peek_Back();
    void Enqueue(int value);
    void Dequeue();
    // render
    void updatePositionNode();
    sf::Vector2i updateKBM(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render();
};

#endif