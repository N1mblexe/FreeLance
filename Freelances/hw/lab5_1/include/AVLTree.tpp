#ifndef AVL_TREE_TPP
#define AVL_TREE_TPP

// ============================================================================
// PRIVATE HELPER FUNCTIONS
// ============================================================================

template <typename T>
AVLNode<T> *AVLTree<T>::copySubtree(AVLNode<T> *node, AVLNode<T> *parent) {
  if (node == nullptr) {
    return nullptr;
  }

  AVLNode<T> *newNode = new AVLNode<T>(node->data, parent);
  newNode->height = node->height;
  newNode->left = copySubtree(node->left, newNode);
  newNode->right = copySubtree(node->right, newNode);
  return newNode;
}

template <typename T> void AVLTree<T>::clearSubtree(AVLNode<T> *node) {
  if (node == nullptr) {
    return;
  }

  clearSubtree(node->left);
  clearSubtree(node->right);
  delete node;
}

template <typename T> int AVLTree<T>::getHeight(AVLNode<T> *node) const {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

template <typename T> void AVLTree<T>::updateHeight(AVLNode<T> *node) {
  if (node == nullptr) {
    return;
  }

  int leftHeight = getHeight(node->left);
  int rightHeight = getHeight(node->right);
  node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <typename T> int AVLTree<T>::getBalance(AVLNode<T> *node) const {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

template <typename T> AVLNode<T> *AVLTree<T>::rotateRight(AVLNode<T> *y) {
  AVLNode<T> *x = y->left;
  AVLNode<T> *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update parents
  x->parent = y->parent;
  y->parent = x;
  if (T2 != nullptr) {
    T2->parent = y;
  }

  // Update heights
  updateHeight(y);
  updateHeight(x);

  return x;
}

template <typename T> AVLNode<T> *AVLTree<T>::rotateLeft(AVLNode<T> *x) {
  AVLNode<T> *y = x->right;
  AVLNode<T> *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update parents
  y->parent = x->parent;
  x->parent = y;
  if (T2 != nullptr) {
    T2->parent = x;
  }

  // Update heights
  updateHeight(x);
  updateHeight(y);

  return y;
}

template <typename T> AVLNode<T> *AVLTree<T>::balance(AVLNode<T> *node) {
  if (node == nullptr) {
    return nullptr;
  }

  updateHeight(node);

  int balanceFactor = getBalance(node);

  // Left heavy
  if (balanceFactor > 1) {
    // Left-Right case
    if (getBalance(node->left) < 0) {
      node->left = rotateLeft(node->left);
    }
    // Left-Left case
    return rotateRight(node);
  }

  // Right heavy
  if (balanceFactor < -1) {
    // Right-Left case
    if (getBalance(node->right) > 0) {
      node->right = rotateRight(node->right);
    }
    // Right-Right case
    return rotateLeft(node);
  }

  return node;
}

template <typename T>
AVLNode<T> *AVLTree<T>::insertHelper(AVLNode<T> *node, AVLNode<T> *parent,
                                     const T &value, bool &inserted) {
  if (node == nullptr) {
    inserted = true;
    nodeCount_++;
    return new AVLNode<T>(value, parent);
  }

  if (value < node->data) {
    node->left = insertHelper(node->left, node, value, inserted);
  } else if (value > node->data) {
    node->right = insertHelper(node->right, node, value, inserted);
  } else {
    // Duplicate value
    inserted = false;
    return node;
  }

  return balance(node);
}

template <typename T>
AVLNode<T> *AVLTree<T>::removeHelper(AVLNode<T> *node, const T &value,
                                     bool &removed) {
  if (node == nullptr) {
    removed = false;
    return nullptr;
  }

  if (value < node->data) {
    node->left = removeHelper(node->left, value, removed);
  } else if (value > node->data) {
    node->right = removeHelper(node->right, value, removed);
  } else {
    // Found node to delete
    removed = true;

    // Node with one or no child
    if (node->left == nullptr || node->right == nullptr) {
      AVLNode<T> *temp = node->left ? node->left : node->right;

      if (temp == nullptr) {
        // No child
        delete node;
        nodeCount_--;
        return nullptr;
      } else {
        // One child
        temp->parent = node->parent;
        delete node;
        nodeCount_--;
        return temp;
      }
    } else {
      // Node with two children
      AVLNode<T> *successor = findMin(node->right);
      node->data = successor->data;
      node->right = removeHelper(node->right, successor->data, removed);
      // Note: removed is already true, nodeCount decremented in recursive call
    }
  }

  return balance(node);
}

template <typename T> AVLNode<T> *AVLTree<T>::findMin(AVLNode<T> *node) const {
  if (node == nullptr) {
    return nullptr;
  }

  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename T>
void AVLTree<T>::inorderHelper(AVLNode<T> *node, T *result,
                               size_t &index) const {
  if (node == nullptr) {
    return;
  }

  inorderHelper(node->left, result, index);
  result[index++] = node->data;
  inorderHelper(node->right, result, index);
}

template <typename T>
void AVLTree<T>::preorderHelper(AVLNode<T> *node, T *result,
                                size_t &index) const {
  if (node == nullptr) {
    return;
  }

  result[index++] = node->data;
  preorderHelper(node->left, result, index);
  preorderHelper(node->right, result, index);
}

template <typename T>
void AVLTree<T>::postorderHelper(AVLNode<T> *node, T *result,
                                 size_t &index) const {
  if (node == nullptr) {
    return;
  }

  postorderHelper(node->left, result, index);
  postorderHelper(node->right, result, index);
  result[index++] = node->data;
}

template <typename T>
void AVLTree<T>::printHelper(AVLNode<T> *node, const std::string &prefix,
                             bool isLeft) const {
  if (node == nullptr) {
    return;
  }

  std::cout << prefix;
  std::cout << (isLeft ? "|-- " : "\\-- ");
  std::cout << Color::INFO << node->data << Color::RESET;
  std::cout << Color::DEBUG_COLOR << " (h=" << node->height
            << ", bf=" << getBalance(node) << ")" << Color::RESET << std::endl;

  printHelper(node->left, prefix + (isLeft ? "|   " : "    "), true);
  printHelper(node->right, prefix + (isLeft ? "|   " : "    "), false);
}

template <typename T>
void AVLTree<T>::toJsonHelper(AVLNode<T> *node, json &j) const {
  if (node == nullptr) {
    j = nullptr;
    return;
  }

  j["data"] = node->data;
  j["height"] = node->height;
  j["balance"] = getBalance(node);

  if (node->left != nullptr) {
    toJsonHelper(node->left, j["left"]);
  }

  if (node->right != nullptr) {
    toJsonHelper(node->right, j["right"]);
  }
}

// ============================================================================
// CONSTRUCTORS & DESTRUCTOR
// ============================================================================

template <typename T> AVLTree<T>::AVLTree() : root_(nullptr), nodeCount_(0) {}

template <typename T> AVLTree<T>::~AVLTree() { clear(); }

template <typename T>
AVLTree<T>::AVLTree(const AVLTree &other)
    : root_(nullptr), nodeCount_(other.nodeCount_) {
  root_ = copySubtree(other.root_, nullptr);
}

template <typename T>
AVLTree<T>::AVLTree(AVLTree &&other) noexcept
    : root_(other.root_), nodeCount_(other.nodeCount_) {
  other.root_ = nullptr;
  other.nodeCount_ = 0;
}

template <typename T> AVLTree<T> &AVLTree<T>::operator=(const AVLTree &other) {
  if (this != &other) {
    clear();
    nodeCount_ = other.nodeCount_;
    root_ = copySubtree(other.root_, nullptr);
  }
  return *this;
}

template <typename T>
AVLTree<T> &AVLTree<T>::operator=(AVLTree &&other) noexcept {
  if (this != &other) {
    clear();
    root_ = other.root_;
    nodeCount_ = other.nodeCount_;
    other.root_ = nullptr;
    other.nodeCount_ = 0;
  }
  return *this;
}

// ============================================================================
// CORE OPERATIONS
// ============================================================================

template <typename T> bool AVLTree<T>::insert(const T &value) {
  bool inserted = false;
  root_ = insertHelper(root_, nullptr, value, inserted);

  if (!inserted) {
    std::cout << Color::WARNING << "Warning: Duplicate value " << value
              << " not inserted" << Color::RESET << std::endl;
  }

  return inserted;
}

template <typename T> bool AVLTree<T>::remove(const T &value) {
  bool removed = false;
  root_ = removeHelper(root_, value, removed);

  if (!removed) {
    std::cout << Color::ERROR << "Error: Value " << value << " not found"
              << Color::RESET << std::endl;
  }

  return removed;
}

template <typename T> bool AVLTree<T>::search(const T &value) const {
  AVLNode<T> *current = root_;

  while (current != nullptr) {
    if (value < current->data) {
      current = current->left;
    } else if (value > current->data) {
      current = current->right;
    } else {
      return true;
    }
  }

  return false;
}

template <typename T> void AVLTree<T>::clear() {
  clearSubtree(root_);
  root_ = nullptr;
  nodeCount_ = 0;
}

template <typename T> bool AVLTree<T>::isEmpty() const {
  return root_ == nullptr;
}

template <typename T> size_t AVLTree<T>::nodeCount() const {
  return nodeCount_;
}

template <typename T> size_t AVLTree<T>::height() const {
  return static_cast<size_t>(getHeight(root_));
}

// ============================================================================
// ACCESSOR METHODS
// ============================================================================

template <typename T> AVLNode<T> *AVLTree<T>::getRoot() const { return root_; }

// ============================================================================
// TRAVERSALS
// ============================================================================

template <typename T> T *AVLTree<T>::inorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  inorderHelper(root_, result, index);
  return result;
}

template <typename T> T *AVLTree<T>::preorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  preorderHelper(root_, result, index);
  return result;
}

template <typename T> T *AVLTree<T>::postorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  postorderHelper(root_, result, index);
  return result;
}

template <typename T> T *AVLTree<T>::levelorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];

  // Manual queue implementation using array
  AVLNode<T> **queue = new AVLNode<T> *[count];
  size_t front = 0;
  size_t rear = 0;
  size_t index = 0;

  queue[rear++] = root_;

  while (front < rear) {
    AVLNode<T> *current = queue[front++];
    result[index++] = current->data;

    if (current->left != nullptr) {
      queue[rear++] = current->left;
    }
    if (current->right != nullptr) {
      queue[rear++] = current->right;
    }
  }

  delete[] queue;
  return result;
}

// ============================================================================
// PRINT OPERATIONS
// ============================================================================

template <typename T> void AVLTree<T>::print() const {
  std::cout << Color::HEADER << "=== AVL Tree Structure ===" << Color::RESET
            << std::endl;

  if (root_ == nullptr) {
    std::cout << Color::WARNING << "(empty tree)" << Color::RESET << std::endl;
    return;
  }

  printHelper(root_, "", false);

  std::cout << Color::DEBUG_COLOR << "Nodes: " << nodeCount_
            << ", Height: " << height() << Color::RESET << std::endl;
}

template <typename T> void AVLTree<T>::printInorder() const {
  std::cout << Color::HEADER << "Inorder: " << Color::RESET;

  size_t count;
  T *result = inorderTraversal(count);

  if (result == nullptr) {
    std::cout << Color::WARNING << "(empty)" << Color::RESET << std::endl;
    return;
  }

  for (size_t i = 0; i < count; ++i) {
    std::cout << result[i];
    if (i < count - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;

  delete[] result;
}

// ============================================================================
// JSON OPERATIONS
// ============================================================================

template <typename T> json AVLTree<T>::toJson(const char *name) const {
  json j;
  j["name"] = name;
  j["type"] = "AVLTree";
  j["nodeCount"] = nodeCount_;
  j["height"] = height();

  if (root_ != nullptr) {
    toJsonHelper(root_, j["root"]);
  } else {
    j["root"] = nullptr;
  }

  // Also include traversals
  size_t count;
  T *inorder = inorderTraversal(count);
  if (inorder != nullptr) {
    j["inorder"] = json::array();
    for (size_t i = 0; i < count; ++i) {
      j["inorder"].push_back(inorder[i]);
    }
    delete[] inorder;
  }

  return j;
}

template <typename T> bool AVLTree<T>::loadFromJson(const json &j) {
  try {
    clear();

    if (!j.contains("inorder") || j["inorder"].is_null()) {
      return true; // Empty tree
    }

    // Insert values from inorder array
    for (const auto &val : j["inorder"]) {
      insert(val.get<T>());
    }

    return true;
  } catch (const std::exception &e) {
    std::cout << Color::ERROR << "Error loading JSON: " << e.what()
              << Color::RESET << std::endl;
    return false;
  }
}

template <typename T> bool AVLTree<T>::loadFromFile(const char *filename) {
  try {
    std::ifstream file(filename);

    if (!file.is_open()) {
      std::cout << Color::ERROR << "Error: Cannot open file " << filename
                << Color::RESET << std::endl;
      return false;
    }

    json j;
    file >> j;
    file.close();

    return loadFromJson(j);
  } catch (const std::exception &e) {
    std::cout << Color::ERROR << "Error loading file: " << e.what()
              << Color::RESET << std::endl;
    return false;
  }
}

template <typename T>
bool AVLTree<T>::saveToFile(const char *filename, const char *name) const {
  try {
    std::ofstream file(filename);

    if (!file.is_open()) {
      std::cout << Color::ERROR << "Error: Cannot create file " << filename
                << Color::RESET << std::endl;
      return false;
    }

    json j = toJson(name);
    file << std::setw(2) << j << std::endl;
    file.close();

    std::cout << Color::SUCCESS << "Tree saved to " << filename << Color::RESET
              << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cout << Color::ERROR << "Error saving file: " << e.what()
              << Color::RESET << std::endl;
    return false;
  }
}

#endif // AVL_TREE_TPP
