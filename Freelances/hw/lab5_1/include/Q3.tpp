#ifndef Q3_TPP
#define Q3_TPP

// ============================================================================
// Q3: Find Distance Between Two Nodes with Path
// ============================================================================
//

#include <stack>
#include <vector>

template <typename T>
int findDistanceWithPath(const BST<T> &tree, const T &val1, const T &val2, T *pathOut, size_t &pathLength)
{
  if (val1 == val2)
  {
    pathOut[0] = val1;
    pathLength = 1;
    return 0;
  }

  pathLength = 0;

  if (!FindPath(tree.getRoot(), val1, val2, pathOut, pathLength))
    return -1;

  return static_cast<int>(pathLength - 1);
}

template <typename T>
bool FindPath(BSTNode<T> *node, const T &val1, const T &val2, T *pathOut, size_t &pathSize)
{
  if (node == nullptr)
    return false;

  if (val1 < node->data && val2 < node->data)
    return FindPath(node->left, val1, val2, pathOut, pathSize);
  if (val1 > node->data && val2 > node->data)
    return FindPath(node->right, val1, val2, pathOut, pathSize);

  std::stack<T> pathV1;
  BSTNode<T> *temp = node;
  while (temp != nullptr)
  {
    pathV1.push(temp->data);
    if (temp->data == val1)
      break;
    temp = (val1 < temp->data) ? temp->left : temp->right;
  }

  if (temp == nullptr)
    return false;

  std::vector<T> pathV2;
  temp = node;
  while (temp != nullptr)
  {
    pathV2.push_back(temp->data);
    if (temp->data == val2)
      break;
    temp = (val2 < temp->data) ? temp->left : temp->right;
  }

  if (temp == nullptr)
    return false;

  size_t idx = 0;
  while (!pathV1.empty())
  {
    pathOut[idx++] = pathV1.top();
    pathV1.pop();
  }

  for (size_t i = 1; i < pathV2.size(); ++i)
    pathOut[idx++] = pathV2[i];
  pathSize = idx;

  return true;
}

#endif // Q3_TPP
