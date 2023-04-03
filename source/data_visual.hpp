#ifndef __data_visual_hpp__
#define __data_visual_hpp__
#include <SFML/Graphics.hpp>

struct DataVisualization {
private:
    // Varibles
    sf::RenderWindow* window;
    bool running = true;

    // Functions
    void InitWindow();
    void StaticArray();
    void DynamicArray();
    void LinkedList();
    void Stack();
    void Queue();
    /* manipulate:
        initialize
        add
        delete
        update
        search data
    */
public:
    // Constructors/Destructors
    DataVisualization();
    virtual ~DataVisualization();

    // Functions
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};

#endif