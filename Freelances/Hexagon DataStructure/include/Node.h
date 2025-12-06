#ifndef NODE_H
#define NODE_H

class Node
{
public:
    int value;
    Node *left;
    Node *right;

    Node(int val);
    ~Node();
};

#endif // NODE_H
