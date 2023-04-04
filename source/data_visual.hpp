#ifndef __data_visual_hpp__
#define __data_visual_hpp__
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include "state.hpp"
#include "button.hpp"

struct DataVisualization {
private:
    // Varibles
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Font font;
    bool running = true;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    std::stack<State*> states;

    std::vector<Button> listbutton;

    // Initializations
    void InitWindow();
    void InitStates();
    void InitButton();

    //Functions
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
    // Constructors/Destructors
    DataVisualization();
    virtual ~DataVisualization();

    // Mouse
    void updateMousePositions();

    // Functions
    void Initialize();
    void processEvents();
    void update();
    void render();
    void run();
};

#endif