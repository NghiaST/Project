#ifndef __data_visualization_hpp__
#define __data_visualization_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include "state.hpp"
#include "ds_staticarray.hpp"
#include "ds_dynamicarray.hpp"
#include "ds_linkedlist.hpp"
#include "ds_stack.hpp"
#include "ds_queue.hpp"
#include "themes.hpp"

enum DATA_STRUCTURE{DS_STATICARRAY = 0, DS_DYNAMICARRAY, DS_LINKEDLIST, DS_STACK, DS_QUEUE};

struct DataVisualization {
private:
    // Varibles
    sf::RenderWindow* window;
    Themes *LightMode, *DarkMode, presentMode;
    bool active;
    int keyboardType;
    int mouseType;
    sf::Vector2f mousePosView;

    State* states;
    DATA_STRUCTURE ds_present;
    StructStaticArray* StaticArray;
    StructDynamicArray* DynamicArray;
    StructLinkedList* LinkedList;
    StructStack* Stack;
    StructQueue* Queue;

    // Initializations
    void InitThemes();
    void InitWindow();
    void InitStates();

    // Functions
    void processEvents();
    void update();
    void render();

public:
    // Constructors/Destructors
    DataVisualization();
    virtual ~DataVisualization();
    //#define get_DS(x) (x != DS_QUEUE ? x != DS_STACK ? x != DS_LINKEDLIST ? x != DS_DYNAMICARRAY ? StaticArray : DynamicArray : LinkedList : Stack : Queue)

    void run();
};

#endif