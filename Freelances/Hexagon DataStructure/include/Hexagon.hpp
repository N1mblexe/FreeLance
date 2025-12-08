#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "BST.hpp"

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
    void printCorners() const;

private:
    BST *arr[6];
    int size;
};

#endif // HEXAGON_HPP
