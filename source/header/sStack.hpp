#ifndef __sStack_hpp__
#define __sStack_hpp__
#include <iostream>
#include <vector>
#include "sNode.hpp"

struct sStack {
private:
    sNode1D* head;
public:
    sStack();
    ~sStack();
    std::vector<int> getData();
    int getN();
    void refresh();

    void Init(std::vector<int> list);
    void Push(int value);
    void Pop();
    void Clear();
};

#endif