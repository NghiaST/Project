#ifndef __struct_ds_hpp__
#define __struct_ds_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>

#include "node.hpp"
#include "arrow.hpp"
#include "support_function.hpp"
#include "manipulate_animation.hpp"
#include "settings.hpp"
#include "mouseKey.hpp"

enum ANIMATION_TYPE {ANIMATION_PAUSE = 0, ANIMATION_PLAY, ANIMATION_STEP_DOWN, ANIMATION_STEP_UP};

struct StructDataStructure {
protected:
    // window
    sf::RenderWindow* window;
    Themes* theme;
    sf::Font* font;
    double* speed;
    bool active;

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
    float sizeNode;   /// rectangle: length, circle: diameter 
    float diffx;
    float diffy;
    float distance;
    unsigned int sizeText;
    float thickness;

    // animation
    bool running = false;
    bool pause = false;
    bool step_step = false;
    ANIMATION_TYPE type_running = ANIMATION_PAUSE;   // 0, 1, 2, 3, 4 : none, common, pause, step by step <-, step by step ->
    double steptime = 1.3;
    double totaltime;
    double time;

    int step_total;
    int step_present;
    int step_next;
    sf::Clock clock;

    std::vector<sf::Vector2f> listPoint;
    std::vector<int> printElements;
    int count_nodePrint;
    int count_arrowPrint;

    std::vector<std::string> vecStr;
    int Val;
    int preSize;/// size of array, number of elements (previous)

    // type animation
    int Manipulate = -1;
    int subManipulate = -1;
    std::vector<int> listStep;

    // shape
    std::vector<std::unique_ptr<Node>> listNode;
    std::vector<ArrowNode> listArrow;
    std::vector<Manipulate_Animation_ArrayNode> nodeAnimation;
    std::vector<Manipulate_Animation_ArrayArrow> arrowAnimation;

public:
    StructDataStructure(VisualizationSettings* settings, bool active);
    ~StructDataStructure();

    // setup
    void turn_on();
    void turn_off();
    void startAnimationDS();
    void stopAnimationDS();

    // get
    int getManipulate();
    int getsubManipulate();
    const bool& isActive() const;
    std::vector<sf::Vector2f> getPosition(int size);

    // manipulate
    void Initialize_Empty();
    void Initialize_Random();
    void Initialize_Manual(std::vector<int> arr);
    int Initialize_ExternalFile(std::string filename);
    int Insert_First(int value);
    int Insert_Last(int value);
    int Insert_Manual(int pos, int value);
    void Del_First();
    void Del_Last();
    int Del_Manual(int pos);
    int Update(int pos, int value);
    int Access(int pos);
    int Search(int value);

    // update
    virtual void refreshAnimation() {}
    sf::Vector2i updateKBM(sf::Vector2f mousePos, MOUSE mouseType, KEYBOARD keyboardType);
    void updateTypeAnimation(int type);
    virtual void run(int manipulate, int way, std::vector<std::string> vecStr) = 0;

    void updateTimeAnimation();
    virtual int update();   /// return step

    // print
    virtual void refreshrender();
    virtual void render();
};

#endif