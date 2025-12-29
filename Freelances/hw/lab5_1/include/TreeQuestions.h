#ifndef TREE_QUESTIONS_H
#define TREE_QUESTIONS_H

#include "AVLTree.hpp"
#include "BST.hpp"
#include "Tree234.hpp"

// ============================================================================
// CSE211 TREE LAB - STUDENT QUESTIONS
// ============================================================================
//
// Instructions:
// - Implement the functions in the corresponding Q*.tpp files
// - Do NOT modify this header file
// - Each function has specific requirements documented below
// - Test your implementations using the provided test cases
//
// ============================================================================

// ============================================================================
// Q1: Convert BST to Sorted Circular Doubly Linked List (In-Place)
// ============================================================================
/**
 * @brief Convert a BST to a sorted circular doubly linked list in-place
 *
 * Transform the BST into a circular doubly linked list where:
 * - The 'left' pointer acts as 'prev' in the linked list
 * - The 'right' pointer acts as 'next' in the linked list
 * - Nodes are in sorted (inorder) order
 * - The list is circular: last->right = first, first->left = last
 *
 * @tparam T Data type stored in the tree
 * @param tree The BST to convert (will be modified)
 * @return Pointer to the HEAD (smallest element) of the circular list
 *         Returns nullptr if tree is empty
 *
 * IMPORTANT: This is an IN-PLACE conversion. Do NOT allocate new nodes.
 *            After this function, the tree structure is destroyed.
 *
 * Example:
 *       4
 *      / \
 *     2   6
 *    / \ / \
 *   1  3 5  7
 *
 *   Becomes: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 <-> 7 <-> (back to 1)
 *            ^                                     |
 *            |_____________________________________|
 *
 *   Returns pointer to node with value 1
 *
 * Verification:
 * - Traverse using 'right' pointers: should visit nodes in ascending order
 * - Traverse using 'left' pointers: should visit nodes in descending order
 * - head->left should point to tail (largest element)
 * - tail->right should point to head (smallest element)
 *
 * Hints:
 * - Use tree.getRoot() to get the root BSTNode<T>*
 * - BSTNode has: data, left, right, parent fields
 * - Think about inorder traversal and linking nodes as you visit them
 * - You may use recursion or iteration
 * - Consider tracking head and tail of the list being built
 */
template <typename T> BSTNode<T> *convertToCircularDLL(BST<T> &tree);

// ============================================================================
// Q2: Reconstruct AVL Tree from Preorder and Height Arrays
// ============================================================================
/**
 * @brief Reconstruct an AVL tree from preorder traversal and height arrays
 *
 * Given two arrays:
 * - preorder[]: The preorder traversal of an AVL tree
 * - heights[]:  The height of each node (corresponding to preorder array)
 *
 * Reconstruct the original AVL tree structure.
 *
 * @tparam T Data type stored in the tree
 * @param preorder Array containing preorder traversal values
 * @param heights Array containing height of each node (parallel to preorder)
 * @param size Number of elements in the arrays
 * @return Pointer to a new AVLTree containing the reconstructed tree
 *         Returns nullptr if inputs are invalid
 *
 * Height definition:
 * - A leaf node has height 1
 * - An empty subtree has height 0
 * - Node height = 1 + max(left_height, right_height)
 *
 * Example:
 *   preorder = [10, 5, 3, 7, 15, 12, 20]
 *   heights  = [3,  2, 1, 1, 2,  1,  1]
 *
 *   Reconstructs:
 *          10 (h=3)
 *         /  \
 *      5(h=2) 15(h=2)
 *      /  \   /  \
 *    3(1) 7(1) 12(1) 20(1)
 *
 * The function should:
 * 1. Allocate a new AVLTree
 * 2. Reconstruct the exact structure using preorder and height info
 * 3. Verify the result is a valid AVL tree
 * 4. Return nullptr if reconstruction fails or result is invalid
 *
 * Hints:
 * - Preorder visits: root, left subtree, right subtree
 * - Height info helps determine subtree boundaries
 * - Use recursion to build left and right subtrees
 * - A node with height h has children with height < h
 * - The caller is responsible for deleting the returned tree
 */
template <typename T>
AVLTree<T> *reconstructAVL(const T *preorder, const int *heights, size_t size);

// ============================================================================
// Q3: Find Distance Between Two Nodes with Path
// ============================================================================
/**
 * @brief Find the distance between two nodes and print the path
 *
 * Given a BST and two values, find:
 * 1. The distance (number of edges) between the two nodes
 * 2. The path from the first node to the second node
 *
 * @tparam T Data type stored in the tree
 * @param tree The BST to search in
 * @param val1 First node value
 * @param val2 Second node value
 * @param pathOut Output array to store the path (caller allocates)
 * @param pathLength Output: number of nodes in the path
 * @return The distance (number of edges) between the nodes
 *         Returns -1 if either node is not found
 *
 * Distance definition:
 * - Distance from a node to itself is 0
 * - Distance between adjacent nodes is 1
 * - Distance = number of edges in the path
 *
 * Path format:
 * - pathOut should contain all nodes from val1 to val2 (inclusive)
 * - Path goes through the Lowest Common Ancestor (LCA)
 *
 * Example:
 *       10
 *      /  \
 *     5    15
 *    / \   / \
 *   3   7 12  20
 *
 *   findDistanceWithPath(tree, 3, 12, pathOut, pathLength)
 *   Returns: 4 (edges: 3->5->10->15->12)
 *   pathOut: [3, 5, 10, 15, 12]
 *   pathLength: 5
 *
 *   findDistanceWithPath(tree, 7, 3, pathOut, pathLength)
 *   Returns: 2 (edges: 7->5->3)
 *   pathOut: [7, 5, 3]
 *   pathLength: 3
 *
 * Hints:
 * - First find the Lowest Common Ancestor (LCA) of the two nodes
 * - Distance = dist(val1, LCA) + dist(LCA, val2)
 * - Build path by combining: path(val1 to LCA) + path(LCA to val2)
 * - Be careful about path direction and avoiding LCA duplication
 * - Caller allocates pathOut with sufficient size (tree.nodeCount())
 */
template <typename T>
int findDistanceWithPath(const BST<T> &tree, const T &val1, const T &val2,
                         T *pathOut, size_t &pathLength);

// ============================================================================
// Q4: Range Query with Statistics on 2-3-4 Tree
// ============================================================================
/**
 * @brief Find all keys in a range and compute statistics
 *
 * Given a 2-3-4 tree and a range [minVal, maxVal], find all keys
 * within the range (inclusive) and compute statistics.
 *
 * @tparam T Data type stored in the tree (must support arithmetic operations)
 * @param tree The 2-3-4 tree to search
 * @param minVal Minimum value of the range (inclusive)
 * @param maxVal Maximum value of the range (inclusive)
 * @param resultOut Output array to store found keys (caller allocates)
 * @param resultCount Output: number of keys found
 * @param sum Output: sum of all keys in range
 * @param rangeMin Output: minimum key found in range
 * @param rangeMax Output: maximum key found in range
 * @return true if at least one key was found, false otherwise
 *
 * The resultOut array should contain keys in SORTED ORDER.
 *
 * Example:
 *   2-3-4 tree with keys: [5, 10, 15, 20, 25, 30, 35, 40]
 *
 *   rangeQuery(tree, 12, 32, resultOut, count, sum, min, max)
 *   Returns: true
 *   resultOut: [15, 20, 25, 30]
 *   resultCount: 4
 *   sum: 90
 *   rangeMin: 15
 *   rangeMax: 30
 *
 *   rangeQuery(tree, 100, 200, resultOut, count, sum, min, max)
 *   Returns: false
 *   resultCount: 0
 *   (sum, min, max are undefined when no keys found)
 *
 * Hints:
 * - Use tree.getRoot() to access the root Node234<T>*
 * - Node234 has: keys[3], children[4], keyCount, isLeaf()
 * - Traverse the tree, but PRUNE branches that can't contain range values
 * - For efficiency, don't visit subtrees that are entirely out of range
 * - Collect keys in sorted order (inorder traversal naturally does this)
 * - Caller allocates resultOut with size tree.nodeCount()
 */
template <typename T>
bool rangeQuery(const Tree234<T> &tree, const T &minVal, const T &maxVal,
                T *resultOut, size_t &resultCount, T &sum, T &rangeMin,
                T &rangeMax);

// ============================================================================
// Include implementations
// ============================================================================

#include "Q1.tpp"
#include "Q2.tpp"
#include "Q3.tpp"
#include "Q4.tpp"

#endif // TREE_QUESTIONS_H
