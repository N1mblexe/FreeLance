#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Color.h"
#include "TreeNode.hpp"
#include "json.hpp"

using json = nlohmann::json;

/**
 * @brief Self-balancing AVL Tree implementation
 *
 * An AVL tree is a self-balancing binary search tree where the heights
 * of the two child subtrees of any node differ by at most one.
 *
 * @tparam T Data type stored in the tree (must support comparison operators)
 *
 * No STL containers - uses raw pointers and dynamic memory allocation
 */
template <typename T> class AVLTree {
private:
  AVLNode<T> *root_;
  size_t nodeCount_;

  // ========================================================================
  // PRIVATE HELPER FUNCTIONS
  // ========================================================================

  /**
   * @brief Recursively copy a subtree
   */
  AVLNode<T> *copySubtree(AVLNode<T> *node, AVLNode<T> *parent);

  /**
   * @brief Recursively clear a subtree
   */
  void clearSubtree(AVLNode<T> *node);

  /**
   * @brief Get the height of a node (handles nullptr)
   */
  int getHeight(AVLNode<T> *node) const;

  /**
   * @brief Update the height of a node based on children
   */
  void updateHeight(AVLNode<T> *node);

  /**
   * @brief Calculate balance factor (left height - right height)
   */
  int getBalance(AVLNode<T> *node) const;

  /**
   * @brief Right rotation
   *
   *     y                x
   *    / \              / \
   *   x   C    =>      A   y
   *  / \                  / \
   * A   B                B   C
   */
  AVLNode<T> *rotateRight(AVLNode<T> *y);

  /**
   * @brief Left rotation
   *
   *   x                  y
   *  / \                / \
   * A   y      =>      x   C
   *    / \            / \
   *   B   C          A   B
   */
  AVLNode<T> *rotateLeft(AVLNode<T> *x);

  /**
   * @brief Balance a node after insertion/deletion
   */
  AVLNode<T> *balance(AVLNode<T> *node);

  /**
   * @brief Recursive insert helper
   */
  AVLNode<T> *insertHelper(AVLNode<T> *node, AVLNode<T> *parent, const T &value,
                           bool &inserted);

  /**
   * @brief Recursive remove helper
   */
  AVLNode<T> *removeHelper(AVLNode<T> *node, const T &value, bool &removed);

  /**
   * @brief Find minimum node in subtree
   */
  AVLNode<T> *findMin(AVLNode<T> *node) const;

  /**
   * @brief Helper for inorder traversal
   */
  void inorderHelper(AVLNode<T> *node, T *result, size_t &index) const;

  /**
   * @brief Helper for preorder traversal
   */
  void preorderHelper(AVLNode<T> *node, T *result, size_t &index) const;

  /**
   * @brief Helper for postorder traversal
   */
  void postorderHelper(AVLNode<T> *node, T *result, size_t &index) const;

  /**
   * @brief Helper for printing tree structure
   */
  void printHelper(AVLNode<T> *node, const std::string &prefix,
                   bool isLeft) const;

  /**
   * @brief Helper for JSON serialization
   */
  void toJsonHelper(AVLNode<T> *node, json &j) const;

public:
  // ========================================================================
  // CONSTRUCTORS & DESTRUCTOR
  // ========================================================================

  AVLTree();
  ~AVLTree();

  // Copy constructor
  AVLTree(const AVLTree &other);

  // Move constructor
  AVLTree(AVLTree &&other) noexcept;

  // Copy assignment
  AVLTree &operator=(const AVLTree &other);

  // Move assignment
  AVLTree &operator=(AVLTree &&other) noexcept;

  // ========================================================================
  // CORE OPERATIONS
  // ========================================================================

  /**
   * @brief Insert a value into the AVL tree
   * @param value Value to insert
   * @return true if inserted, false if duplicate
   */
  bool insert(const T &value);

  /**
   * @brief Remove a value from the AVL tree
   * @param value Value to remove
   * @return true if removed, false if not found
   */
  bool remove(const T &value);

  /**
   * @brief Search for a value in the AVL tree
   * @param value Value to search for
   * @return true if found, false otherwise
   */
  bool search(const T &value) const;

  /**
   * @brief Remove all nodes from the tree
   */
  void clear();

  /**
   * @brief Check if the tree is empty
   */
  bool isEmpty() const;

  /**
   * @brief Get the number of nodes in the tree
   */
  size_t nodeCount() const;

  /**
   * @brief Get the height of the tree
   */
  size_t height() const;

  // ========================================================================
  // ACCESSOR METHODS
  // ========================================================================

  /**
   * @brief Get the root node (for question implementations)
   */
  AVLNode<T> *getRoot() const;

  // ========================================================================
  // TRAVERSALS
  // ========================================================================

  /**
   * @brief Inorder traversal (left, root, right)
   * @param count Output parameter for array size
   * @return Dynamically allocated array (caller must delete[])
   */
  T *inorderTraversal(size_t &count) const;

  /**
   * @brief Preorder traversal (root, left, right)
   * @param count Output parameter for array size
   * @return Dynamically allocated array (caller must delete[])
   */
  T *preorderTraversal(size_t &count) const;

  /**
   * @brief Postorder traversal (left, right, root)
   * @param count Output parameter for array size
   * @return Dynamically allocated array (caller must delete[])
   */
  T *postorderTraversal(size_t &count) const;

  /**
   * @brief Level-order traversal (BFS)
   * @param count Output parameter for array size
   * @return Dynamically allocated array (caller must delete[])
   */
  T *levelorderTraversal(size_t &count) const;

  // ========================================================================
  // PRINT OPERATIONS
  // ========================================================================

  /**
   * @brief Print tree structure to console (shows height and balance)
   */
  void print() const;

  /**
   * @brief Print inorder traversal
   */
  void printInorder() const;

  // ========================================================================
  // JSON OPERATIONS
  // ========================================================================

  /**
   * @brief Convert tree to JSON object
   */
  json toJson(const char *name = "AVLTree") const;

  /**
   * @brief Load tree from JSON object
   */
  bool loadFromJson(const json &j);

  /**
   * @brief Load tree from JSON file
   */
  bool loadFromFile(const char *filename);

  /**
   * @brief Save tree to JSON file
   */
  bool saveToFile(const char *filename, const char *name = "AVLTree") const;
};

#include "AVLTree.tpp"

#endif // AVL_TREE_HPP
