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
#include "manipulate_animation.hpp"

struct StructLinkedList : StructDataStructure {
protected:
    // value
    std::vector<CircleNode> listNode;
    std::vector<ArrowNode> listArrow;
    std::vector<sf::Vector2f> listPoint;

    // Manipulate_Animation_ArrayNode* nodeAnimation[20];
    // Manipulate_Animation_ArrayArrow* arrowAnimation[20];

    std::vector<Manipulate_Animation_ArrayNode> nodeAnimation;
    std::vector<Manipulate_Animation_ArrayArrow> arrowAnimation;

    double speed = 1;

    std::vector<int> preElements;

    bool running = false;
    int Manipulate = -1;
    int Way = -1;
    int Pos = -1;
    std::string Str1;
    std::string Str2;
    int Val;
    int preSize; /// size of array, number of elements (previous)

    double totaltime;
    sf::Clock clock;

    int count_nodePrint;
public:
    StructLinkedList(sf::RenderWindow* window, bool active);
    ~StructLinkedList();

    void turn_on();
    void run(int manipulate, int way, std::string str1, std::string str2);

    void Animation_Insert_Last();
    void updateAnimation();

    // support function
    std::vector<sf::Vector2f> getPosition(int size);

    // render
    void updatePositionNode();
    sf::Vector2i update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render();
};
#endif