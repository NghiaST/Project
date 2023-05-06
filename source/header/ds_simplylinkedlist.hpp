#ifndef __ds_simplylinkedlist_hpp__
#define __ds_simplylinkedlist_hpp__
#include "struct_ds.hpp"

struct StructSimplyLinkedList : StructDataStructure {
public:
    StructSimplyLinkedList(VisualizationSettings* settings, bool active);
    ~StructSimplyLinkedList();

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