#include "Node.hpp"

// Node sınıfı: BST düğümü, değer ve iki çocuk işaretçisi tutar

Node::Node(int val)
{
    value = val;
    left = nullptr;
    right = nullptr;
}

Node::~Node()
{
}
