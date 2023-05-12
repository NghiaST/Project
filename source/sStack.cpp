#include "sStack.hpp"

sStack::sStack()
{
    head = nullptr;
}

sStack::~sStack()
{
    refresh();
}

std::vector<int> sStack::getData()
{
    std::vector<int> list;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        list.push_back(tmp->value);
    return list;
}

int sStack::getN()
{
    int N = 0;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        ++N;
    return N;
}

void sStack::refresh()
{
    Clear();
}

void sStack::Init(std::vector<int> list)
{
    refresh();
    for(int i = (int) list.size() - 1; i >= 0; i--)
        Push(list[i]);
}

void sStack::Push(int value) {
    sNode1D* cur = new sNode1D(value);
    cur->next = head;
    head = cur;
}

void sStack::Pop() {
    if (head == nullptr)
        return;
    sNode1D* cur = head;
    head = head->next;
    delete cur;
}

void sStack::Clear() {
    while (head)
        Pop();
}