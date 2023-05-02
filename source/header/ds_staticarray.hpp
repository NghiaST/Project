#ifndef __ds_staticarray_hpp__
#define __ds_staticarray_hpp__
#include "struct_ds.hpp"

struct StructStaticArray : StructDataStructure {
private:
    int size_fixed;
public:
    StructStaticArray(VisualizationSettings* settings, bool active);
    ~StructStaticArray();

    void refreshAnimation() override;
    void run(int manipulate, int way, std::vector<std::string> vecStr);

    void Initialize_Empty_Fixedsize(int size_fixed);
    void Initialize_Random_Unfixedsize();
    void Initialize_Manual_Fixedsize(int size_fixed, std::vector<int> arr);
    int Initialize_ExternalFile_Fixedsize(int size_fixed, std::string filename);

    void Animation_Initialize(int way);
    void Animation_Insert_First();
    void Animation_Insert_Last();
    void Animation_Insert_Manual();
    void Animation_Del_First();
    void Animation_Del_Last();
    void Animation_Del_Manual();
    void Animation_Update();
    void Animation_Access();
    void Animation_Search();
};

#endif