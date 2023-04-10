#ifndef __struct_ds_hpp__
#define __struct_ds_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"

struct StructDataStructure {
protected:
    // window
    sf::RenderWindow* window;
    bool active;

    // font
    sf::Font font;

    // point
    sf::Vector2f centerVisual;

    // check which manipulate is activating
    int type1; // none = -1, initialize, insert, del, update, search
    int type2; // none = -1

    // list
    int maxsize;
    int sizearray;
    std::vector<int> elements;

    // data for node
    int sizeNode;
    int distance;
    int diffy;
    std::vector<TripleColor> listColor;

public:
    StructDataStructure(sf::RenderWindow* window, bool active);
    ~StructDataStructure();

    void Initialize_Empty();
    void Initialize_Random();
    void Initialize_Manual(std::vector<int> arr);
    void Initialize_ExternalFile(std::string filename);

    void Insert_First(int value);
    void Insert_Last(int value);
    void Insert_Manual(int pos, int value);

    void Del_First();
    void Del_Last();
    void Del_Manual(int pos);

    void Update(int pos, int value);

    void Search(int value);

    void turn_off();
    void turn_on();
    const bool& isActive() const;

    // void run(int manipulate, int way, std::string str1, std::string str2);


    // render
    // sf::Vector2i update(sf::Vector2f mousePos, int mouseType, int keyboardType);
};

#endif