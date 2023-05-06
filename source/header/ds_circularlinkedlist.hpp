#ifndef __ds_circularlinkedlist_hpp__
#define __ds_circularlinkedlist_hpp__
#include "struct_ds.hpp"

struct StructCircularLinkedList : StructDataStructure {
public:
    StructCircularLinkedList(VisualizationSettings* settings, bool active);
    ~StructCircularLinkedList();

    void refreshAnimation() override;
    void run(int manipulate, int way, std::vector<std::string> vecStr) override;

    void Animation_Initialize(int way);
    void Animation_Insert_First();
    void Animation_Insert_Last();
    void Animation_Insert_Manual();
    void Animation_Del_First();
    void Animation_Del_Last();
    void Animation_Del_Manual();
    void Animation_Update();
    void Animation_Search();
};
#endif