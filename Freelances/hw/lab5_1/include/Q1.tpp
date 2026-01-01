#ifndef Q1_TPP
#define Q1_TPP

// ============================================================================
// Q1: Convert BST to Sorted Circular Doubly Linked List (In-Place)
// ============================================================================
//

template <typename T>
void ToDLLHelper(BSTNode<T> *node, BSTNode<T> *&head, BSTNode<T> *&prev)
{
    if (node == nullptr)
        return;

    ToDLLHelper(node->left, head, prev);

    if (prev == nullptr)
        head = node;
    else
    {
        node->left = prev;
        prev->right = node;
    }
    prev = node;
    ToDLLHelper(node->right, head, prev);
}

template <typename T>
BSTNode<T> *convertToCircularDLL(BST<T> &tree)
{
    BSTNode<T> *root = tree.getRoot();

    if (root == nullptr)
        return nullptr;

    BSTNode<T> *head = nullptr;
    BSTNode<T> *prev = nullptr;

    ToDLLHelper(root, head, prev);

    if (head != nullptr && prev != nullptr)
    {
        head->left = prev;
        prev->right = head;
    }

    return head;
}
#endif // Q1_TPP