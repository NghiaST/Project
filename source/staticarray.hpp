#ifndef __staticarray_hpp__
#define __staticarray_hpp__
#include <SFML/Graphics.hpp>
#include "graphics_func.hpp"

enum PRESENT {INIT = 0, ADD = 1, DELETE, UPDATE, SEARCH};

struct StructStaticArray {
private:
    sf::RenderWindow* window;
    sf::Font font;
    const static int maxsize = 10;
    int sizearray;
    int arr[10];
    ViewSquareNode *staticarr;
    PRESENT type;
    bool active;
public:
    void turn_off();
    void turn_on();
    void Initialize();
    void Add();
    void Delete();
    void Update();
    void Search();
    void run(/*int manipulate, int way*/); /// Ex: Add - Insert to the last

    const bool& isActive() const;

    StructStaticArray(sf::RenderWindow* window, bool active);
    ~StructStaticArray();

    // render
    void refreshrender();
    void print();
};
#endif