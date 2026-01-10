#include "../../include/data_structures/PriorityQueue.hpp"
#include <queue>
#include <stdexcept>
#include <models/Crew.hpp>
#include <vector>

namespace ds {

template <typename T>
PriorityQueue<T>::PriorityQueue() : root(nullptr), size(0) {}

template <typename T>
void deleteSubtree(HeapNode<T>* node) {
    if (!node) return;
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() { deleteSubtree(root); }

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

    if (size == 1) {
        delete root;
        root = nullptr;
        size = 0;
        return result;
    }

    size_t idx = size; // index of last node
    // Build path bits excluding the most significant bit
    std::vector<int> path;
    while (idx > 1) {
        path.push_back(idx & 1);
        idx >>= 1;
    }
    // traverse from root following reversed path
    HeapNode<T>* last = root;
    for (int i = (int)path.size() - 1; i >= 0; --i) {
        if (path[i] == 0) last = last->left;
        else last = last->right;
    }

    // Move last's data to root
    root->data = last->data;

    // detach last from its parent
    if (last->parent) {
        if (last->parent->left == last) last->parent->left = nullptr;
        else if (last->parent->right == last) last->parent->right = nullptr;
    }

    delete last;
    --size;

    // Re-heapify down from root
    heapifyDown(root);

    return result;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const { return size == 0; }

template <typename T>
size_t PriorityQueue<T>::getSize() const { return size; }

}

template class ds::PriorityQueue<int>;
template class ds::PriorityQueue<models::Crew>;

