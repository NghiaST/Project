#ifndef __manipulate_animation_hpp__
#define __manipulate_animation_hpp__
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <memory>
#include "node.hpp"
#include "arrow.hpp"

const double Delay = 0.3;
const double Fulltime = 1;
const double Steptime = Delay + Fulltime;

struct Manipulate_Animation_Node {
private:
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
    int statusAnimation;
    int preStatus;
    int status;
    std::string word;
public:
    Manipulate_Animation_Node(int statusAnimation, int preStatus, int status, sf::Vector2f startPoint, sf::Vector2f endPoint, std::string word);
    void build(Node* node);
};

struct Manipulate_Animation_ArrayNode {
private:
    Node* node;
    sf::Vector2f presentPoint;
    int statusAnimation;
    int preStatus;
    int status;
    std::string word;

    double delay = Delay;
    double fulltime = Fulltime;
    double steptime = Steptime;

    std::vector<Manipulate_Animation_Node> listStep;
    int previous_step = -1;

public:
    //Manipulate_Animation_ArrayNode() {}
    void setup(std::unique_ptr<Node>* node, sf::Vector2f presentPoint, int word, bool view);
    void setNode(std::unique_ptr<Node>* node);
    void setWord(int number);
    void setWord(std::string word);
    void setStatusAnimation(int statusAnimation);
    void setPresentPoint(sf::Vector2f presentPoint);

    void addStep(int statusAnimation);
    void addStep(int statusAnimation, sf::Vector2f nextPoint);
    void addStep(int statusAnimation, sf::Vector2f presentPoint, sf::Vector2f nextPoint);
    void skipMultiStep(int count);

    void runTime(double time);
    void runStep(int step, double time);

    void clearStep();
    double getTotalstep();
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

    std::vector<Manipulate_Animation_Arrow> listStep;
    int previous_step = -1;

public:
    //Manipulate_Animation_ArrayArrow() {}
    void setup(ArrowNode* arrow, sf::Vector2f startPoint, sf::Vector2f endPoint, bool view);
    void setArrow(ArrowNode* arrow);
    void setStatusAnimation(int statusAnimation);
    void setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint);

    void addStep(int statusAnimation);
    void addStep(int statusAnimation, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    void addStep(int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint);
    void skipMultiStep(int count);

    void runTime(double time);
    void runStep(int step, double time);

    void clearStep();
    int getStep();
};

#endif