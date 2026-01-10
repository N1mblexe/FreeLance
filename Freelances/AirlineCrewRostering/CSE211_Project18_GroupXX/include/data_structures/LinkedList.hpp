#pragma once

#include <stdexcept>

namespace ds {

template <typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode* prev;

    ListNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
   private:
    ListNode<T>* head;
    ListNode<T>* tail;
    size_t size;

   public:
    LinkedList();

    ~LinkedList();

    void push_back(const T& value);

    void pop_front();

    bool isEmpty() const;

    size_t getSize() const;

    void clear();

    ListNode<T>* getHead() const;
};
}  // namespace ds