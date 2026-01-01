#ifndef Q4_TPP
#define Q4_TPP

// ============================================================================
// Q4: Range Query with Statistics on 2-3-4 Tree
// ============================================================================
//
#include <functional>

template <typename T>
bool AddToResult(T *resultOut, size_t &resultCount, const T &val)
{
  resultOut[resultCount++] = val;
  return true;
}

template <typename T>
bool rangeQuery(const Tree234<T> &tree, const T &minVal, const T &maxVal, T *resultOut, size_t &resultCount, T &sum, T &rangeMin, T &rangeMax)
{
  resultCount = 0;

  rangeQueryHelper(tree.getRoot(), minVal, maxVal, resultOut, resultCount);

  if (resultCount == 0)
    return false;

  sum = T();
  for (size_t i = 0; i < resultCount; ++i)
    sum += resultOut[i];
  rangeMin = resultOut[0];
  rangeMax = resultOut[resultCount - 1];

  return true;
}

template <typename T>
void rangeQueryHelper(Node234<T> *node, const T &minVal, const T &maxVal, T *resultOut, size_t &resultCount)
{
  if (node == nullptr)
    return;

  for (size_t i = 0; i < node->keyCount; ++i)
  {
    rangeQueryHelper(node->children[i], minVal, maxVal, resultOut, resultCount);
    const T &k = node->keys[i];
    if (k >= minVal && k <= maxVal)
    {
      AddToResult(resultOut, resultCount, k);
    }
  }
  rangeQueryHelper(node->children[node->keyCount], minVal, maxVal, resultOut, resultCount);
}

#endif // Q4_TPP
