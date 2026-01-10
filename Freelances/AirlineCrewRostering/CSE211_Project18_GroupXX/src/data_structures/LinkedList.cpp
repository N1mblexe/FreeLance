#include "../../include/data_structures/LinkedList.hpp"
#include "../../include/data_structures/Graph.hpp"
#include "../../include/data_structures/HashMap.hpp"
#include <stdexcept>
#include <string>
#include <models/Flight.hpp>

namespace ds {

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() { clear(); }

template <typename T>
void LinkedList<T>::push_back(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);
    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::pop_front() {
    if (!head) throw std::underflow_error("List is empty");

    ListNode<T>* temp = head;
    head = head->next;

    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;

    delete temp;
    size--;
}

template <typename T>
bool LinkedList<T>::isEmpty() const { return size == 0; }

template <typename T>
size_t LinkedList<T>::getSize() const { return size; }

template <typename T>
void LinkedList<T>::clear() {
    while (head) {
        pop_front();
    }
}

template <typename T>
ListNode<T>* LinkedList<T>::getHead() const { return head; }


// Explicit instantiations for types used by test/main
}  // namespace ds

// instantiate common types
template class ds::LinkedList<int>;
template class ds::LinkedList<ds::Vertex>;
template class ds::LinkedList<ds::Edge>;
template class ds::LinkedList< ds::Entry<std::string,int> >;
template class ds::LinkedList<std::string>;
template class ds::LinkedList< models::Flight >;

