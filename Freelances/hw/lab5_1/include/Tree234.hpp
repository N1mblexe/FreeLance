#ifndef TREE234_HPP
#define TREE234_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Color.h"
#include "TreeNode.hpp"
#include "json.hpp"

using json = nlohmann::json;

/**
 * @brief 2-3-4 Tree (B-tree of order 4) implementation
 *
 * A 2-3-4 tree is a self-balancing search tree where:
 * - Each node can have 1, 2, or 3 keys
 * - Each node can have 2, 3, or 4 children (hence 2-3-4)
 * - All leaves are at the same depth
 *
 * @tparam T Data type stored in the tree (must support comparison operators)
 *
 * No STL containers - uses raw pointers and dynamic memory allocation
 */
template <typename T> class Tree234 {
private:
  Node234<T> *root_;
  size_t nodeCount_; // Number of keys (not nodes)

  // ========================================================================
  // PRIVATE HELPER FUNCTIONS
  // ========================================================================

  /**
   * @brief Recursively copy a subtree
   */
  Node234<T> *copySubtree(Node234<T> *node, Node234<T> *parent);

  /**
   * @brief Recursively clear a subtree
   */
  void clearSubtree(Node234<T> *node);

  /**
   * @brief Split a 4-node into two 2-nodes, pushing middle key up
   */
  void split(Node234<T> *node);

  /**
   * @brief Insert a key into a non-full node
   */
  void insertNonFull(Node234<T> *node, const T &value);

  /**
   * @brief Find the appropriate child index for a value
   */
  int findChildIndex(Node234<T> *node, const T &value) const;

  /**
   * @brief Insert a key into a node's key array (maintains sorted order)
   */
  void insertKey(Node234<T> *node, const T &value);

  /**
   * @brief Helper for searching
   */
  bool searchHelper(Node234<T> *node, const T &value) const;

  /**
   * @brief Helper for computing height
   */
  size_t heightHelper(Node234<T> *node) const;

  /**
   * @brief Helper for inorder traversal
   */
  void inorderHelper(Node234<T> *node, T *result, size_t &index) const;

  /**
   * @brief Helper for preorder traversal
   */
  void preorderHelper(Node234<T> *node, T *result, size_t &index) const;

  /**
   * @brief Helper for postorder traversal
   */
  void postorderHelper(Node234<T> *node, T *result, size_t &index) const;

  /**
   * @brief Helper for printing tree structure
   */
  void printHelper(Node234<T> *node, const std::string &prefix,
                   bool isLast) const;

  /**
   * @brief Helper for JSON serialization
   */
  void toJsonHelper(Node234<T> *node, json &j) const;

  /**
   * @brief Count total nodes (not keys) in subtree
   */
  size_t countNodes(Node234<T> *node) const;

  // ========================================================================
  // DELETION HELPERS
  // ========================================================================

  /**
   * @brief Remove a key from the tree
   */
  bool removeHelper(Node234<T> *node, const T &value);

  /**
   * @brief Get predecessor (largest key in left subtree)
   */
  T getPredecessor(Node234<T> *node, int keyIndex);

  /**
   * @brief Get successor (smallest key in right subtree)
   */
  T getSuccessor(Node234<T> *node, int keyIndex);

  /**
   * @brief Merge two children around a key
   */
  void merge(Node234<T> *node, int keyIndex);

  /**
   * @brief Borrow a key from left sibling
   */
  void borrowFromLeft(Node234<T> *node, int childIndex);

  /**
   * @brief Borrow a key from right sibling
   */
  void borrowFromRight(Node234<T> *node, int childIndex);

  /**
   * @brief Ensure child has at least 2 keys before descending
   */
  void fill(Node234<T> *node, int childIndex);

public:
  // ========================================================================
  // CONSTRUCTORS & DESTRUCTOR
  // ========================================================================

  Tree234();
  ~Tree234();

  // Copy constructor
  Tree234(const Tree234 &other);

  // Move constructor
  Tree234(Tree234 &&other) noexcept;

  // Copy assignment
  Tree234 &operator=(const Tree234 &other);

  // Move assignment
  Tree234 &operator=(Tree234 &&other) noexcept;

  // ========================================================================
  // CORE OPERATIONS
  // ========================================================================

  /**
   * @brief Insert a value into the 2-3-4 tree
   * @param value Value to insert
   * @return true if inserted, false if duplicate
   */
  bool insert(const T &value);

  /**
   * @brief Remove a value from the 2-3-4 tree
   * @param value Value to remove
   * @return true if removed, false if not found
   */
  bool remove(const T &value);

  /**
   * @brief Search for a value in the 2-3-4 tree
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
   * @brief Get the number of keys in the tree
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
  Node234<T> *getRoot() const;

  // ========================================================================
  // TRAVERSALS
  // ========================================================================

  /**
   * @brief Inorder traversal
   * @param count Output parameter for array size
   * @return Dynamically allocated array (caller must delete[])
   */
  T *inorderTraversal(size_t &count) const;

  /**
   * @brief Preorder traversal
   * @param count Output parameter for array size
   * @return Dynamically allocated array (caller must delete[])
   */
  T *preorderTraversal(size_t &count) const;

  /**
   * @brief Postorder traversal
   * @param count Output parameter for array size
   * @return Dynamically allocated array (caller must delete[])
   */
  T *postorderTraversal(size_t &count) const;

  // ========================================================================
  // PRINT OPERATIONS
  // ========================================================================

  /**
   * @brief Print tree structure to console
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
  json toJson(const char *name = "Tree234") const;

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
  bool saveToFile(const char *filename, const char *name = "Tree234") const;
};

#include "Tree234.tpp"

#endif // TREE234_HPP
