#ifndef __sStaticArray_hpp__
#define __sStaticArray_hpp__
#include <iostream>
#include <vector>

struct sStaticArray {
private:
    int *data;
    int N;
    int fixedSize;
public:
    ~sStaticArray();
    void refresh();
    std::vector<int> getData();
    int getN();
    int getFixedSize();

    void Init(int fixedSize, std::vector<int> list);
    void Insert(int pos, int value);
    void Del(int pos);
    void Update(int pos, int value);
    int Search(int value);
};

#endif