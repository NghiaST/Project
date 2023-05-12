#include "sStaticArray.hpp"

sStaticArray::~sStaticArray()
{
    refresh();
}

void sStaticArray::refresh()
{
    if (data) delete[] data;
    N = fixedSize = 0;
}

std::vector<int> sStaticArray::getData()
{
    std::vector<int> list(data, data + N);
    return list;
}

int sStaticArray::getN()
{
    return N;
}

int sStaticArray::getFixedSize()
{
    return fixedSize;
}

void sStaticArray::Init(int fixedSize, std::vector<int> list)
{
    refresh();
    this->fixedSize = fixedSize;
    data = new int[fixedSize];
    N = list.size();

    for (int i = 0; i < fixedSize; i++) {
        if (i < N) {
            data[i] = list[i];
        } else {
            data[i] = 0;
        }
    }
}

void sStaticArray::Insert(int pos, int value) {
    if (pos < 0 || pos >= fixedSize)
        return;
    if (N == fixedSize)
        return;
    N++;
    for(int i = N - 2; i >= pos; i++)
        data[i + 1] = data[i];
    data[pos] = value;
}

void sStaticArray::Del(int pos) {
    if (pos < 0 || pos >= N)
        return;
        
    for(int i = N - 1; i > pos; i--)
        data[i - 1] = data[i];
    data[N--] = 0;
}

void sStaticArray::Update(int pos, int value) {
    if (pos < 0 || pos >= N)
        return;
    data[pos] = value;
}

int sStaticArray::Search(int value) {
    for (int i = 0; i < N; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
}