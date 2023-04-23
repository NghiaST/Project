#ifndef __data_visualization_hpp__
#define __data_visualization_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "state.hpp"
#include "ds_staticarray.hpp"
#include "ds_dynamicarray.hpp"
#include "ds_linkedlist.hpp"
#include "ds_stack.hpp"
#include "ds_queue.hpp"
#include "mouseKey.hpp"
#include "settings.hpp"

enum DATA_STRUCTURE{DS_STATICARRAY = 0, DS_DYNAMICARRAY, DS_LINKEDLIST, DS_STACK, DS_QUEUE};

struct DataVisualization {
private:
    // Database
    sf::RenderWindow* window;
    Themes *theme;
    double speed;
    VisualizationSettings* settings;
    sf::Font font, fontNode;

    // Constants
    std::vector<Themes*> listTheme;

    // Status
    bool active;
    int typetheme;
    DATA_STRUCTURE ds_present;
    State* states;

    // Input devices
    KEYBOARD keyboardType;
    MOUSE mouseType;
    sf::Vector2f mousePosView;

    // Data Structure
    StructStaticArray* StaticArray;
    StructDynamicArray* DynamicArray;
    StructLinkedList* LinkedList;
    StructStack* Stack;
    StructQueue* Queue;

private:
    // Initializations
    void InitThemes();
    void InitWindow();
    void InitFont();

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