#ifndef __staticarray_hpp__
#define __staticarray_hpp__
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstring>
#include "graphics_func.hpp"


struct StructStaticArray {
private:
    // constant
    enum PRESENT {NONE = -1, INIT, ADD, DELETE, UPDATE, SEARCH};

    // value
    sf::RenderWindow* window;
    sf::Font font;
    const static int maxsize = 10;
    int sizearray;
    int arr[10];
    ViewSquareNode *staticarr;

    // value check which case is activated
    PRESENT type1;
    int type2;

    bool active;
public:
    void Initialize_Empty();
    void Initialize_Random();
    void Initialize_UserDefinedList();
    void Initialize_ExternalFile();

    void Add_FromTheFirst();
    void Add_FromTheLast();
    void Add_FromTheMiddle();

    void Del_AtTheFirst();
    void Del_AtTheLast();
    void Del_AtTheMiddle();

    void Update();

    void Search();

    void turn_off();
    void turn_on();
    void Initialize(int way);
    void Add(int way);
    void Delete(int way);
    void Update(int way);
    void Search(int way);
    void run(int manipulate, int way); /// Ex: Add - Insert to the last

    const bool& isActive() const;

    StructStaticArray(sf::RenderWindow* window, bool active);
    ~StructStaticArray();

    // render
    void refreshrender();
    void print();
};
#endif