#ifndef __data_visualization_hpp__
#define __data_visualization_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "state.hpp"
#include "ds_staticarray.hpp"
#include "ds_dynamicarray.hpp"
#include "ds_simplylinkedlist.hpp"
#include "ds_doublylinkedlist.hpp"
#include "ds_circularlinkedlist.hpp"
#include "ds_stack.hpp"
#include "ds_queue.hpp"
#include "mouseKey.hpp"
#include "settings.hpp"

enum DATA_STRUCTURE{DS_STATICARRAY = 0, DS_DYNAMICARRAY, DS_SIMPLYLINKEDLIST, DS_DOUBLYLINKEDLIST, DS_CIRCULARLINKEDLIST, DS_STACK, DS_QUEUE};

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
    std::vector<double> listSpeed;

    // Status
    bool active;
    int typetheme;
    int typespeed;
    DATA_STRUCTURE ds_present;
    State* states;

    // Input devices
    KEYBOARD keyboardType;
    MOUSE mouseType;
    sf::Vector2f mousePosView;

    // Data Structure
    std::unique_ptr<StructDataStructure> DataStructure;

private:
    // Initializations
    void InitThemes();
    void InitWindow();
    void InitFont();
    void InitSpeed();

    // Functions
    void processEvents();
    void update();
    void render();

public:
    // Constructors/Destructors
    DataVisualization();
    virtual ~DataVisualization();
    void run();
};

#endif