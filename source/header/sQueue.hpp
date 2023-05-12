#ifndef __sQueue_hpp__
#define __sQueue_hpp__
#include <iostream>
#include <vector>
#include "sNode.hpp"

struct sQueue {
private:
    sNode1D *head, *tail;
public:
    sQueue();
    ~sQueue();
    std::vector<int> getData();
    int getN();
    void refresh();

    void Init(std::vector<int> list);
    void Enqueue(int value);
    void Dequeue();
    void Clear();
};

#endif