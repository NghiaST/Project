#ifndef __structure_hpp__
#define __structure_hpp__
#include <SFML/Graphics.hpp>

struct DataVisualization {
private:
    sf::RenderWindow window;
    bool running = true;
    void Open();
    void CommonView();
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
    void run();
};

#endif