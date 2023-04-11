#ifndef __manipulate_animation_hpp__
#define __manipulate_animation_hpp__
#include <SFML/Graphics.hpp>
#include <vector>
#include "node.hpp"
#include "arrow.hpp"

const double Delay = 0.2;
const double Fulltime = 1;
const double Steptime = Delay + Fulltime;

struct Manipulate_Animation_Node {
public:
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
    int statusAnimation;
    int status;
public:
    Manipulate_Animation_Node(int statusAnimation, int status, sf::Vector2f startPoint, sf::Vector2f endPoint);
    void build(CircleNode* node);
};

struct Manipulate_Animation_ArrayNode {
private:
    CircleNode* node;
    double delay = Delay;
    double fulltime = Fulltime;
    double steptime = Steptime;
    // double total_time;
    // double time;
    std::vector<Manipulate_Animation_Node> listStep;
    int previous_step = -1;

public:
    
    Manipulate_Animation_ArrayNode() {}
    void setNode(CircleNode* node);
    void addStep(int statusAnimation, int status, sf::Vector2f startPoint, sf::Vector2f endPoint);
    void addMultiStep(int count, int statusAnimation, int status, sf::Vector2f startPoint, sf::Vector2f endPoint);
    void runTime(double time);
    void runStep(int step, double time);
    void clearStep();

    int getStep();
};

struct Manipulate_Animation_Arrow {
private:
    int statusAnimation;
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
    sf::Vector2f nextStartPoint;
    sf::Vector2f nextEndPoint;
public:
    Manipulate_Animation_Arrow(int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    void build(ArrowNode* arrow);
};

struct Manipulate_Animation_ArrayArrow {
private:
    ArrowNode* arrow;
    double delay = Delay;
    double fulltime = Fulltime;
    double steptime = Steptime;
    // double total_time;
    // double time;
    std::vector<Manipulate_Animation_Arrow> listStep;
    int previous_step = -1;

public:
    Manipulate_Animation_ArrayArrow() {}
    void setArrow(ArrowNode* arrow);
    void addStep(int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    void addMultiStep(int count, int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    void runTime(double time);
    void runStep(int step, double time);
    void clearStep();

    
    int getStep();
};

#endif