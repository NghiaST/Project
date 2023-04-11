#include "manipulate_animation.hpp"

Manipulate_Animation_Node::Manipulate_Animation_Node(int statusAnimation, int status, sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    this->statusAnimation = statusAnimation;
    this->status = status;
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}

void Manipulate_Animation_Node::build(CircleNode* node)
{
    node->prepareAnimation(startPoint, endPoint, statusAnimation, status);
}

void Manipulate_Animation_ArrayNode::setNode(CircleNode *node)
{
    this->node = node;
}

void Manipulate_Animation_ArrayNode::addStep(int statusAnimation, int status, sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    listStep.push_back(Manipulate_Animation_Node(statusAnimation, status, startPoint, endPoint));
}

void Manipulate_Animation_ArrayNode::runTime(double time)
{
    if (listStep.size() == 0) {
        std::cout << "Bug in manipulate\n";
        exit(1);
    }
    int step = (int) (time / this->steptime);
    if (step >= listStep.size()) step = listStep.size() - 1;
    if (step < 0) step = 0;
    runStep(step, time - step * this->steptime);
}

void Manipulate_Animation_ArrayNode::runStep(int step, double time)
{
    if (listStep.size() == 0) {
        std::cout << "Bug in manipulate\n";
        exit(1);
    }
    if (step >= listStep.size()) step = listStep.size() - 1;
    if (step < 0) step = 0;

    if (step != previous_step)
    {
        listStep[step].build(node);
        previous_step = step;
    }
    node->updateAnimation(time);
}

void Manipulate_Animation_ArrayNode::clearStep()
{
    listStep.clear();
    previous_step = -1;
}

Manipulate_Animation_Arrow::Manipulate_Animation_Arrow(int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    this->statusAnimation = statusAnimation;
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->nextStartPoint = nextStartPoint;
    this->nextEndPoint = nextEndPoint;
}

void Manipulate_Animation_Arrow::build(ArrowNode *arrow)
{
    arrow->setAllPoint(startPoint, endPoint, nextStartPoint, nextEndPoint);
    arrow->setStatusAnimation(statusAnimation);
}

void Manipulate_Animation_ArrayArrow::setArrow(ArrowNode *arrow)
{
    this->arrow = arrow;
}

void Manipulate_Animation_ArrayArrow::addStep(int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    listStep.push_back(Manipulate_Animation_Arrow(statusAnimation, startPoint, endPoint, nextStartPoint, nextEndPoint));
}

void Manipulate_Animation_ArrayArrow::runTime(double time)
{
    int step = (int) (time / this->steptime);
    if (step >= listStep.size()) step = listStep.size() - 1;
    if (step < 0) step = 0;
    runStep(step, time - step * this->steptime);
}

void Manipulate_Animation_ArrayArrow::runStep(int step, double time)
{
    if (listStep.size() == 0) {
        std::cout << "Bug in manipulate Animation\n";
        exit(1);
    }
    if (step >= listStep.size()) step = listStep.size() - 1;
    if (step < 0) step = 0;

    if (step != previous_step)
    {
        listStep[step].build(arrow);
        previous_step = step;
    }
    arrow->setTime(time);
}

void Manipulate_Animation_ArrayArrow::clearStep()
{
    listStep.clear();
    previous_step = -1;
}
