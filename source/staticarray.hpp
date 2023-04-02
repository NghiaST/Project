#ifndef __staticarray_hpp__
#define __staticarray_hpp__
#include <SFML/Graphics.hpp>

class StructStaticArray {
private:
    sf::RenderWindow window;
    void Initialize();
    void Add();
    void Delete();
    void Update();
    void SearchData();
public:
    StructStaticArray(sf::RenderWindow& _window);
    void run();
};
#endif