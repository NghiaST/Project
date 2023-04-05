#ifndef __data_visual_hpp__
#define __data_visual_hpp__
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include "state.hpp"
#include "staticarray.hpp"

enum PAGE{STATIC_ARRAY = 0, DYNAMIC_ARRAY, LINKED_LIST, STACK, QUEUE};

const int iSTATIC = 0;
const int iDYNAMIC = 1;
const int iLINKEDLIST = 2;
const int iSTACK = 3;
const int iQUEUE = 4;
const int iINIT = 5;
const int iADD = 6;
const int iDELETE = 7;
const int iUPDATE = 8;
const int iSEARCH = 9;

struct DataVisualization {
private:
    // Varibles
    sf::RenderWindow* window;
    sf::Event sfEvent;
    bool running;
    int keyboardType;

    State* states;
    PAGE page_present;
    StructStaticArray* StaticArray;
    StructStaticArray* DynamicArray;
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