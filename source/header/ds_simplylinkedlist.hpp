#ifndef __ds_simplylinkedlist_hpp__
#define __ds_simplylinkedlist_hpp__
#include "struct_ds.hpp"

struct StructSimplyLinkedList : StructDataStructure {
public:
    StructSimplyLinkedList(VisualizationSettings* settings, bool active);
    ~StructSimplyLinkedList();

    void refreshAnimation() override;
    void run(int manipulate, int way, std::vector<std::string> vecStr) override;

    void Initialize_Empty();
    void Initialize_Random();
    void Initialize_Manual(std::vector<int> arr);
    int Initialize_ExternalFile(std::string filename);
    int Insert_First(int value);
    int Insert_Last(int value);
    int Insert_Manual(int pos, int value);
    void Del_First();
    void Del_Last();
    int Del_Manual(int pos);
    int Update(int pos, int value);
    int Search(int value);

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