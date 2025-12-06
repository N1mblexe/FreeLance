#ifndef BST_H
#define BST_H

#include "Node.h"

class BST
{
public:
    BST();
    ~BST();
    void insert(int value);
    int getHeight() const;
    void postorderExtract(int *&arr, int &size);
    int getRootValue() const;
    void clear();

private:
    Node *root;
    int getHeightHelper(Node *node) const;
    void postorderHelper(Node *node, int *arr, int &idx);
    int countNodes(Node *node) const;
    void clearHelper(Node *node);
};

#endif // BST_H
