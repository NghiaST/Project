#ifndef __staticarray_hpp__
#define __staticarray_hpp__
#include <SFML/Graphics.hpp>
#include "graphics_func.hpp"

enum PRESENT {INIT = 0, ADD = 1, DELETE, UPDATE, SEARCH};

class StructStaticArray {
private:
    sf::RenderWindow* window;
    const static int maxsize = 10;
    int sizearray;
    int arr[10];
    ViewSquareNode *staticarr;
    PRESENT type;
    bool active;
public:
    void Initialize();
    void Add();
    void Delete();
    void Update();
    void SearchData();

    StructStaticArray(sf::RenderWindow* window);
    void print();
};
#endif