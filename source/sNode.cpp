#include "sNode.hpp"

sNode1D::sNode1D() : next(nullptr), value(0) {}
sNode1D::sNode1D(int value) : next(nullptr), value(value) {}

sNode2D::sNode2D() : next(nullptr), prev(nullptr), value(0) {}
sNode2D::sNode2D(int value) : next(nullptr), prev(nullptr), value(value) {}

void connectNode(sNode2D* nodex, sNode2D* nodey)
{
    if (nodex) nodex->next = nodey;
    if (nodey) nodey->prev = nodex;
}