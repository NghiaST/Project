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

void Manipulate_Animation_ArrayNode::addStep(int statusAnimation)
{
    if (statusAnimation == NOD_MOVE) {
        std::cout << "Error manipulatee_animation_arrayNode: NOD_MOVE don't have position\n";
        exit(14);
    }
    this->addStep(statusAnimation, this->presentPoint, this->presentPoint);
}
void Manipulate_Animation_ArrayNode::addStep(int statusAnimation, sf::Vector2f nextPoint)
{
    this->addStep(statusAnimation, this->presentPoint, nextPoint);
}
void Manipulate_Animation_ArrayNode::addStep(int statusAnimation, sf::Vector2f presentPoint, sf::Vector2f nextPoint)
{
    setStatusAnimation(statusAnimation);
    listStep.push_back(Manipulate_Animation_Node(this->statusAnimation, this->status, presentPoint, nextPoint));
    setPresentPoint(nextPoint);
}

void Manipulate_Animation_ArrayNode::skipMultiStep(int count)
{
    while (count--) this->addStep(NOD_SKIP);
}

void Manipulate_Animation_ArrayNode::runTime(double time)
{
    if (listStep.size() == 0) {
        std::cout << "Bug in manipulate 1 : listStep size = 0\n";
        exit(1);
    }
    int step = (int) (1.0L * time / this->steptime);
    if (step >= listStep.size()) step = listStep.size() - 1;
    if (step < 0) step = 0;
    runStep(step, time - step * this->steptime);
}

void Manipulate_Animation_ArrayNode::runStep(int step, double time)
{
    if (listStep.size() == 0) {
        std::cout << "Bug in manipulate 2: listStep size = 0\n";
        exit(1);
    }
    if (step >= listStep.size()) step = listStep.size() - 1;

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
    status = 0;
}

void Manipulate_Animation_ArrayNode::setStatusAnimation(int statusAnimation)
{
    switch (statusAnimation)
    {
        case NOD_NOPE : this->status = -1; break;
        case NOD_STABLE : break;
        case NOD_RECOLOR : std::cout << "Error manipulate_animation.cpp getBuildStatusAnimation: shouldn't use it\n"; break;
        case NOD_APPEAR : this->status = 3; break;
        case NOD_DEL : break;
        case NOD_MOVE : break;
        case NOD_NORMAL : statusAnimation = NOD_STABLE; status = 0; break;
        case NOD_SHOW : statusAnimation = NOD_RECOLOR; status = 1; break;
        case NOD_SOLVE : statusAnimation = NOD_RECOLOR; status = 4; break;
        case NOD_UNSHOW : statusAnimation = NOD_RECOLOR; status = 2; break;
        case NOD_ACTIVE : statusAnimation = NOD_RECOLOR; status = 3; break;
        case NOD_SKIP : 
            switch (this->statusAnimation)
            {
                case NOD_NOPE : case NOD_DEL :
                    statusAnimation = NOD_NOPE;
                    break;
                case NOD_STABLE : case NOD_RECOLOR : case NOD_APPEAR : case NOD_MOVE :
                    statusAnimation = NOD_STABLE;
                    break;
                default :
                    std::cout << "Error manipulate_animation.cpp getBuildStatusAnimation nod_skip\n";
                    exit(11);
            }
            break;
        default :
            std::cout << "Error node.cpp prepareAnimation statusAnimation out of range\n";
            exit(12);
            break;
    }
    this->statusAnimation = statusAnimation;
}

void Manipulate_Animation_ArrayNode::setPresentPoint(sf::Vector2f presentPoint)
{
    this->presentPoint = presentPoint;
}

void Manipulate_Animation_ArrayNode::setup(CircleNode *node, sf::Vector2f presentPoint, bool view)
{
    clearStep();
    setNode(node);
    setPresentPoint(presentPoint);
    if (view)
        setStatusAnimation(AR_NORMAL);
    else
        setStatusAnimation(AR_NOPE);
}

double Manipulate_Animation_ArrayNode::getTotaltime()
{
    return this->listStep.size() * steptime + delay * 5;
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

void Manipulate_Animation_ArrayArrow::setPoint(sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}

void Manipulate_Animation_ArrayArrow::addStepNoChange()
{
    if (this->listStep.size() == 0)
    {
        std::cout << "Error add step no change: listStep size = 0\n";
        exit(6);
    }
}

void Manipulate_Animation_ArrayArrow::addStep(int statusAnimation)
{
    if (statusAnimation == AR_MOVE) {
        std::cout << "manipulate_animation Manipulate_Animation_ArrayArrow : add MOVE without position\n";
        exit(13);
    }
    this->addStep(statusAnimation, this->startPoint, this->endPoint, this->startPoint, this->endPoint);
}
void Manipulate_Animation_ArrayArrow::addStep(int statusAnimation, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    this->addStep(statusAnimation, this->startPoint, this->endPoint, nextStartPoint, nextEndPoint);
}
void Manipulate_Animation_ArrayArrow::addStep(int statusAnimation, sf::Vector2f startPoint, sf::Vector2f endPoint, sf::Vector2f nextStartPoint, sf::Vector2f nextEndPoint)
{
    setStatusAnimation(statusAnimation);
    listStep.push_back(Manipulate_Animation_Arrow(this->statusAnimation, startPoint, endPoint, nextStartPoint, nextEndPoint));
    this->startPoint = nextStartPoint;
    this->endPoint = nextEndPoint;
}

void Manipulate_Animation_ArrayArrow::skipMultiStep(int count)
{
    while (count--) this->addStep(AR_SKIP);
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
        std::cout << "Bug in manipulate Animation 3: listStep size = 0\n";
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

void Manipulate_Animation_ArrayArrow::setStatusAnimation(int statusAnimation)
{
    if (statusAnimation == AR_SKIP)
    {
        switch (this->statusAnimation)
        {
            case AR_NOPE : case AR_DEL :
                statusAnimation = AR_NOPE;
                break;
            case AR_NORMAL : case AR_NORMALMOVE :
                statusAnimation = AR_NORMAL;
                break; 
            case AR_ACTIVE : case AR_ACTIVEMOVE : case AR_CREATE : case AR_COLOR_TO :
                statusAnimation = AR_ACTIVE;
                break;
            default : 
                std::cout << this->statusAnimation << " Manipulateanimation.cpp setstatusanimation\n";
                exit(20);
        }
    }

    if (statusAnimation == AR_MOVE)
    {
        switch (this->statusAnimation)
        {
            case AR_NORMAL : case AR_NORMALMOVE :
                statusAnimation = AR_NORMALMOVE;
                break;
            case AR_ACTIVE : case AR_ACTIVEMOVE : case AR_CREATE : case AR_COLOR_TO :
                statusAnimation = AR_ACTIVEMOVE;
                break;
            case AR_NOPE : case AR_DEL : 
                statusAnimation = AR_NOPE;
                break;
            default : 
                std::cout << "Error manipulate_animation.cpp addStep error value\n";
                exit(7);
        }
    }
    this->statusAnimation = statusAnimation;
}

int Manipulate_Animation_ArrayArrow::getStep()
{
    return this->listStep.size();
}

void Manipulate_Animation_ArrayArrow::setup(ArrowNode* arrow, sf::Vector2f startPoint, sf::Vector2f endPoint, bool view)
{
    clearStep();
    setArrow(arrow);
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    if (view)
        setStatusAnimation(AR_NORMAL);
    else 
        setStatusAnimation(AR_NOPE);
}
