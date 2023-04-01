#ifndef __structure_hpp__
#define __structure_hpp__

class DataVisualization {
private:
    bool running = true;
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