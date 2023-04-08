#ifndef __data_visual_hpp__
#define __data_visual_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "state.hpp"
#include "staticarray.hpp"

enum PAGE{PAGE_STATICARRAY = 0, PAGE_DYNAMICARRAY, PAGE_LINKEDLIST, PAGE_STACK, PAGE_QUEUE};

struct DataVisualization {
private:
    // Varibles
    sf::RenderWindow* window;
    bool active;
    int keyboardType;
    int mouseType;
    sf::Vector2f mousePosView;

    State* states;
    PAGE page_present;
    StructStaticArray* StaticArray;
    StructDynamicArray* DynamicArray;
    StructStaticArray* LinkedList;
    StructStaticArray* Stack;
    StructStaticArray* Queue;

    // Initializations
    void InitWindow();
    void InitStates();

public:
    // Constructors/Destructors
    DataVisualization();
    virtual ~DataVisualization();

    // Functions
    void processEvents();
    void update();
    void render();
    void run();
};

#endif