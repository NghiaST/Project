#ifndef __ds_linkedlist_hpp__
#define __ds_linkedlist_hpp__
#include "struct_ds.hpp"

struct StructLinkedList : StructDataStructure {
public:
    StructLinkedList(VisualizationSettings* settings, bool active);
    ~StructLinkedList();

    std::vector<sf::Vector2f> getPosition(int size);
    void run(int manipulate, int way, std::string str1, std::string str2);

    // render
    sf::Vector2i updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);
    void refreshNode();
    void refreshrender();
    void render();

    void Animation_Initialize(int way);
    void Animation_Insert_First();
    void Animation_Insert_Last();
    void Animation_Insert_Manual();
    void Animation_Del_First();
    void Animation_Del_Last();
    void Animation_Del_Manual();
    void Animation_Update();
    void Animation_Search();

    void stopAnimation();


};
#endif