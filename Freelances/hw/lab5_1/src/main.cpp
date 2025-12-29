// src/main.cpp - Tree Questions Demo (Q1-Q4) with Test Validation
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "AVLTree.hpp"
#include "BST.hpp"
#include "Color.h"
#include "Tree234.hpp"
#include "TreeQuestions.h"

// ============================================================================
// Test Result Tracking
// ============================================================================
struct TestStats {
  int passed = 0;
  int failed = 0;
  int total = 0;
};

TestStats globalStats;

void printTestResult(const std::string &desc, bool passed,
                     const std::string &expected = "",
                     const std::string &actual = "") {
  globalStats.total++;
  if (passed) {
    globalStats.passed++;
    std::cout << "  " << Color::SUCCESS << "[PASS]" << Color::RESET << " "
              << desc;
    if (!expected.empty()) {
      std::cout << " " << Color::DIM << "(expected: " << expected << ")"
                << Color::RESET;
    }
    std::cout << std::endl;
  } else {
    globalStats.failed++;
    std::cout << "  " << Color::ERROR << "[FAIL]" << Color::RESET << " " << desc
              << std::endl;
    if (!expected.empty() || !actual.empty()) {
      std::cout << "         " << Color::DIM << "Expected: " << Color::YELLOW
                << expected << Color::RESET << Color::DIM
                << " | Got: " << Color::RED << actual << Color::RESET
                << std::endl;
    }
  }
}

void printQuestionHeader(int qNum, const std::string &title,
                         const std::string &theme) {
  std::cout << std::endl;
  std::cout << Color::BOLD << Color::BG_BLUE << Color::WHITE
            << " =========================================================== "
            << Color::RESET << std::endl;
  std::cout << Color::BOLD << Color::CYAN << "  Q" << qNum << ": " << title
            << Color::RESET << Color::DIM << " [" << theme << "]"
            << Color::RESET << std::endl;
  std::cout << Color::BOLD << Color::BG_BLUE << Color::WHITE
            << " =========================================================== "
            << Color::RESET << std::endl;
}

void printSectionHeader(const std::string &title) {
  std::cout << std::endl
            << Color::BOLD << Color::MAGENTA << "  * " << title << Color::RESET
            << std::endl;
}

void printTreeInfo(const std::string &info) {
  std::cout << Color::DIM << "    " << info << Color::RESET << std::endl;
}

// ============================================================================
// Q1: Convert BST to Sorted Circular Doubly Linked List
// ============================================================================
void demoQ1() {
  printQuestionHeader(1, "BST to Circular Doubly Linked List",
                      "In-Place Conversion");

  // Use heap allocation to prevent destructor issues
  BST<int> *bst = new BST<int>();
  int values[] = {4, 2, 6, 1, 3, 5, 7};
  for (int v : values) {
    bst->insert(v);
  }

  printSectionHeader("Original BST");
  bst->print();

  printSectionHeader("Converting to Circular DLL");
  size_t originalCount = bst->nodeCount();
  BSTNode<int> *head = convertToCircularDLL(*bst);

  // NOTE: After conversion, the BST structure is destroyed.
  // We must NOT delete bst normally as it will try to traverse corrupted
  // pointers. The nodes are now owned by the circular DLL.

  printSectionHeader("Test Cases");

  // Test 1: Head is not null
  printTestResult("Head is not null", head != nullptr, "not null",
                  head != nullptr ? "not null" : "null");

  if (head != nullptr) {
    // Test 2: Head is smallest element
    printTestResult("Head is smallest element (1)", head->data == 1, "1",
                    std::to_string(head->data));

    // Test 3: Verify forward traversal order
    int forwardOrder[] = {1, 2, 3, 4, 5, 6, 7};
    bool forwardCorrect = true;
    BSTNode<int> *current = head;
    for (int i = 0; i < 7; ++i) {
      if (current->data != forwardOrder[i]) {
        forwardCorrect = false;
        break;
      }
      current = current->right;
    }
    printTestResult("Forward traversal order [1,2,3,4,5,6,7]", forwardCorrect,
                    "1,2,3,4,5,6,7", forwardCorrect ? "correct" : "incorrect");

    // Test 4: Verify circular property (tail->right == head)
    BSTNode<int> *tail = head->left;
    printTestResult("Circular: tail->right == head", tail->right == head,
                    "true", tail->right == head ? "true" : "false");

    // Test 5: Verify tail is largest element
    printTestResult("Tail is largest element (7)", tail->data == 7, "7",
                    std::to_string(tail->data));

    // Test 6: Count nodes in list
    size_t count = 0;
    current = head;
    do {
      count++;
      current = current->right;
    } while (current != head && count <= originalCount + 1);
    printTestResult("Node count matches original", count == originalCount,
                    std::to_string(originalCount), std::to_string(count));

    // Clean up: delete circular DLL nodes manually
    current = head;
    for (size_t i = 0; i < originalCount; ++i) {
      BSTNode<int> *next = current->right;
      delete current;
      current = next;
    }
  }

  // Delete the BST shell (nodes already deleted above)
  // We can't call delete bst because that would try to clear nodes
  // Instead, just leak the small BST object (acceptable for demo)
}

// ============================================================================
// Q2: Reconstruct AVL Tree from Preorder and Height Arrays
// ============================================================================
void demoQ2() {
  printQuestionHeader(2, "Reconstruct AVL from Preorder + Heights",
                      "Tree Building");

  // Create a sample AVL tree first
  printSectionHeader("Original AVL Tree");
  AVLTree<int> original;
  int insertOrder[] = {10, 5, 15, 3, 7, 12, 20};
  for (int v : insertOrder) {
    original.insert(v);
  }
  original.print();

  // Get preorder and heights
  size_t count;
  int *preorder = original.preorderTraversal(count);

  // For this test, we'll manually set heights based on the tree structure
  int heights[] = {3, 2, 1, 1, 2, 1, 1}; // Heights corresponding to preorder

  printSectionHeader("Input Arrays");
  std::cout << "    Preorder: [";
  for (size_t i = 0; i < count; ++i) {
    std::cout << preorder[i];
    if (i < count - 1)
      std::cout << ", ";
  }
  std::cout << "]" << std::endl;

  std::cout << "    Heights:  [";
  for (size_t i = 0; i < count; ++i) {
    std::cout << heights[i];
    if (i < count - 1)
      std::cout << ", ";
  }
  std::cout << "]" << std::endl;

  printSectionHeader("Reconstructing AVL Tree");
  AVLTree<int> *reconstructed = reconstructAVL(preorder, heights, count);

  printSectionHeader("Test Cases");

  // Test 1: Reconstruction succeeded
  printTestResult("Reconstruction succeeded", reconstructed != nullptr,
                  "not null", reconstructed != nullptr ? "not null" : "null");

  if (reconstructed != nullptr) {
    // Test 2: Node count matches
    printTestResult("Node count matches", reconstructed->nodeCount() == count,
                    std::to_string(count),
                    std::to_string(reconstructed->nodeCount()));

    // Test 3: Inorder matches (same values)
    size_t reconCount;
    int *reconInorder = reconstructed->inorderTraversal(reconCount);
    size_t origCount;
    int *origInorder = original.inorderTraversal(origCount);

    bool inorderMatch = (reconCount == origCount);
    if (inorderMatch) {
      for (size_t i = 0; i < reconCount; ++i) {
        if (reconInorder[i] != origInorder[i]) {
          inorderMatch = false;
          break;
        }
      }
    }
    printTestResult("Inorder traversal matches", inorderMatch,
                    "3,5,7,10,12,15,20", inorderMatch ? "matches" : "differs");

    delete[] reconInorder;
    delete[] origInorder;

    // Test 4: Height is reasonable
    printTestResult("Tree height is balanced", reconstructed->height() <= 4,
                    "<=4", std::to_string(reconstructed->height()));

    reconstructed->print();
    delete reconstructed;
  }

  delete[] preorder;
}

// ============================================================================
// Q3: Find Distance Between Two Nodes with Path
// ============================================================================
void demoQ3() {
  printQuestionHeader(3, "Distance Between Nodes with Path",
                      "LCA-Based Calculation");

  BST<int> bst;
  int values[] = {10, 5, 15, 3, 7, 12, 20};
  for (int v : values) {
    bst.insert(v);
  }

  printSectionHeader("BST Structure");
  bst.print();

  printSectionHeader("Test Case 1: Distance from 3 to 12");
  int path1[20];
  size_t pathLen1;
  int dist1 = findDistanceWithPath(bst, 3, 12, path1, pathLen1);

  printTestResult("Distance is 4", dist1 == 4, "4", std::to_string(dist1));
  printTestResult("Path length is 5", pathLen1 == 5, "5",
                  std::to_string(pathLen1));

  std::cout << "    Path: [";
  for (size_t i = 0; i < pathLen1; ++i) {
    std::cout << path1[i];
    if (i < pathLen1 - 1)
      std::cout << " -> ";
  }
  std::cout << "]" << std::endl;

  // Verify path is correct: [3, 5, 10, 15, 12]
  int expectedPath1[] = {3, 5, 10, 15, 12};
  bool pathCorrect1 = (pathLen1 == 5);
  if (pathCorrect1) {
    for (size_t i = 0; i < 5; ++i) {
      if (path1[i] != expectedPath1[i]) {
        pathCorrect1 = false;
        break;
      }
    }
  }
  printTestResult("Path is [3,5,10,15,12]", pathCorrect1, "3,5,10,15,12",
                  pathCorrect1 ? "correct" : "incorrect");

  printSectionHeader("Test Case 2: Distance from 7 to 3");
  int path2[20];
  size_t pathLen2;
  int dist2 = findDistanceWithPath(bst, 7, 3, path2, pathLen2);

  printTestResult("Distance is 2", dist2 == 2, "2", std::to_string(dist2));

  std::cout << "    Path: [";
  for (size_t i = 0; i < pathLen2; ++i) {
    std::cout << path2[i];
    if (i < pathLen2 - 1)
      std::cout << " -> ";
  }
  std::cout << "]" << std::endl;

  printSectionHeader("Test Case 3: Same node (5 to 5)");
  int path3[20];
  size_t pathLen3;
  int dist3 = findDistanceWithPath(bst, 5, 5, path3, pathLen3);

  printTestResult("Distance is 0", dist3 == 0, "0", std::to_string(dist3));
  printTestResult("Path length is 1", pathLen3 == 1, "1",
                  std::to_string(pathLen3));

  printSectionHeader("Test Case 4: Non-existent node");
  int path4[20];
  size_t pathLen4;
  int dist4 = findDistanceWithPath(bst, 3, 100, path4, pathLen4);

  printTestResult("Returns -1 for missing node", dist4 == -1, "-1",
                  std::to_string(dist4));
}

// ============================================================================
// Q4: Range Query with Statistics on 2-3-4 Tree
// ============================================================================
void demoQ4() {
  printQuestionHeader(4, "Range Query on 2-3-4 Tree", "Search with Statistics");

  Tree234<int> tree;
  int values[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
  for (int v : values) {
    tree.insert(v);
  }

  printSectionHeader("2-3-4 Tree Structure");
  tree.print();

  printSectionHeader("Test Case 1: Range [12, 32]");
  int result1[20];
  size_t count1;
  int sum1, min1, max1;
  bool found1 = rangeQuery(tree, 12, 32, result1, count1, sum1, min1, max1);

  printTestResult("Found keys in range", found1, "true",
                  found1 ? "true" : "false");
  printTestResult("Count is 4", count1 == 4, "4", std::to_string(count1));

  if (found1) {
    printTestResult("Sum is 90 (15+20+25+30)", sum1 == 90, "90",
                    std::to_string(sum1));
    printTestResult("Min is 15", min1 == 15, "15", std::to_string(min1));
    printTestResult("Max is 30", max1 == 30, "30", std::to_string(max1));
  }

  printSectionHeader("Test Case 2: Range [1, 100] (all keys)");
  int result2[20];
  size_t count2;
  int sum2, min2, max2;
  bool found2 = rangeQuery(tree, 1, 100, result2, count2, sum2, min2, max2);

  printTestResult("Found all keys", found2 && count2 == 10, "10",
                  std::to_string(count2));
  if (found2) {
    printTestResult("Sum is 275", sum2 == 275, "275", std::to_string(sum2));
    printTestResult("Min is 5", min2 == 5, "5", std::to_string(min2));
    printTestResult("Max is 50", max2 == 50, "50", std::to_string(max2));
  }

  printSectionHeader("Test Case 3: Range [100, 200] (no keys)");
  int result3[20];
  size_t count3;
  int sum3, min3, max3;
  bool found3 = rangeQuery(tree, 100, 200, result3, count3, sum3, min3, max3);

  printTestResult("No keys found", !found3, "false", found3 ? "true" : "false");
  printTestResult("Count is 0", count3 == 0, "0", std::to_string(count3));

  printSectionHeader("Test Case 4: Single key range [20, 20]");
  int result4[20];
  size_t count4;
  int sum4, min4, max4;
  bool found4 = rangeQuery(tree, 20, 20, result4, count4, sum4, min4, max4);

  printTestResult("Found single key", found4 && count4 == 1, "1",
                  std::to_string(count4));
  if (found4) {
    printTestResult("Key is 20", result4[0] == 20, "20",
                    std::to_string(result4[0]));
  }
}

// ============================================================================
// Print Summary
// ============================================================================
void printSummary() {
  std::cout << std::endl;
  std::cout << Color::BOLD << Color::BG_BLUE << Color::WHITE
            << " =========================================================== "
            << Color::RESET << std::endl;
  std::cout << Color::BOLD << Color::CYAN << "  TEST SUMMARY" << Color::RESET
            << std::endl;
  std::cout << Color::BOLD << Color::BG_BLUE << Color::WHITE
            << " =========================================================== "
            << Color::RESET << std::endl;
  std::cout << std::endl;

  std::cout << "  Total Tests: " << globalStats.total << std::endl;
  std::cout << "  " << Color::SUCCESS << "Passed: " << globalStats.passed
            << Color::RESET << std::endl;
  std::cout << "  " << Color::ERROR << "Failed: " << globalStats.failed
            << Color::RESET << std::endl;

  double percentage = (globalStats.total > 0)
                          ? (100.0 * globalStats.passed / globalStats.total)
                          : 0.0;
  std::cout << "  Score: " << std::fixed << std::setprecision(1) << percentage
            << "%" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// Main
// ============================================================================
int main(int argc, char *argv[]) {
  std::cout << Color::BOLD << Color::BG_GREEN << Color::WHITE
            << " =========================================================== "
            << Color::RESET << std::endl;
  std::cout << Color::BOLD << Color::GREEN
            << "  CSE211 - Tree Data Structures Lab" << Color::RESET
            << std::endl;
  std::cout << Color::BOLD << Color::BG_GREEN << Color::WHITE
            << " =========================================================== "
            << Color::RESET << std::endl;

  // Check if specific question is requested
  int questionNum = 0;
  if (argc > 1) {
    questionNum = std::atoi(argv[1]);
  }

  if (questionNum == 0 || questionNum == 1)
    demoQ1();
  if (questionNum == 0 || questionNum == 2)
    demoQ2();
  if (questionNum == 0 || questionNum == 3)
    demoQ3();
  if (questionNum == 0 || questionNum == 4)
    demoQ4();

  printSummary();

  return (globalStats.failed == 0) ? 0 : 1;
}
