#ifndef __ds_dynamicarray_hpp__
#define __ds_dynamicarray_hpp__
#include "struct_ds.hpp"

struct StructDynamicArray : StructDataStructure {
public:
    StructDynamicArray(VisualizationSettings* settings, bool active);
    ~StructDynamicArray();

    void refreshAnimation() override;
    void run(int manipulate, int way, std::vector<std::string> vecStr);

    void Allocate(int size, int value);

    void Animation_Initialize(int way);
    void Animation_Insert_First();
    void Animation_Insert_Last();
    void Animation_Insert_Manual();
    void Animation_Del_First();
    void Animation_Del_Last();
    void Animation_Del_Manual();
    void Animation_Update();
    void Animation_Allocate();
    void Animation_Access();
    void Animation_Search();
};

#endif