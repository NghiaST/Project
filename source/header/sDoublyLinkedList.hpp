#ifndef __sDoublyLinkedList_hpp__
#define __sDoublyLinkedList_hpp__
#include <iostream>
#include <vector>
#include "sNode.hpp"

struct sDoublyLinkedList {
private:
    sNode2D *head, *tail;
public:
    sDoublyLinkedList();
    ~sDoublyLinkedList();
    std::vector<int> getData();
    int getN();
    void refresh();

    void Init(std::vector<int> list);
    void Insert_Left(int value);
    void Insert_Right(int value);
    void Insert_Middle(int pos, int value);
    bool Delete_Left();
    bool Delete_Right();
    bool Delete_Middle(int pos);
    void Update(int pos, int value);
    int Search(int value);
};

#endif