#include "llfunctional.h"
#include "llrb_tree.h"

namespace LL {
template <class Key, class Allocator = LL::allocator<Key>,
          class Compare = LL::less<Key> >
class set {
   public:
    using Container_type = LL::_rb_tree<Key, Key, LL::identity<Key>, Compare>;
    using key_type = Key;
    using value_type = Key;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using compare_type = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = key_type*;
    using const_pointer = const key_type*;
    using iterator = typename Container_type::const_iterator;
    using reverse_iterator = typename Container_type::const_reverse_iterator;

   private:
    using self = set<Key>;
    Container_type container;

   public:
    set() : container(Container_type()) {}
    set(const self& rhs):container(rhs.container){}
    set(self&& rhs):container(LL::move(rhs.container)){}
    ~set() = default;
    self& operator=(const self& rhs){
        container = rhs.container;
    }
    self& operator=( self&& rhs){
        container = LL::move(rhs.container);
    }
    iterator begin() const { return container.begin(); }
    reverse_iterator rbegin() const { return container.rbegin(); }
    iterator end() const { return container.end(); }
    reverse_iterator rend() const { return container.rend(); }
    bool empty() const { return container.empty(); }
    size_type size() const { return container.size(); }
    void clear() { return container.clear(); }
    void insert(const value_type& x) { container.insert_unique(x); }
    void erase(const value_type& x) { container.erase(x); }
    size_type count(const key_type& key) { return container.count(key); };
    iterator find(const key_type& key) const { return container.find(key); }
    iterator lower_bound(const key_type& key) const {
        return container.lower_bound(key);
    }
    iterator upper_bound(const key_type& key) const {
        return container.upper_bound(key);
    }
};
template <class Key, class Allocator = LL::allocator<Key>,
          class Compare = LL::less<Key> >
class multiset {
   private:
    using Container_type = LL::_rb_tree<Key, Key, LL::identity<Key>, Compare>;
    using key_type = Key;
    using value_type = Key;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using compare_type = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = key_type*;
    using const_pointer = const key_type*;
    using iterator = typename Container_type::const_iterator;
    using reverse_iterator = typename Container_type::const_reverse_iterator;

   private:
    using self = multiset<Key>;
    Container_type container;
   public:
    multiset() : container(Container_type()) {}
    multiset(const self& rhs):container(rhs.container){}
    multiset(self&& rhs):container(LL::move(rhs.container)){}
    ~multiset() = default;
    self& operator=(const self& rhs){
        container = rhs.container;
    }
    self& operator=( self&& rhs){
        container = LL::move(rhs.container);
    }
    iterator begin() const { return container.begin(); }
    reverse_iterator rbegin() const { return container.rbegin(); }
    iterator end() const { return container.end(); }
    reverse_iterator rend() const { return container.rend(); }
    bool empty() const { return container.empty(); }
    size_type size() const { return container.size(); }
    void clear() { return container.clear(); }
    void insert(const value_type& x) { container.insert_equal(x); }
    void erase(const value_type& x) { container.erase(x); }
    iterator find(const key_type& key) { return container.find(key); }
    iterator lower_bound(const key_type& key) const {
        return container.lower_bound(key);
    }
    iterator upper_bound(const key_type& key) const {
        return container.upper_bound(key);
    }
};

}  // namespace LL