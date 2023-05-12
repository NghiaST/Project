#ifndef __sDynamicArray_hpp__
#define __sDynamicArray_hpp__
#include <iostream>
#include <vector>

struct sDynamicArray {
private:
    int *data;
    int N;
public:
    ~sDynamicArray();
    void refresh();
    std::vector<int> getData();
    int getN();

    void Init(std::vector<int> list);
    void Insert(int pos, int value);
    void Del(int pos);
    void Update(int pos, int value);
    int Search(int value);
};

#endif