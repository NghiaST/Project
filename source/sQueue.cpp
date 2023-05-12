#include "sDoublyLinkedList.hpp"

sDoublyLinkedList::sDoublyLinkedList()
{
    head = tail = nullptr;
}

sDoublyLinkedList::~sDoublyLinkedList()
{
    refresh();
}

std::vector<int> sDoublyLinkedList::getData()
{
    std::vector<int> list;
    for(sNode2D* tmp = head; tmp; tmp = tmp->next)
        list.push_back(tmp->value);
    return list;
}

int sDoublyLinkedList::getN()
{
    int N = 0;
    for(sNode2D* tmp = head; tmp; tmp = tmp->next)
        ++N;
    return N;
}

void sDoublyLinkedList::refresh()
{
    while (head)
        Delete_Left();
}

void sDoublyLinkedList::Init(std::vector<int> list)
{
    refresh();
    for(int i = (int) list.size() - 1; i >= 0; i--)
        Insert_Left(list[i]);
}

void sDoublyLinkedList::Insert_Left(int value)
{
    sNode2D* cur = new sNode2D(value);
    connectNode(cur, head);
    head = cur;
    if (!tail) tail = head;
}

void sDoublyLinkedList::Insert_Right(int value)
{
    sNode2D* cur = new sNode2D(value);
    connectNode(tail, cur);
    tail = cur;
    if (!head) head = tail;
}

void sDoublyLinkedList::Insert_Middle(int pos, int value) {
    if (pos <= 0 || pos >= getN()) return;
    sNode2D* pre = head;
    for(int i = 0; i < pos - 1; i++)
        pre = pre->next;
    sNode2D* cur = new sNode2D(value);
    connectNode(cur, pre->next);
    connectNode(pre, cur);
}

bool sDoublyLinkedList::Delete_Left() {
    if (head == nullptr)
        return false;
    sNode2D* cur = head;
    head = head->next;
    delete cur;
    return true;
}

bool sDoublyLinkedList::Delete_Right() {
    if (head == nullptr)
        return false;
    sNode2D* cur = head;
    head = head->next;
    delete cur;
    return true;
}

bool sDoublyLinkedList::Delete_Middle(int pos)
{
    sNode2D* pre = head;
    for(int i = 0; i < pos - 1; i ++)
        pre = pre->next;
    sNode2D* tmp = pre->next;
    connectNode(pre, tmp);
    delete tmp;
    return true;
}

void sDoublyLinkedList::Update(int pos, int value)
{
    if (pos < 0 || pos >= getN()) return;
    sNode2D* cur = head;
    for(int i = 0; i < pos; i++)
        cur = cur->next;
    cur->value = value;
}

int sDoublyLinkedList::Search(int value)
{
    int pos = 0;
    sNode2D* cur = head;
    while (cur && cur->value != value)
        cur = cur->next, ++pos;
    if (!cur) return -1;
    return pos;
}