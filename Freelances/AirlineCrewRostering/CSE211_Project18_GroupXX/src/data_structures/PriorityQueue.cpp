#include "../../include/data_structures/PriorityQueue.hpp"
#include <queue>
#include <stdexcept>

namespace ds {

template <typename T>
PriorityQueue<T>::PriorityQueue() : root(nullptr), size(0) {}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {}

template <typename T>
void PriorityQueue<T>::swapData(HeapNode<T>* a, HeapNode<T>* b) {
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

template <typename T>
void PriorityQueue<T>::heapifyUp(HeapNode<T>* node) {
    while (node->parent && node->data > node->parent->data) {
        swapData(node, node->parent);
        node = node->parent;
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(HeapNode<T>* node) {
    if (!node) return;

    HeapNode<T>* largest = node;
    if (node->left && node->left->data > largest->data) largest = node->left;
    if (node->right && node->right->data > largest->data) largest = node->right;

    if (largest != node) {
        swapData(node, largest);
        heapifyDown(largest);
    }
}

template <typename T>
void PriorityQueue<T>::push(const T& value) {
    HeapNode<T>* newNode = new HeapNode<T>(value);
    if (!root) {
        root = newNode;
    } else {
        std::queue<HeapNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            HeapNode<T>* curr = q.front();
            q.pop();

            if (!curr->left) {
                curr->left = newNode;
                newNode->parent = curr;
                break;
            } else {
                q.push(curr->left);
            }

            if (!curr->right) {
                curr->right = newNode;
                newNode->parent = curr;
                break;
            } else {
                q.push(curr->right);
            }
        }
    }
    size++;
    heapifyUp(newNode);
}

template <typename T>
T PriorityQueue<T>::pop() {
    if (!root) throw std::underflow_error("Queue is empty");
    T result = root->data;
    return result;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const { return size == 0; }

}  // namespace ds

// explicit instantiation for common test type
template class ds::PriorityQueue<int>;

