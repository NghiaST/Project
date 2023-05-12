#include "sSinglyLinkedList.hpp"

sSinglyLinkedList::sSinglyLinkedList()
{
    head = tail = nullptr;
}

sSinglyLinkedList::~sSinglyLinkedList()
{
    refresh();
}

std::vector<int> sSinglyLinkedList::getData()
{
    std::vector<int> list;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        list.push_back(tmp->value);
    return list;
}

int sSinglyLinkedList::getN()
{
    int N = 0;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        ++N;
    return N;
}

void sSinglyLinkedList::refresh()
{
    while (head)
        Delete_Left();
}

void sSinglyLinkedList::Init(std::vector<int> list)
{
    refresh();
    for(int i = (int) list.size() - 1; i >= 0; i--)
        Insert_Left(list[i]);
}

void sSinglyLinkedList::Insert_Left(int value)
{
    sNode1D* cur = new sNode1D(value);
    cur->next = head;
    head = cur;
    if (!tail) tail = head;
}

void sSinglyLinkedList::Insert_Right(int value)
{
    sNode1D* cur = new sNode1D(value);
    tail->next = cur;
    tail = cur;
    if (!head) head = tail;
}

void sSinglyLinkedList::Insert_Middle(int pos, int value) {
    if (pos <= 0 || pos >= getN()) return;
    sNode1D* pre = head;
    for(int i = 0; i < pos - 1; i++)
        pre = pre->next;
    sNode1D* cur = new sNode1D(value);
    cur->next = pre->next;
    pre->next = cur;
}

bool sSinglyLinkedList::Delete_Left() {
    if (head == nullptr)
        return false;
    sNode1D* cur = head;
    head = head->next;
    delete cur;
    return true;
}

bool sSinglyLinkedList::Delete_Right() {
    if (head == nullptr)
        return false;
    sNode1D* cur = head;
    head = head->next;
    delete cur;
    return true;
}

bool sSinglyLinkedList::Delete_Middle(int pos)
{
    sNode1D* pre = head;
    for(int i = 0; i < pos - 1; i ++)
        pre = pre->next;
    sNode1D* tmp = pre->next;
    pre->next = tmp->next;
    delete tmp;
    return true;
}

void sSinglyLinkedList::Update(int pos, int value)
{
    if (pos < 0 || pos >= getN()) return;
    sNode1D* cur = head;
    for(int i = 0; i < pos; i++)
        cur = cur->next;
    cur->value = value;
}

int sSinglyLinkedList::Search(int value)
{
    int pos = 0;
    sNode1D* cur = head;
    while (cur && cur->value != value)
        cur = cur->next, ++pos;
    if (cur == nullptr) return -1;
    return pos;
}