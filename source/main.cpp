#include "data_visual.hpp"

int main()
{
    DataVisualization* NewVisual = new DataVisualization();
    NewVisual->run();
    delete NewVisual;
}
/* 
categories:
    void StaticArray();
    void DynamicArray();
    void LinkedList(); // simply, doubly, circular
    void Stack();
    void Queue();

manipulations:
    initialize
    add
    delete
    update
    search data
*/
