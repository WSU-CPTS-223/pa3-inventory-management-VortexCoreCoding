#ifndef HASH_TABLE
#define HASH_TABLE

#include <functional>
#include <list>
#include <utility>
#include <iostream>
#include <vector>

using std::string;
using std::pair;
using std::list;
using std::vector;
using std::cout;
using std::endl;

template <class Key, class Value> class HashTable {
private:
    vector<list<pair<Key, Value>>> values_; // vector (the actual table) stores lists (for side-chaining) of pairs of keys and values
    size_t table_size_;

public:
    HashTable(int table_size = 1);
    bool Insert(const Key& key, const Value& value);
    bool Delete(const Key& key, const Value& value);
    const Value* Find(const Key& key) const;
    void PrintAtKey(const Key& key) const;
};

#endif

template <class Key, class Value>
inline HashTable<Key, Value>::HashTable(int table_size)
{
    table_size_ = table_size;
    values_ = vector<list<pair<Key, Value>>>(table_size); // initializes vector with empty slots
}

template <class Key, class Value>
inline bool HashTable<Key, Value>::Insert(const Key& key, const Value& value)
{
    std::hash<Key> hasher;
    size_t index = hasher(key) % table_size_; // this should theoretically give the correct array position for the key within the bounds of the table
    
    for (auto& pair : values_[index]) {
        if (pair.first == key && pair.second == value) {
            return false; // duplicate
        }
    }
    // item not present in list, good to add
    values_.at(index).push_front({key, value});
    return true;
}

template <class Key, class Value>
inline bool HashTable<Key, Value>::Delete(const Key& key, const Value& value)
{
    std::hash<Key> hasher;
    size_t index = hasher(key) % table_size_;

    auto it = values_[index].begin(); // it should be a list iterator

    for (; it != values_[index].end(); it++) {
        if (it->first == key) {
            values_[index].erase(it);
            return true;
        }
    }
    return false;
}

template <class Key, class Value>
inline const Value* HashTable<Key, Value>::Find(const Key& key) const
{
    std::hash<Key> hasher;
    size_t index = hasher(key) % table_size_;

    for (auto& pair : values_[index]) {
        if (pair.first == key) {
            return &pair.second;
        }
    }
    return nullptr;
}

template <class Key, class Value>
inline void HashTable<Key, Value>::PrintAtKey(const Key &key) const
{
    std::hash<Key> hasher;
    size_t index = hasher(key) % table_size_;

    for (auto& pair : values_[index]) {
        if (pair.first == key) {
            cout << pair.second < endl;
        }
    }
}
