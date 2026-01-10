#pragma once

#include <queue>
#include <stdexcept>

namespace ds {

template <typename T>
struct HeapNode {
    T data;
    HeapNode* parent;
    HeapNode* left;
    HeapNode* right;

    HeapNode(T val) : data(val), parent(nullptr), left(nullptr), right(nullptr) {}
};

template <typename T>
class PriorityQueue {
   private:
    HeapNode<T>* root;
    size_t size;
    void swapData(HeapNode<T>* a, HeapNode<T>* b);

    void heapifyUp(HeapNode<T>* node);

    void heapifyDown(HeapNode<T>* node);

   public:
    PriorityQueue();

    ~PriorityQueue();

    void push(const T& value);

    T pop();

    bool isEmpty() const;
};
}  // namespace ds