#ifndef __LL_UNORDERED_MAP_H__
#define __LL_UNORDERED_MAP_H__
#include "llhashtable.h"
namespace LL {
template <class Key, class T, class Hash = LL::hash<Key>,
          class KeyEqual = LL::equal_to<Key>,
          class Allocator = LL::allocator<LL::pair<Key, T>>>
class unordered_map {
   public:
    using key_type = Key;
    // !
    using value_type = LL::pair<const Key, T>;
    using mapped_type = T;
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
    using self = unordered_map<Key, Hash, KeyEqual, Allocator>;

   private:
    container_type container;

   public:
    unordered_map() : container(container_type(50, hasher(), key_equal())) {}
    unordered_map(const self& rhs) : contianer(rhs.container) {}
    unordered_map(self&& rhs) : container(LL::move(rhs.container)) {}
    self& operator=(const self& rhs) { container = rhs.container; }
    self& operator=(self&& rhs) { container = LL::move(rhs.container); }

    mapped_type& operator[](const key_type& key) {
        return *(container.insert_unique(value_type(key, mapped_type())).first)
                    .second;
    }
    iterator begin() { return container.begin(); }
    iterator cbegin() { return container.cbegin(); }

    iterator end() { return container.end(); }
    iterator cend() { return container.cend(); }

    bool empty() { return container.empty(); }
    size_type size() { return container.size(); }
    size_type max_size() { return container.maxsize(); }

    void clear() { container.clear(); }
    LL::pair<iterator, bool> insert(const value_type& value) {
        return container.insert_unique(value);
    }

    iterator erase() { return container.erase(); }
    void swap(self& rhs) { LL::swap(container, rhs.container); }

    size_type count(const key_type& key) { return container.count(key); }
    iterator find(const key_type& key) { return container.find(key); }
};
template <class Key, class T, class Hash = LL::hash<Key>,
          class KeyEqual = LL::equal_to<Key>,
          class Allocator = LL::allocator<LL::pair<Key, T>>>
class unordered_multimap {
   public:
    using key_type = Key;
    // !
    using value_type = LL::pair<const Key, T>;
    using mapped_type = T;
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
    using self = unordered_multimap<Key, Hash, KeyEqual, Allocator>;

   private:
    container_type container;

   public:
    unordered_multimap()
        : container(container_type(50, hasher(), key_equal())) {}
    unordered_multimap(const self& rhs) : contianer(rhs.container) {}
    unordered_multimap(self&& rhs) : container(LL::move(rhs.container)) {}
    self& operator=(const self& rhs) { container = rhs.container; }
    self& operator=(self&& rhs) { container = LL::move(rhs.container); }

    mapped_type& operator[](const key_type& key) {
        return *(container.insert_equal(value_type(key, mapped_type()))).second;
    }
    iterator begin() { return container.begin(); }
    iterator cbegin() { return container.cbegin(); }

    iterator end() { return container.end(); }
    iterator cend() { return container.cend(); }

    bool empty() { return container.empty(); }
    size_type size() { return container.size(); }
    size_type max_size() { return container.maxsize(); }

    void clear() { container.clear(); }
    iterator insert(const value_type& value) {
        return container.insert_unique(value);
    }

    iterator erase() { return container.erase(); }
    void swap(self& rhs) { LL::swap(container, rhs.container); }

    size_type count(const key_type& key) { return container.multi_count(key); }
    iterator find(const key_type& key) { return container.find(key); }
};

template <class Key, class T>
void swap(unordered_map<Key, T> a, unordered_map<Key, T> b) {
    a.swap(b);
}
template <class Key, class T>
void swap(unordered_multimap<Key, T> a, unordered_multimap<Key, T> b) {
    a.swap(b);
}
}  // namespace LL
#endif