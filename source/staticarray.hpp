#ifndef __staticarray_hpp__
#define __staticarray_hpp__
#include <SFML/Graphics.hpp>
#include "graphics_func.hpp"

class StructStaticArray {
private:
    sf::RenderWindow* window;
    const static int maxsize = 10;
    int sizearray;
    int arr[10];
    ViewSquareNode *staticarr;
    void Initialize();
    void Add();
    void Delete();
    void Update();
    void SearchData();
public:
    StructStaticArray(sf::RenderWindow* window);
    void run();
};
#endif