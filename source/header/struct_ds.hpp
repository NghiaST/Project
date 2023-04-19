#ifndef __struct_ds_hpp__
#define __struct_ds_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "themes.hpp"

struct StructDataStructure {
protected:
    // window
    sf::RenderWindow* window;
    PublicThemes* theme;
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
    float sizeNode;   /// rectangle: length, area: diameter 
    float diffx;
    float diffy;
    float distance;
    unsigned int sizeText;
    float thickness;

    // animation
    bool running = false;
    bool pause = false;
    bool step_step = false;
    double totaltime;
    sf::Clock clock;
    double speed = 1;

    std::vector<sf::Vector2f> listPoint;
    std::vector<int> printElements;
    int count_nodePrint;

    std::string Str1;
    std::string Str2;
    int Val;
    int preSize;/// size of array, number of elements (previous)

    // type animation
    int Manipulate = -1;
    int Way = -1;
    int Pos = -1;

public:
    StructDataStructure(sf::RenderWindow* window, PublicThemes* theme, bool active);
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

    int Search(int value);

    // virtual void updatePositionNode() = 0;
    void turn_on();
    void turn_off();
    const bool& isActive() const;

    virtual void run(int manipulate, int way, std::string str1, std::string str2) = 0;
    virtual void refreshrender() = 0;
    virtual void render() = 0;

    // render
    // sf::Vector2i update(sf::Vector2f mousePos, int mouseType, int keyboardType);
};

#endif