#include "BST.hpp"
#include <cstddef>

// BST sınıfı: düğüm ekleme, yükseklik hesaplama ve postorder çıkarma sağlar

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clear();
}

void BST::insert(int value)
{
    Node **curr = &root;
    while (*curr)
    {
        if (value <= (*curr)->value)
        {
            curr = &((*curr)->left);
        }
        else
        {
            curr = &((*curr)->right);
        }
    }
    *curr = new Node(value);
}

int BST::getHeight() const
{
    return getHeightHelper(root);
}

int BST::getHeightHelper(Node *node) const
{
    if (!node)
        return 0;
    int lh = getHeightHelper(node->left);
    int rh = getHeightHelper(node->right);
    return 1 + (lh > rh ? lh : rh);
}

void BST::postorderExtract(int *&arr, int &size)
{
    //  : postorder ile değerleri al ve ağacı temizle
    size = countNodes(root);
    arr = new int[size];
    int idx = 0;
    postorderHelper(root, arr, idx);
    clear();
}

void BST::postorderHelper(Node *node, int *arr, int &idx)
{
    if (!node)
        return;
    postorderHelper(node->left, arr, idx);
    postorderHelper(node->right, arr, idx);
    arr[idx++] = node->value;
}

int BST::countNodes(Node *node) const
{
    if (!node)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BST::getRootValue() const
{
    return root ? root->value : 0;
}

void BST::clear()
{
    clearHelper(root);
    root = nullptr;
}

void BST::clearHelper(Node *node)
{
    if (!node)
        return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}
