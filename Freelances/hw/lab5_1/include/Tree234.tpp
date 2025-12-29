#ifndef TREE234_TPP
#define TREE234_TPP

// ============================================================================
// PRIVATE HELPER FUNCTIONS
// ============================================================================

template <typename T>
Node234<T> *Tree234<T>::copySubtree(Node234<T> *node, Node234<T> *parent) {
  if (node == nullptr) {
    return nullptr;
  }

  Node234<T> *newNode = new Node234<T>();
  newNode->parent = parent;
  newNode->keyCount = node->keyCount;

  // Copy keys
  for (size_t i = 0; i < node->keyCount; ++i) {
    newNode->keys[i] = node->keys[i];
  }

  // Copy children recursively
  for (size_t i = 0; i <= node->keyCount; ++i) {
    newNode->children[i] = copySubtree(node->children[i], newNode);
  }

  return newNode;
}

template <typename T> void Tree234<T>::clearSubtree(Node234<T> *node) {
  if (node == nullptr) {
    return;
  }

  // Clear all children
  for (size_t i = 0; i <= node->keyCount; ++i) {
    clearSubtree(node->children[i]);
  }

  delete node;
}

template <typename T>
int Tree234<T>::findChildIndex(Node234<T> *node, const T &value) const {
  int i = 0;
  while (i < static_cast<int>(node->keyCount) && value > node->keys[i]) {
    ++i;
  }
  return i;
}

template <typename T>
void Tree234<T>::insertKey(Node234<T> *node, const T &value) {
  int i = static_cast<int>(node->keyCount) - 1;

  // Shift keys to make room
  while (i >= 0 && value < node->keys[i]) {
    node->keys[i + 1] = node->keys[i];
    --i;
  }

  node->keys[i + 1] = value;
  node->keyCount++;
}

template <typename T> void Tree234<T>::split(Node234<T> *node) {
  // Node must be a 4-node (3 keys)
  if (node->keyCount != 3) {
    return;
  }

  // Create two new nodes for left and right
  Node234<T> *left = new Node234<T>(node->keys[0]);
  Node234<T> *right = new Node234<T>(node->keys[2]);

  // If not a leaf, distribute children
  if (!node->isLeaf()) {
    left->children[0] = node->children[0];
    left->children[1] = node->children[1];
    right->children[0] = node->children[2];
    right->children[1] = node->children[3];

    // Update parent pointers
    if (left->children[0])
      left->children[0]->parent = left;
    if (left->children[1])
      left->children[1]->parent = left;
    if (right->children[0])
      right->children[0]->parent = right;
    if (right->children[1])
      right->children[1]->parent = right;
  }

  T middleKey = node->keys[1];

  if (node->parent == nullptr) {
    // Node is root - create new root
    Node234<T> *newRoot = new Node234<T>(middleKey);
    newRoot->children[0] = left;
    newRoot->children[1] = right;
    left->parent = newRoot;
    right->parent = newRoot;
    root_ = newRoot;
    delete node;
  } else {
    // Insert middle key into parent
    Node234<T> *parent = node->parent;
    left->parent = parent;
    right->parent = parent;

    // Find where to insert in parent
    int i = findChildIndex(parent, middleKey);

    // Shift keys and children in parent
    for (int j = static_cast<int>(parent->keyCount); j > i; --j) {
      parent->keys[j] = parent->keys[j - 1];
      parent->children[j + 1] = parent->children[j];
    }

    parent->keys[i] = middleKey;
    parent->children[i] = left;
    parent->children[i + 1] = right;
    parent->keyCount++;

    delete node;
  }
}

template <typename T>
void Tree234<T>::insertNonFull(Node234<T> *node, const T &value) {
  if (node->isLeaf()) {
    // Insert key in sorted order
    insertKey(node, value);
    nodeCount_++;
  } else {
    // Find appropriate child
    int i = findChildIndex(node, value);

    // Check for duplicate
    if (i < static_cast<int>(node->keyCount) && node->keys[i] == value) {
      std::cout << Color::WARNING << "Warning: Duplicate value " << value
                << " not inserted" << Color::RESET << std::endl;
      return;
    }

    // Split child if it's a 4-node
    if (node->children[i]->isFull()) {
      split(node->children[i]);
      // After split, we need to decide which child to descend into
      if (value > node->keys[i]) {
        ++i;
      }
    }

    insertNonFull(node->children[i], value);
  }
}

template <typename T>
bool Tree234<T>::searchHelper(Node234<T> *node, const T &value) const {
  if (node == nullptr) {
    return false;
  }

  // Check keys in this node
  for (size_t i = 0; i < node->keyCount; ++i) {
    if (node->keys[i] == value) {
      return true;
    }
  }

  // If leaf, value not found
  if (node->isLeaf()) {
    return false;
  }

  // Find appropriate child
  int i = findChildIndex(node, value);
  return searchHelper(node->children[i], value);
}

template <typename T> size_t Tree234<T>::heightHelper(Node234<T> *node) const {
  if (node == nullptr) {
    return 0;
  }

  // All paths in a 2-3-4 tree have the same height
  return 1 + heightHelper(node->children[0]);
}

template <typename T>
void Tree234<T>::inorderHelper(Node234<T> *node, T *result,
                               size_t &index) const {
  if (node == nullptr) {
    return;
  }

  for (size_t i = 0; i < node->keyCount; ++i) {
    inorderHelper(node->children[i], result, index);
    result[index++] = node->keys[i];
  }
  inorderHelper(node->children[node->keyCount], result, index);
}

template <typename T>
void Tree234<T>::preorderHelper(Node234<T> *node, T *result,
                                size_t &index) const {
  if (node == nullptr) {
    return;
  }

  // First, add all keys in this node
  for (size_t i = 0; i < node->keyCount; ++i) {
    result[index++] = node->keys[i];
  }

  // Then traverse children
  for (size_t i = 0; i <= node->keyCount; ++i) {
    preorderHelper(node->children[i], result, index);
  }
}

template <typename T>
void Tree234<T>::postorderHelper(Node234<T> *node, T *result,
                                 size_t &index) const {
  if (node == nullptr) {
    return;
  }

  // First traverse children
  for (size_t i = 0; i <= node->keyCount; ++i) {
    postorderHelper(node->children[i], result, index);
  }

  // Then add all keys in this node
  for (size_t i = 0; i < node->keyCount; ++i) {
    result[index++] = node->keys[i];
  }
}

template <typename T>
void Tree234<T>::printHelper(Node234<T> *node, const std::string &prefix,
                             bool isLast) const {
  if (node == nullptr) {
    return;
  }

  std::cout << prefix;
  std::cout << (isLast ? "\\-- " : "|-- ");

  // Print node type and keys
  std::cout << Color::DEBUG_COLOR << "[" << node->getNodeType() << "-node] "
            << Color::RESET;

  std::cout << Color::INFO << "[";
  for (size_t i = 0; i < node->keyCount; ++i) {
    std::cout << node->keys[i];
    if (i < node->keyCount - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << Color::RESET << std::endl;

  // Print children
  std::string newPrefix = prefix + (isLast ? "    " : "|   ");
  for (size_t i = 0; i <= node->keyCount; ++i) {
    if (node->children[i] != nullptr) {
      printHelper(node->children[i], newPrefix, i == node->keyCount);
    }
  }
}

template <typename T>
void Tree234<T>::toJsonHelper(Node234<T> *node, json &j) const {
  if (node == nullptr) {
    j = nullptr;
    return;
  }

  j["nodeType"] = node->getNodeType();
  j["keys"] = json::array();
  for (size_t i = 0; i < node->keyCount; ++i) {
    j["keys"].push_back(node->keys[i]);
  }

  if (!node->isLeaf()) {
    j["children"] = json::array();
    for (size_t i = 0; i <= node->keyCount; ++i) {
      json child;
      toJsonHelper(node->children[i], child);
      j["children"].push_back(child);
    }
  }
}

template <typename T> size_t Tree234<T>::countNodes(Node234<T> *node) const {
  if (node == nullptr) {
    return 0;
  }

  size_t count = 1; // Count this node
  for (size_t i = 0; i <= node->keyCount; ++i) {
    count += countNodes(node->children[i]);
  }
  return count;
}

// ============================================================================
// DELETION HELPERS
// ============================================================================

template <typename T>
T Tree234<T>::getPredecessor(Node234<T> *node, int keyIndex) {
  Node234<T> *current = node->children[keyIndex];
  while (!current->isLeaf()) {
    current = current->children[current->keyCount];
  }
  return current->keys[current->keyCount - 1];
}

template <typename T>
T Tree234<T>::getSuccessor(Node234<T> *node, int keyIndex) {
  Node234<T> *current = node->children[keyIndex + 1];
  while (!current->isLeaf()) {
    current = current->children[0];
  }
  return current->keys[0];
}

template <typename T> void Tree234<T>::merge(Node234<T> *node, int keyIndex) {
  Node234<T> *leftChild = node->children[keyIndex];
  Node234<T> *rightChild = node->children[keyIndex + 1];

  // Move key from parent to left child
  leftChild->keys[leftChild->keyCount] = node->keys[keyIndex];
  leftChild->keyCount++;

  // Move keys from right child to left child
  for (size_t i = 0; i < rightChild->keyCount; ++i) {
    leftChild->keys[leftChild->keyCount] = rightChild->keys[i];
    leftChild->keyCount++;
  }

  // Move children from right to left
  if (!leftChild->isLeaf()) {
    for (size_t i = 0; i <= rightChild->keyCount; ++i) {
      leftChild->children[leftChild->keyCount - rightChild->keyCount + i] =
          rightChild->children[i];
      if (rightChild->children[i]) {
        rightChild->children[i]->parent = leftChild;
      }
    }
  }

  // Shift keys and children in parent
  for (int i = keyIndex; i < static_cast<int>(node->keyCount) - 1; ++i) {
    node->keys[i] = node->keys[i + 1];
    node->children[i + 1] = node->children[i + 2];
  }
  node->keyCount--;

  delete rightChild;

  // If root becomes empty
  if (node == root_ && node->keyCount == 0) {
    root_ = leftChild;
    leftChild->parent = nullptr;
    delete node;
  }
}

template <typename T>
void Tree234<T>::borrowFromLeft(Node234<T> *node, int childIndex) {
  Node234<T> *child = node->children[childIndex];
  Node234<T> *leftSibling = node->children[childIndex - 1];

  // Shift keys in child to make room
  for (int i = static_cast<int>(child->keyCount); i > 0; --i) {
    child->keys[i] = child->keys[i - 1];
  }

  // Shift children if not leaf
  if (!child->isLeaf()) {
    for (int i = static_cast<int>(child->keyCount) + 1; i > 0; --i) {
      child->children[i] = child->children[i - 1];
    }
    child->children[0] = leftSibling->children[leftSibling->keyCount];
    if (child->children[0]) {
      child->children[0]->parent = child;
    }
  }

  // Move key from parent to child
  child->keys[0] = node->keys[childIndex - 1];
  child->keyCount++;

  // Move key from sibling to parent
  node->keys[childIndex - 1] = leftSibling->keys[leftSibling->keyCount - 1];
  leftSibling->keyCount--;
}

template <typename T>
void Tree234<T>::borrowFromRight(Node234<T> *node, int childIndex) {
  Node234<T> *child = node->children[childIndex];
  Node234<T> *rightSibling = node->children[childIndex + 1];

  // Move key from parent to child
  child->keys[child->keyCount] = node->keys[childIndex];
  child->keyCount++;

  // Move first child of right sibling if not leaf
  if (!child->isLeaf()) {
    child->children[child->keyCount] = rightSibling->children[0];
    if (child->children[child->keyCount]) {
      child->children[child->keyCount]->parent = child;
    }
  }

  // Move key from sibling to parent
  node->keys[childIndex] = rightSibling->keys[0];

  // Shift keys and children in right sibling
  for (size_t i = 0; i < rightSibling->keyCount - 1; ++i) {
    rightSibling->keys[i] = rightSibling->keys[i + 1];
  }
  if (!rightSibling->isLeaf()) {
    for (size_t i = 0; i < rightSibling->keyCount; ++i) {
      rightSibling->children[i] = rightSibling->children[i + 1];
    }
  }
  rightSibling->keyCount--;
}

template <typename T> void Tree234<T>::fill(Node234<T> *node, int childIndex) {
  // Try to borrow from left sibling
  if (childIndex > 0 && node->children[childIndex - 1]->keyCount > 1) {
    borrowFromLeft(node, childIndex);
  }
  // Try to borrow from right sibling
  else if (childIndex < static_cast<int>(node->keyCount) &&
           node->children[childIndex + 1]->keyCount > 1) {
    borrowFromRight(node, childIndex);
  }
  // Merge with a sibling
  else {
    if (childIndex < static_cast<int>(node->keyCount)) {
      merge(node, childIndex);
    } else {
      merge(node, childIndex - 1);
    }
  }
}

template <typename T>
bool Tree234<T>::removeHelper(Node234<T> *node, const T &value) {
  if (node == nullptr) {
    return false;
  }

  int i = 0;
  while (i < static_cast<int>(node->keyCount) && value > node->keys[i]) {
    ++i;
  }

  // Found key in this node
  if (i < static_cast<int>(node->keyCount) && node->keys[i] == value) {
    if (node->isLeaf()) {
      // Remove from leaf
      for (int j = i; j < static_cast<int>(node->keyCount) - 1; ++j) {
        node->keys[j] = node->keys[j + 1];
      }
      node->keyCount--;
      nodeCount_--;
      return true;
    } else {
      // Internal node - replace with predecessor or successor
      if (node->children[i]->keyCount > 1) {
        T pred = getPredecessor(node, i);
        node->keys[i] = pred;
        return removeHelper(node->children[i], pred);
      } else if (node->children[i + 1]->keyCount > 1) {
        T succ = getSuccessor(node, i);
        node->keys[i] = succ;
        return removeHelper(node->children[i + 1], succ);
      } else {
        merge(node, i);
        return removeHelper(node->children[i], value);
      }
    }
  } else {
    // Key not in this node
    if (node->isLeaf()) {
      return false;
    }

    bool isLast = (i == static_cast<int>(node->keyCount));

    // Ensure child has at least 2 keys
    if (node->children[i]->keyCount == 1) {
      fill(node, i);
    }

    // After fill, the child might have changed
    if (isLast && i > static_cast<int>(node->keyCount)) {
      return removeHelper(node->children[i - 1], value);
    } else {
      return removeHelper(node->children[i], value);
    }
  }
}

// ============================================================================
// CONSTRUCTORS & DESTRUCTOR
// ============================================================================

template <typename T> Tree234<T>::Tree234() : root_(nullptr), nodeCount_(0) {}

template <typename T> Tree234<T>::~Tree234() { clear(); }

template <typename T>
Tree234<T>::Tree234(const Tree234 &other)
    : root_(nullptr), nodeCount_(other.nodeCount_) {
  root_ = copySubtree(other.root_, nullptr);
}

template <typename T>
Tree234<T>::Tree234(Tree234 &&other) noexcept
    : root_(other.root_), nodeCount_(other.nodeCount_) {
  other.root_ = nullptr;
  other.nodeCount_ = 0;
}

template <typename T> Tree234<T> &Tree234<T>::operator=(const Tree234 &other) {
  if (this != &other) {
    clear();
    nodeCount_ = other.nodeCount_;
    root_ = copySubtree(other.root_, nullptr);
  }
  return *this;
}

template <typename T>
Tree234<T> &Tree234<T>::operator=(Tree234 &&other) noexcept {
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

template <typename T> bool Tree234<T>::insert(const T &value) {
  // Check for duplicate
  if (search(value)) {
    std::cout << Color::WARNING << "Warning: Duplicate value " << value
              << " not inserted" << Color::RESET << std::endl;
    return false;
  }

  if (root_ == nullptr) {
    root_ = new Node234<T>(value);
    nodeCount_++;
    return true;
  }

  // If root is a 4-node, split it first
  if (root_->isFull()) {
    split(root_);
  }

  insertNonFull(root_, value);
  return true;
}

template <typename T> bool Tree234<T>::remove(const T &value) {
  if (root_ == nullptr) {
    std::cout << Color::ERROR << "Error: Tree is empty" << Color::RESET
              << std::endl;
    return false;
  }

  bool removed = removeHelper(root_, value);

  if (!removed) {
    std::cout << Color::ERROR << "Error: Value " << value << " not found"
              << Color::RESET << std::endl;
  }

  // Check if root became empty
  if (root_ != nullptr && root_->keyCount == 0) {
    Node234<T> *oldRoot = root_;
    root_ = root_->children[0];
    if (root_) {
      root_->parent = nullptr;
    }
    delete oldRoot;
  }

  return removed;
}

template <typename T> bool Tree234<T>::search(const T &value) const {
  return searchHelper(root_, value);
}

template <typename T> void Tree234<T>::clear() {
  clearSubtree(root_);
  root_ = nullptr;
  nodeCount_ = 0;
}

template <typename T> bool Tree234<T>::isEmpty() const {
  return root_ == nullptr;
}

template <typename T> size_t Tree234<T>::nodeCount() const {
  return nodeCount_;
}

template <typename T> size_t Tree234<T>::height() const {
  return heightHelper(root_);
}

// ============================================================================
// ACCESSOR METHODS
// ============================================================================

template <typename T> Node234<T> *Tree234<T>::getRoot() const { return root_; }

// ============================================================================
// TRAVERSALS
// ============================================================================

template <typename T> T *Tree234<T>::inorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  inorderHelper(root_, result, index);
  return result;
}

template <typename T> T *Tree234<T>::preorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  preorderHelper(root_, result, index);
  return result;
}

template <typename T> T *Tree234<T>::postorderTraversal(size_t &count) const {
  count = nodeCount_;

  if (count == 0) {
    return nullptr;
  }

  T *result = new T[count];
  size_t index = 0;
  postorderHelper(root_, result, index);
  return result;
}

// ============================================================================
// PRINT OPERATIONS
// ============================================================================

template <typename T> void Tree234<T>::print() const {
  std::cout << Color::HEADER << "=== 2-3-4 Tree Structure ===" << Color::RESET
            << std::endl;

  if (root_ == nullptr) {
    std::cout << Color::WARNING << "(empty tree)" << Color::RESET << std::endl;
    return;
  }

  printHelper(root_, "", true);

  std::cout << Color::DEBUG_COLOR << "Keys: " << nodeCount_
            << ", Height: " << height() << ", Nodes: " << countNodes(root_)
            << Color::RESET << std::endl;
}

template <typename T> void Tree234<T>::printInorder() const {
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

template <typename T> json Tree234<T>::toJson(const char *name) const {
  json j;
  j["name"] = name;
  j["type"] = "Tree234";
  j["keyCount"] = nodeCount_;
  j["height"] = height();
  j["nodeCount"] = countNodes(root_);

  if (root_ != nullptr) {
    toJsonHelper(root_, j["root"]);
  } else {
    j["root"] = nullptr;
  }

  // Include inorder traversal
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

template <typename T> bool Tree234<T>::loadFromJson(const json &j) {
  try {
    clear();

    if (!j.contains("inorder") || j["inorder"].is_null()) {
      return true;
    }

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

template <typename T> bool Tree234<T>::loadFromFile(const char *filename) {
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
bool Tree234<T>::saveToFile(const char *filename, const char *name) const {
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

#endif // TREE234_TPP
