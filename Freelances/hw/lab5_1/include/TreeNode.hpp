#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <cstddef>

// ============================================================================
// BST NODE
// ============================================================================

/**
 * @brief Node structure for Binary Search Tree
 * @tparam T Data type stored in the node
 */
template <typename T> struct BSTNode {
  T data;
  BSTNode *left;
  BSTNode *right;
  BSTNode *parent;

  BSTNode(const T &value)
      : data(value), left(nullptr), right(nullptr), parent(nullptr) {}

  BSTNode(const T &value, BSTNode *p)
      : data(value), left(nullptr), right(nullptr), parent(p) {}
};

// ============================================================================
// AVL NODE
// ============================================================================

/**
 * @brief Node structure for AVL Tree (includes height for balance calculation)
 * @tparam T Data type stored in the node
 */
template <typename T> struct AVLNode {
  T data;
  AVLNode *left;
  AVLNode *right;
  AVLNode *parent;
  int height;

  AVLNode(const T &value)
      : data(value), left(nullptr), right(nullptr), parent(nullptr), height(1) {
  }

  AVLNode(const T &value, AVLNode *p)
      : data(value), left(nullptr), right(nullptr), parent(p), height(1) {}
};

// ============================================================================
// 2-3-4 TREE NODE
// ============================================================================

/**
 * @brief Node structure for 2-3-4 Tree
 *
 * A 2-3-4 tree node can have:
 * - 1 key and 2 children (2-node)
 * - 2 keys and 3 children (3-node)
 * - 3 keys and 4 children (4-node)
 *
 * @tparam T Data type stored in the node
 */
template <typename T> struct Node234 {
  T keys[3];            // Maximum 3 keys
  Node234 *children[4]; // Maximum 4 children
  Node234 *parent;
  size_t keyCount; // Number of keys (1, 2, or 3)

  Node234() : parent(nullptr), keyCount(0) {
    for (int i = 0; i < 4; ++i) {
      children[i] = nullptr;
    }
  }

  Node234(const T &value) : parent(nullptr), keyCount(1) {
    keys[0] = value;
    for (int i = 0; i < 4; ++i) {
      children[i] = nullptr;
    }
  }

  Node234(const T &value, Node234 *p) : parent(p), keyCount(1) {
    keys[0] = value;
    for (int i = 0; i < 4; ++i) {
      children[i] = nullptr;
    }
  }

  /**
   * @brief Check if this is a leaf node (no children)
   */
  bool isLeaf() const { return children[0] == nullptr; }

  /**
   * @brief Check if this node is full (has 3 keys)
   */
  bool isFull() const { return keyCount == 3; }

  /**
   * @brief Get the type of node (2-node, 3-node, or 4-node)
   */
  int getNodeType() const { return static_cast<int>(keyCount) + 1; }
};

#endif // TREE_NODE_HPP
