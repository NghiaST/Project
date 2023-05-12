#ifndef __ds_stack_hpp__
#define __ds_stack_hpp__
#include "struct_ds.hpp"

struct StructStack : StructDataStructure {
public:
    StructStack(VisualizationSettings* settings, bool active);
    ~StructStack();

    void refreshAnimation() override;
    void run(int manipulate, int way, std::vector<std::string> vecStr) override;

    void Initialize_Empty();
    void Initialize_Random();
    void Initialize_Manual(std::vector<int> arr);
    int Initialize_ExternalFile(std::string filename);
    int Push(int value);
    void Pop();
    void Clear();

    void Animation_Initialize(int way);
    void Animation_Push();
    void Animation_Pop();
    void Animation_Peek();
    void Animation_Clear();
};

#endif