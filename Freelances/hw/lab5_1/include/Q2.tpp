#ifndef Q2_TPP
#define Q2_TPP

template <typename T>
size_t getIndex(const T &val, const T *preorder, size_t size)
{
    for (size_t i = 0; i < size; i++)
        if (preorder[i] == val)
            return i;

    return (size_t)-1;
}

template <typename T>
bool checkHeights(AVLNode<T> *root, const T *preorder, const int *heights, size_t size)
{
    if (root == nullptr)
        return true;

    size_t index = getIndex(root->data, preorder, size);

    if (index == (size_t)-1 || root->height != heights[index])
        return false;

    return checkHeights(root->left, preorder, heights, size) && checkHeights(root->right, preorder, heights, size);
}

template <typename T>
AVLTree<T> *reconstructAVL(const T *preorder, const int *heights, size_t size)
{
    if (preorder == nullptr || heights == nullptr || size == 0)
        return nullptr;

    for (size_t i = 0; i < size; ++i)
        if (heights[i] <= 0)
            return nullptr;

    AVLTree<T> *tree = new AVLTree<T>();
    bool invalid = false;

    for (size_t i = 0; i < size; ++i)
    {
        if (!tree->insert(preorder[i]))
        {
            invalid = true;
            break;
        }
    }
    if (!invalid && tree->nodeCount() != size)
        invalid = true;

    if (!invalid && !checkHeights(tree->getRoot(), preorder, heights, size))
        invalid = true;

    if (invalid)
    {
        delete tree;
        return nullptr;
    }

    return tree;
}

#endif //Q2_TPP
