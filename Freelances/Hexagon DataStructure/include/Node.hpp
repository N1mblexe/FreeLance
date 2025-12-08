#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
    int value;
    Node *left;
    Node *right;

    Node(int val);
    ~Node();
};

#endif // NODE_HPP
