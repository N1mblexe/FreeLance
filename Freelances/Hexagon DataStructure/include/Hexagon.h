#ifndef HEXAGON_H
#define HEXAGON_H

#include "BST.h"

class Hexagon
{
public:
    Hexagon();
    ~Hexagon();
    bool isFull() const;
    bool isEmpty() const;
    void enqueue(BST *tree);
    BST *dequeueFIFO();
    BST *dequeuePriority();
    int getDisplayValue() const;
    int getSize() const;
    BST *getBST(int idx) const;

private:
    BST *arr[6];
    int size;
};

#endif // HEXAGON_H
