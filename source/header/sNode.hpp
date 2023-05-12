#ifndef __sNode_hpp__
#define __sNode_hpp__

struct sNode1D {
    sNode1D* next;
    int value;

    sNode1D();
    sNode1D(int value);
};

struct sNode2D {
    sNode2D *prev, *next;
    int value;
    
    sNode2D();
    sNode2D(int value);
};
void connectNode(sNode2D* nodex, sNode2D* nodey);

#endif