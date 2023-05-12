#include "sDynamicArray.hpp"

sDynamicArray::~sDynamicArray()
{
    refresh();
}

void sDynamicArray::refresh()
{
    if (data) delete[] data;
    N = 0;
}

std::vector<int> sDynamicArray::getData()
{
    std::vector<int> list(data, data + N);
    return list;
}

int sDynamicArray::getN()
{
    return N;
}

void sDynamicArray::Init(std::vector<int> list)
{
    refresh();
    N = list.size();
    data = new int[N];

    for (int i = 0; i < N; i++) {
        data[i] = list[i];
    }
}

void sDynamicArray::Insert(int pos, int value) {
    if (pos < 0 || pos > N)
        return;
    int* newdata = new int[++N];

    for(int i = 0, j = 0; i < N - 1; i++, j++)
    {
        if (j == pos) 
            j++;
        newdata[j] = data[i];
    }
    refresh();
    data = newdata;
}

void sDynamicArray::Del(int pos) {
    if (pos < 0 || pos >= N)
        return;
    int* newdata = new int[--N];
        
    for(int i = 0, j = 0; j < N; i++, j++)
    {
        if (i == pos) 
            i++;
        newdata[j] = data[i];
    }
    refresh();
    data = newdata;
}

void sDynamicArray::Update(int pos, int value) {
    if (pos < 0 || pos >= N)
        return;
    data[pos] = value;
}

int sDynamicArray::Search(int value) {
    for (int i = 0; i < N; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
}