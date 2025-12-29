#ifndef BST_HPP
#define BST_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Color.h"
#include "json.hpp"
#include "TreeNode.hpp"

using json = nlohmann::json;

/**
 * @brief Pointer-based Binary Search Tree implementation
 *
 * @tparam T Data type stored in the tree (must support comparison operators)
 *
 * No STL containers - uses raw pointers and dynamic memory allocation
 */
template <typename T>
class BST {
protected:
    BSTNode<T>* root_;
    size_t nodeCount_;

    // ========================================================================
    // PROTECTED HELPER FUNCTIONS
    // ========================================================================

    /**
     * @brief Recursively copy a subtree
     */
    BSTNode<T>* copySubtree(BSTNode<T>* node, BSTNode<T>* parent);

    /**
     * @brief Recursively clear a subtree
     */
    void clearSubtree(BSTNode<T>* node);

    /**
     * @brief Find the minimum node in a subtree
     */
    BSTNode<T>* findMin(BSTNode<T>* node) const;

    /**
     * @brief Find the maximum node in a subtree
     */
    BSTNode<T>* findMax(BSTNode<T>* node) const;

    /**
     * @brief Calculate height of a subtree
     */
    size_t heightHelper(BSTNode<T>* node) const;

    /**
     * @brief Helper for inorder traversal
     */
    void inorderHelper(BSTNode<T>* node, T* result, size_t& index) const;

    /**
     * @brief Helper for preorder traversal
     */
    void preorderHelper(BSTNode<T>* node, T* result, size_t& index) const;

    /**
     * @brief Helper for postorder traversal
     */
    void postorderHelper(BSTNode<T>* node, T* result, size_t& index) const;

    /**
     * @brief Helper for printing tree structure
     */
    void printHelper(BSTNode<T>* node, const std::string& prefix, bool isLeft) const;

    /**
     * @brief Helper for JSON serialization
     */
    void toJsonHelper(BSTNode<T>* node, json& j) const;

public:
    // ========================================================================
    // CONSTRUCTORS & DESTRUCTOR
    // ========================================================================

    BST();
    ~BST();

    // Copy constructor
    BST(const BST& other);

    // Move constructor
    BST(BST&& other) noexcept;

    // Copy assignment
    BST& operator=(const BST& other);

    // Move assignment
    BST& operator=(BST&& other) noexcept;

    // ========================================================================
    // CORE OPERATIONS
    // ========================================================================

    /**
     * @brief Insert a value into the BST
     * @param value Value to insert
     * @return true if inserted, false if duplicate
     */
    virtual bool insert(const T& value);

    /**
     * @brief Remove a value from the BST
     * @param value Value to remove
     * @return true if removed, false if not found
     */
    virtual bool remove(const T& value);

    /**
     * @brief Search for a value in the BST
     * @param value Value to search for
     * @return true if found, false otherwise
     */
    bool search(const T& value) const;

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
    BSTNode<T>* getRoot() const;

    // ========================================================================
    // TRAVERSALS
    // ========================================================================

    /**
     * @brief Inorder traversal (left, root, right)
     * @param count Output parameter for array size
     * @return Dynamically allocated array (caller must delete[])
     */
    T* inorderTraversal(size_t& count) const;

    /**
     * @brief Preorder traversal (root, left, right)
     * @param count Output parameter for array size
     * @return Dynamically allocated array (caller must delete[])
     */
    T* preorderTraversal(size_t& count) const;

    /**
     * @brief Postorder traversal (left, right, root)
     * @param count Output parameter for array size
     * @return Dynamically allocated array (caller must delete[])
     */
    T* postorderTraversal(size_t& count) const;

    /**
     * @brief Level-order traversal (BFS)
     * @param count Output parameter for array size
     * @return Dynamically allocated array (caller must delete[])
     */
    T* levelorderTraversal(size_t& count) const;

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
    json toJson(const char* name = "BST") const;

    /**
     * @brief Load tree from JSON object
     */
    bool loadFromJson(const json& j);

    /**
     * @brief Load tree from JSON file
     */
    bool loadFromFile(const char* filename);

    /**
     * @brief Save tree to JSON file
     */
    bool saveToFile(const char* filename, const char* name = "BST") const;
};

#include "BST.tpp"

#endif // BST_HPP
