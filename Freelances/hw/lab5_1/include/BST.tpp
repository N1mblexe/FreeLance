#ifndef BST_TPP
#define BST_TPP

// ============================================================================
// PROTECTED HELPER FUNCTIONS
// ============================================================================

template <typename T>
BSTNode<T> *BST<T>::copySubtree(BSTNode<T> *node, BSTNode<T> *parent) {
  if (node == nullptr) {
    return nullptr;
  }

  BSTNode<T> *newNode = new BSTNode<T>(node->data, parent);
  newNode->left = copySubtree(node->left, newNode);
  newNode->right = copySubtree(node->right, newNode);
  return newNode;
}

template <typename T> void BST<T>::clearSubtree(BSTNode<T> *node) {
  if (node == nullptr) {
    return;
  }

  clearSubtree(node->left);
  clearSubtree(node->right);
  delete node;
}

template <typename T> BSTNode<T> *BST<T>::findMin(BSTNode<T> *node) const {
  if (node == nullptr) {
    return nullptr;
  }

  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename T> BSTNode<T> *BST<T>::findMax(BSTNode<T> *node) const {
  if (node == nullptr) {
    return nullptr;
  }

  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

template <typename T> size_t BST<T>::heightHelper(BSTNode<T> *node) const {
  if (node == nullptr) {
    return 0;
  }

  size_t leftHeight = heightHelper(node->left);
  size_t rightHeight = heightHelper(node->right);

  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <typename T>
void BST<T>::inorderHelper(BSTNode<T> *node, T *result, size_t &index) const {
  if (node == nullptr) {
    return;
  }

  inorderHelper(node->left, result, index);
  result[index++] = node->data;
  inorderHelper(node->right, result, index);
}

template <typename T>
void BST<T>::preorderHelper(BSTNode<T> *node, T *result, size_t &index) const {
  if (node == nullptr) {
    return;
  }

  result[index++] = node->data;
  preorderHelper(node->left, result, index);
  preorderHelper(node->right, result, index);
}

template <typename T>
void BST<T>::postorderHelper(BSTNode<T> *node, T *result, size_t &index) const {
  if (node == nullptr) {
    return;
  }

  postorderHelper(node->left, result, index);
  postorderHelper(node->right, result, index);
  result[index++] = node->data;
}

template <typename T>
void BST<T>::printHelper(BSTNode<T> *node, const std::string &prefix,
                         bool isLeft) const {
  if (node == nullptr) {
    return;
  }

  std::cout << prefix;
  std::cout << (isLeft ? "|-- " : "\\-- ");
  std::cout << Color::INFO << node->data << Color::RESET << std::endl;

  printHelper(node->left, prefix + (isLeft ? "|   " : "    "), true);
  printHelper(node->right, prefix + (isLeft ? "|   " : "    "), false);
}

template <typename T>
void BST<T>::toJsonHelper(BSTNode<T> *node, json &j) const {
  if (node == nullptr) {
    j = nullptr;
    return;
  }

  j["data"] = node->data;

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

template <typename T> BST<T>::BST() : root_(nullptr), nodeCount_(0) {}

template <typename T> BST<T>::~BST() { clear(); }

template <typename T>
BST<T>::BST(const BST &other) : root_(nullptr), nodeCount_(other.nodeCount_) {
  root_ = copySubtree(other.root_, nullptr);
}

template <typename T>
BST<T>::BST(BST &&other) noexcept
    : root_(other.root_), nodeCount_(other.nodeCount_) {
  other.root_ = nullptr;
  other.nodeCount_ = 0;
}

template <typename T> BST<T> &BST<T>::operator=(const BST &other) {
  if (this != &other) {
    clear();
    nodeCount_ = other.nodeCount_;
    root_ = copySubtree(other.root_, nullptr);
  }
  return *this;
}

template <typename T> BST<T> &BST<T>::operator=(BST &&other) noexcept {
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

template <typename T> bool BST<T>::insert(const T &value) {
  if (root_ == nullptr) {
    root_ = new BSTNode<T>(value);
    nodeCount_++;
    return true;
  }

  BSTNode<T> *current = root_;
  BSTNode<T> *parent = nullptr;

  while (current != nullptr) {
    parent = current;

    if (value < current->data) {
      current = current->left;
    } else if (value > current->data) {
      current = current->right;
    } else {
      // Duplicate value
      std::cout << Color::WARNING << "Warning: Duplicate value " << value
                << " not inserted" << Color::RESET << std::endl;
      return false;
    }
  }

  BSTNode<T> *newNode = new BSTNode<T>(value, parent);

  if (value < parent->data) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  nodeCount_++;
  return true;
}

template <typename T> bool BST<T>::remove(const T &value) {
  BSTNode<T> *current = root_;

  // Find the node to remove
  while (current != nullptr && current->data != value) {
    if (value < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  if (current == nullptr) {
    std::cout << Color::ERROR << "Error: Value " << value << " not found"
              << Color::RESET << std::endl;
    return false;
  }

  // Case 1: Node has no children (leaf)
  if (current->left == nullptr && current->right == nullptr) {
    if (current == root_) {
      root_ = nullptr;
    } else if (current->parent->left == current) {
      current->parent->left = nullptr;
    } else {
      current->parent->right = nullptr;
    }
    delete current;
  }
  // Case 2: Node has one child
  else if (current->left == nullptr || current->right == nullptr) {
    BSTNode<T> *child =
        (current->left != nullptr) ? current->left : current->right;
    child->parent = current->parent;

    if (current == root_) {
      root_ = child;
    } else if (current->parent->left == current) {
      current->parent->left = child;
    } else {
      current->parent->right = child;
    }
    delete current;
  }
  // Case 3: Node has two children
  else {
    // Find inorder successor (minimum in right subtree)
    BSTNode<T> *successor = findMin(current->right);
    T successorData = successor->data;

    // Remove the successor (it has at most one child)
    remove(successorData);

    // Replace current's data with successor's data
    current->data = successorData;

    // nodeCount was already decremented in recursive call
    return true;
  }

  nodeCount_--;
  return true;
}

template <typename T> bool BST<T>::search(const T &value) const {
  BSTNode<T> *current = root_;

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

template <typename T> void BST<T>::clear() {
  clearSubtree(root_);
  root_ = nullptr;
  nodeCount_ = 0;
}

template <typename T> bool BST<T>::isEmpty() const { return root_ == nullptr; }

template <typename T> size_t BST<T>::nodeCount() const { return nodeCount_; }

template <typename T> size_t BST<T>::height() const {
  return heightHelper(root_);
}

// ============================================================================
// ACCESSOR METHODS
// ============================================================================

template <typename T> BSTNode<T> *BST<T>::getRoot() const { return root_; }

// ============================================================================
// TRAVERSALS
// ============================================================================

template <typename T> T *BST<T>::inorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  inorderHelper(root_, result, index);
  return result;
}

template <typename T> T *BST<T>::preorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  preorderHelper(root_, result, index);
  return result;
}

template <typename T> T *BST<T>::postorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  postorderHelper(root_, result, index);
  return result;
}

template <typename T> T *BST<T>::levelorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];

  // Manual queue implementation using array
  BSTNode<T> **queue = new BSTNode<T> *[count];
  size_t front = 0;
  size_t rear = 0;
  size_t index = 0;

  queue[rear++] = root_;

  while (front < rear) {
    BSTNode<T> *current = queue[front++];
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

template <typename T> void BST<T>::print() const {
  std::cout << Color::HEADER << "=== BST Structure ===" << Color::RESET
            << std::endl;

  if (root_ == nullptr) {
    std::cout << Color::WARNING << "(empty tree)" << Color::RESET << std::endl;
    return;
  }

  printHelper(root_, "", false);

  std::cout << Color::DEBUG_COLOR << "Nodes: " << nodeCount_
            << ", Height: " << height() << Color::RESET << std::endl;
}

template <typename T> void BST<T>::printInorder() const {
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

template <typename T> json BST<T>::toJson(const char *name) const {
  json j;
  j["name"] = name;
  j["type"] = "BST";
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

template <typename T> bool BST<T>::loadFromJson(const json &j) {
  try {
    clear();

    if (!j.contains("inorder") || j["inorder"].is_null()) {
      return true; // Empty tree
    }

    // Insert values from inorder array
    // Note: This doesn't preserve original structure, just values
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

template <typename T> bool BST<T>::loadFromFile(const char *filename) {
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
bool BST<T>::saveToFile(const char *filename, const char *name) const {
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

#endif // BST_TPP
