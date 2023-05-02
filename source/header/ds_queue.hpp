#ifndef __ds_queue_hpp__
#define __ds_queue_hpp__
#include "struct_ds.hpp"

struct StructQueue : StructDataStructure {
public:
    StructQueue(VisualizationSettings* settings, bool active);
    ~StructQueue();

    void refreshAnimation() override;
    void run(int manipulate, int way, std::vector<std::string> vecStr) override;

    int Enqueue(int value);
    void Dequeue();
    void Clear();

    void Animation_Initialize(int way);
    void Animation_Enqueue();
    void Animation_Dequeue();
    void Animation_Clear();
};

#endif