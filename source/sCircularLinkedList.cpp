#include "sCircularLinkedList.hpp"

sCircularLinkedList::sCircularLinkedList()
{
    head = tail = nullptr;
}

sCircularLinkedList::~sCircularLinkedList()
{
    refresh();
}

std::vector<int> sCircularLinkedList::getData()
{
    std::vector<int> list;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        list.push_back(tmp->value);
    return list;
}

int sCircularLinkedList::getN()
{
    int N = 0;
    for(sNode1D* tmp = head; tmp; tmp = tmp->next)
        ++N;
    return N;
}

void sCircularLinkedList::refresh()
{
    while (head)
        Delete_Left();
}

void sCircularLinkedList::Init(std::vector<int> list)
{
    refresh();
    for(int i = (int) list.size() - 1; i >= 0; i--)
        Insert_Left(list[i]);
}

void sCircularLinkedList::Insert_Left(int value)
{
    sNode1D* cur = new sNode1D(value);
    if (!head) head = tail = cur;
    tail->next = cur; cur->next = head;
    head = cur;
}

void sCircularLinkedList::Insert_Right(int value)
{
    sNode1D* cur = new sNode1D(value);
    if (!head) head = tail = cur;
    tail->next = cur; cur->next = head;
    tail = cur;
}

void sCircularLinkedList::Insert_Middle(int pos, int value) {
    if (pos <= 0 || pos >= getN()) return;
    sNode1D* pre = head;
    for(int i = 0; i < pos - 1; i++)
        pre = pre->next;
    sNode1D* cur = new sNode1D(value);
    cur->next = pre->next;
    pre->next = cur;
}

bool sCircularLinkedList::Delete_Left() {
    if (head == nullptr)
        return false;
    sNode1D* cur = head;
    head = head->next;
    delete cur; 
    return true;
}

bool sCircularLinkedList::Delete_Right() {
    if (head == nullptr)
        return false;
    sNode1D* cur = head;
    head = head->next;
    delete cur;
    return true;
}

bool sCircularLinkedList::Delete_Middle(int pos)
{
    sNode1D* pre = head;
    for(int i = 0; i < pos - 1; i ++)
        pre = pre->next;
    sNode1D* tmp = pre->next;
    pre->next = tmp->next;
    delete tmp;
    return true;
}

void sCircularLinkedList::Update(int pos, int value)
{
    if (pos < 0 || pos >= getN()) return;
    sNode1D* cur = head;
    for(int i = 0; i < pos; i++)
        cur = cur->next;
    cur->value = value;
    return;
}

int sCircularLinkedList::Search(int value)
{
    int pos = 0;
    sNode1D* cur = head;
    while (cur && cur->value != value)
        cur = cur->next, ++pos;
    if (cur == nullptr) return -1;
    return pos;
}