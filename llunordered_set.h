#ifndef __LL_UNORDERED_SET_H__
#define __LL_UNORDERED_SET_H__
#include "llhashtable.h"
namespace LL {
template <class Key, class Hash = LL::hash<Key>,
          class KeyEqual = LL::equal_to<Key>,
          class Allocator = LL::allocator<Key>>
class unordered_set {
   public:
    using key_type = Key;
    using value_type = Key;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename allocator_trait<allocator_type>::pointer;
    using const_pointer =
        typename allocator_trait<allocator_type>::const_pointer;
    using container_type =
        typename LL::hashtable<key_type, key_type, hasher, key_equal,
                               LL::identity<key_type>>;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using local_iterator = typename container_type::const_local_iterator;
    using self = unordered_set<Key, Hash, KeyEqual, Allocator>;

   private:
    container_type container;

   public:
    unordered_set() : container(container_type(50, hasher(), key_equal())) {}
    unordered_set(const self& rhs):contianer(rhs.container){} 
    unordered_set(self&& rhs):container(LL::move(rhs.container)){}
    self& operator=(const self& rhs){
        container = rhs.container;
    }
    self& operator=(self&& rhs){
        container = LL::move(rhs.container);
    }
    iterator begin()  { return container.begin(); }
    iterator cbegin()  { return container.cbegin(); }

    iterator end()  { return container.end(); }
    iterator cend()  { return container.cend(); }

    bool empty() { return container.empty(); }
    size_type size() { return container.size(); }
    size_type max_size() { return container.maxsize(); }

    void clear() { container.clear(); }
    LL::pair<iterator, bool> insert(const value_type& value) {
        return container.insert_unique(value);
    }

    iterator erase() { return container.erase(); }
    void swap(self& rhs) { container.swap(rhs.container); }

    size_type count(const key_type& key) { return container.count(key); }
    iterator find(const key_type& key) { return container.find(key); }
};
template <class Key, class Hash = LL::hash<Key>,
          class KeyEqual = LL::equal_to<Key>,
          class Allocator = LL::allocator<Key>>
class unordered_multiset {
   public:
    using key_type = Key;
    using value_type = Key;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename allocator_trait<allocator_type>::pointer;
    using const_pointer =
        typename allocator_trait<allocator_type>::const_pointer;
    using container_type =
        typename LL::hashtable<key_type, key_type, hasher, key_equal,
                               LL::identity<key_type>>;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using local_iterator = typename container_type::const_local_iterator;
    using self = unordered_multiset<Key, Hash, KeyEqual, Allocator>;

   private:
    container_type container;

   public:
    unordered_multiset() : container(container_type(50, hasher(), key_equal())) {}
    unordered_multiset(const self& rhs):contianer(rhs.container){} 
    unordered_multiset(self&& rhs):container(LL::move(rhs.container)){}
    self& operator=(const self& rhs){
        container = rhs.container;
    }
    self& operator=(self&& rhs){
        container = LL::move(rhs.container);
    } 
    iterator begin()  { return container.begin(); }
    iterator cbegin()  { return container.cbegin(); }

    iterator end()  { return container.end(); }
    iterator cend()  { return container.cend(); }

    bool empty() { return container.empty(); }
    size_type size() { return container.size(); }
    size_type max_size() { return container.maxsize(); }

    void clear() { container.clear(); }
    iterator insert(const value_type& value) {
        return container.insert_equal(value);
    }

    iterator erase() { return container.erase(); }
    void swap(self& rhs) { container.swap(rhs.container) }

    size_type count(const key_type& key) { return container.multi_count(key); }
    iterator find(const key_type& key) { return container.find(key); }
};

template<class Key>
void swap(unordered_set<Key> a, unordered_set<Key> b){
    a.swap(b);
}
template<class Key>
void swap(unordered_multiset<Key> a, unordered_multiset<Key> b){
    a.swap(b);
}
}  // namespace LL
#endif