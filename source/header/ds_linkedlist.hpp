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

    std::vector<Manipulate_Animation_ArrayNode> nodeAnimation;
    std::vector<Manipulate_Animation_ArrayArrow> arrowAnimation;

    double speed = 1;

    std::vector<int> printElements;

    bool running = false;
    // int Manipulate = -1;
    // int Way = -1;
    // int Pos = -1;
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
    std::vector<sf::Vector2f> getPosition(int size);
    void updateAnimation();
    void run(int manipulate, int way, std::string str1, std::string str2);

    // render
    sf::Vector2i updateKBM(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void updatePositionNode();
    void refreshrender();
    void render();

    void Animation_Initialize(int way);
    void Animation_Insert_First();
    void Animation_Insert_Last();
    void Animation_Insert_Manual();
    void Animation_Del_First();
    void Animation_Del_Last();
    void Animation_Del_Manual();
    // void Animation_Update();
    // void Animation_Search();
    void stopAnimation();
};
#endif