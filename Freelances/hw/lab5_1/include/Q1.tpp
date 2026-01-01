#ifndef Q1_TPP
#define Q1_TPP

// ============================================================================
// Q1: Convert BST to Sorted Circular Doubly Linked List (In-Place)
// ============================================================================
//

template <typename T>
void convertToDLLHelper(BSTNode<T> *root, BSTNode<T> *&head, BSTNode<T> *&prev)
{
    if (root == nullptr)
        return;

    convertToDLLHelper(root->left, head, prev);

    if (prev == nullptr)
        head = root;
    else
    {
        root->left = prev;
        prev->right = root;
    }
    prev = root;
    convertToDLLHelper(root->right, head, prev);
}

template <typename T>
BSTNode<T> *convertToCircularDLL(BST<T> &tree)
{
    BSTNode<T> *root = tree.getRoot();

    if (root == nullptr)
        return nullptr;

    BSTNode<T> *head = nullptr;
    BSTNode<T> *prev = nullptr;

    convertToDLLHelper(root, head, prev);

    if (head != nullptr && prev != nullptr)
    {
        head->left = prev;
        prev->right = head;
    }

    return head;
}
#endif // Q1_TPP

//