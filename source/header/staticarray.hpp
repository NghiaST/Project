#ifndef __staticarray_hpp__
#define __staticarray_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "struct_support.hpp"

struct StructStaticArray {
private:
    // constant
    enum PRESENT {NONE = -1, INIT, ADD, DELETE, UPDATE, SEARCH};

    // value
    sf::RenderWindow* window;
    sf::Vector2f centerVisual;
    sf::Font font;
    const static int maxsize = 10;
    int sizearray;
    std::vector<int> arr;
    std::vector<RectangleNode> staticarr;

    // value check which case is activated
    PRESENT type1;
    int type2;

    bool active;
public:
    StructStaticArray(sf::RenderWindow* window, bool active);
    ~StructStaticArray();

    void Initialize_Empty();
    void Initialize_Random();
    void Initialize_Manual(std::vector<int> arr);
    void Initialize_ExternalFile(std::string filename);

    void Add_First(int value);
    void Add_Last(int value);
    void Add_Manual(int pos, int value);

    void Del_First();
    void Del_Last();
    void Del_Manual(int pos);

    void Update(int pos, int value);

    void Search(int value);

    void turn_off();
    void turn_on();
    void run(int manipulate, int way, std::string str1, std::string str2);

    const bool& isActive() const;

    // render
    sf::Vector2i update(sf::Vector2f mousePos, int mouseType, int keyboardType);
    void refreshrender();
    void render();
};

struct StructDynamicArray : StructStaticArray {
    StructDynamicArray(sf::RenderWindow* window, bool active) : StructStaticArray(window, active) {};
};

#endif