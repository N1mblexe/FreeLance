#ifndef Q2_TPP
#define Q2_TPP

size_t RevertHeight(size_t currBase, size_t value, size_t maxHeight) {
  return maxHeight - (value - currBase);
}

template <typename T>
size_t InsertWithoutOptimization(AVLNode<T>*& root, AVLNode<T>* value) {
  if (root == nullptr) {
    root = value;
    return 1;
  }

  size_t val = 0;

  if (root->data > value->data)
    val = InsertWithoutOptimization<T>(root->left, value);
  else if (root->data < value->data)
    val = InsertWithoutOptimization<T>(root->right, value);

  return val + 1;
}

template <typename T>
AVLTree<T> *reconstructAVL(const T *preorder, const int *heights, size_t size) {
  
  AVLTree<T>* tree = new AVLTree<T>();
  AVLNode<T>* root = nullptr;

  for(size_t i = 0; i < size; i++) {
    AVLNode<T> *node = new AVLNode<T>(preorder[i]);
    size_t depth = InsertWithoutOptimization<T>(root, node);

    if (RevertHeight(1, depth, (size_t)heights[0]) != (size_t)heights[i]) {
        return nullptr;
    }
  }

  return tree;
}

#endif // Q2_TPP