#include "sQueue.hpp"

sQueue::sQueue()
{
    head = tail = nullptr;
}

sQueue::~sQueue()
{
    refresh();
}

std::vector<int> sQueue::getData()
{
    std::vector<int> list;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        list.push_back(tmp->value);
    return list;
}

int sQueue::getN()
{
    int N = 0;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        ++N;
    return N;
}

void sQueue::refresh()
{
    Clear();
}

void sQueue::Init(std::vector<int> list)
{
    refresh();
    for(int i = (int) list.size() - 1; i >= 0; i--)
        Enqueue(list[i]);
}

void sQueue::Enqueue(int value) {
    sNode1D* cur = new sNode1D(value);
    cur->next = head;
    head = cur;
    if (!tail) tail = head;
}

void sQueue::Dequeue() {
    if (head == nullptr)
        return;
    sNode1D* cur = head;
    head = head->next;
    if (tail == cur) tail = head;
    delete cur;
}

void sQueue::Clear() {
    while (head)
        Dequeue();
}