#ifndef __manipulate_animation_hpp__
#define __manipulate_animation_hpp__
#include <SFML/Graphics.hpp>
#include <vector>
#include "node.hpp"
#include "arrow.hpp"

const double Delay = 0.3;
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
    sf::Vector2f presentPoint;
    int statusAnimation;
    int status;

    double delay = Delay;
    double fulltime = Fulltime;
    double steptime = Steptime;
    // double total_time;
    // double time;
    std::vector<Manipulate_Animation_Node> listStep;
    int previous_step = -1;

    void addStep(int statusAnimation, sf::Vector2f presentPoint, sf::Vector2f nextPoint);

public:
    Manipulate_Animation_ArrayNode() {}
    void setNode(CircleNode* node);
    void addStep(int statusAnimation);
    void addStep(int statusAnimation, sf::Vector2f nextPoint);
    void skipMultiStep(int count);
    void runTime(double time);
    void runStep(int step, double time);
    void clearStep();

    void setStatusAnimation(int statusAnimation);
    void setPresentPoint(sf::Vector2f presentPoint);
    void setup(CircleNode* node, sf::Vector2f presentPoint, bool view);
    double getTotaltime();
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
    sf::Vector2f startPoint, endPoint;
    int statusAnimation;

    double delay = Delay;
    double fulltime = Fulltime;
    double steptime = Steptime;
    // double total_time;
    // double time;
    std::vector<Manipulate_Animation_Arrow> listStep;
    int previous_step = -1;

    void addStep(int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);

public:
    Manipulate_Animation_ArrayArrow() {}
    void setArrow(ArrowNode* arrow);
    void setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint);

    void addStepNoChange();
    void addStep(int statusAnimation);
    void addStep(int statusAnimation, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    void skipMultiStep(int count);
    void runTime(double time);
    void runStep(int step, double time);
    void clearStep();

    void setStatusAnimation(int statusAnimation);
    int getStep();
    void setup(ArrowNode* arrow, sf::Vector2f startPoint, sf::Vector2f endPoint, bool view);
};

#endif