#include "../../include/data_structures/HashMap.hpp"
#include <functional>
#include <string>

namespace ds {

template <typename K, typename V>
HashMap<K, V>::HashMap(size_t cap) : capacity(cap), size(0) {
    buckets = new LinkedList<Entry<K, V>>[capacity];
}

template <typename K, typename V>
HashMap<K, V>::~HashMap() { delete[] buckets; }

template <typename K, typename V>
void HashMap<K, V>::put(const K& key, const V& value) {
    size_t index = hash(key);
    LinkedList<Entry<K, V>>& list = buckets[index];

    ListNode<Entry<K, V>>* curr = list.getHead();
    while (curr) {
        if (curr->data.key == key) {
            curr->data.value = value;
            return;
        }
        curr = curr->next;
    }

    list.push_back({key, value});
    size++;
}

template <typename K, typename V>
V* HashMap<K, V>::get(const K& key) {
    size_t index = hash(key);
    ListNode<Entry<K, V>>* curr = buckets[index].getHead();

    while (curr) {
        if (curr->data.key == key) {
            return &(curr->data.value);
        }
        curr = curr->next;
    }
    return nullptr;
}

// Explicit instantiation can be added here if specific K,V types are known

}  // namespace ds

// explicit instantiation for test
template class ds::HashMap<std::string, int>;

