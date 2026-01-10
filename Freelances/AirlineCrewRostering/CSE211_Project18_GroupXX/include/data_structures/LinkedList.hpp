/**
 * @file LinkedList.hpp
 * @brief Simple doubly-linked list node and container templates.
 */

#pragma once

#include <stdexcept>

namespace ds {

template <typename T>
/**
 * @struct ListNode
 * @brief Node used by `LinkedList<T>` storing the `data` value.
 */
struct ListNode {
    T data;
    ListNode* next;
    ListNode* prev;

    ListNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
/**
 * @class LinkedList
 * @brief Minimal doubly-linked list implementation used by project containers.
 */
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
}