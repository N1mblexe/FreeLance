#pragma once

#include <functional>
#include <string>

#include "LinkedList.hpp"

namespace ds {

template <typename K, typename V>
struct Entry {
    K key;
    V value;

    bool operator==(const Entry& other) const { return key == other.key; }
};

template <typename K, typename V>
class HashMap {
   private:
    LinkedList<Entry<K, V>>* buckets;
    size_t capacity;
    size_t size;

    size_t hash(const K& key) const {
        std::hash<K> hasher;
        return hasher(key) % capacity;
    }
   public:
    HashMap(size_t cap = 101);

    ~HashMap();

    void put(const K& key, const V& value);

    V* get(const K& key);
};
}  // namespace ds