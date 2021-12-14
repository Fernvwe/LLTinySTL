#include "llfunctional.h"
#include "llrb_tree.h"

namespace LL {
template <class Key, class T,
          class Allocator = LL::allocator<LL::pair<const Key, T>>,
          class Compare = LL::less<Key>>
class map {
   public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = LL::pair<const Key, T>;
    using size_type = size_t;
    using diffenerce_type = ptrdiff_t;
    using key_compare = Compare;
    using reference = value_type&;
    using const_reference = const value_type&;

   private:
    using get_key = LL::selectfirst<value_type>;
    using get_data = LL::selectsecond<value_type>;
    using container_type =
        LL::_rb_tree<Key, value_type, LL::selectfirst<value_type>, key_compare,
                     Allocator>;

   private:
    using self = map<Key,T>;
    container_type container;

   public:
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator =
        typename container_type::const_reverse_iterator;

   public:
    map() : container(container_type()) {}
    map(const self& rhs):container(rhs.container){}
    map(self&& rhs):container(LL::move(rhs.container)){}
    ~map() = default;
    self& operator=(const self& rhs){
        container = rhs.container;
    }
    self& operator=( self&& rhs){
        container = LL::move(rhs.container);
    }

    mapped_type& operator[](const key_type& key) {
        auto it = container.insert_unique(value_type(key, mapped_type()));
        return *(it.first).second;
    }

    iterator begin() { return container.begin(); }
    const_iterator begin() const { return container.begin(); }
    iterator cbegin() const { return container.cbegin(); }
    reverse_iterator rbegin() { return container.rbegin(); }
    const_reverse_iterator rbegin() const { return container.rbegin(); }
    reverse_iterator crbegin() const { return container.rbegin(); }

    iterator end() { return container.end(); }
    const_iterator end() const { return container.end(); }
    iterator cend() const { return container.cend(); }
    reverse_iterator rend() { return container.rend(); }
    const_reverse_iterator rend() const { return container.rend(); }
    reverse_iterator crend() const { return container.rbegin(); }

    bool empty() const noexcept { return container.empty(); }
    size_type size() const noexcept { return container.size(); }

    void clear() { container.clear(); }
    void erase(const key_type& key) { container.erase(key); }
    void erase(iterator it) { container.erase(it); }
    void swap(self rhs) { container.swap(rhs.container); }

    size_type count(const key_type& key) { return container.count(key); }
    iterator find(const key_type& key){return container.find(key);}
    iterator lower_bound(const key_type& key){return container.lower_bound(key); }
    iterator upper_bound(const  key_type& key){ return container.upper_bound(key); }
};

template <class Key, class T,
          class Allocator = LL::allocator<LL::pair<const Key, T>>,
          class Compare = LL::less<Key>>
class multimap {
   public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = LL::pair<const Key, T>;
    using size_type = size_t;
    using diffenerce_type = ptrdiff_t;
    using key_compare = Compare;
    using reference = value_type&;
    using const_reference = const value_type&;
    // definite the allocator_trait;
    // using pointer = ;
    // using const_pointer = ;

   private:
    using get_key = LL::selectfirst<value_type>;
    using get_data = LL::selectsecond<value_type>;
    using container_type =
        LL::_rb_tree<Key, value_type, LL::selectfirst<value_type>, key_compare,
                     Allocator>;

   private:
    using self = multimap<Key,T>;
    container_type container;

   public:
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator =
        typename container_type::const_reverse_iterator;

   public:

    multimap() : container(container_type()) {}
    multimap(const self& rhs):container(rhs.container){}
    multimap(self&& rhs):container(LL::move(rhs.container)){}
    ~multimap() = default;
    self& operator=(const self& rhs){
        container = rhs.container;
    }
    self& operator=( self&& rhs){
        container = LL::move(rhs.container);
    }
    mapped_type& operator[](const key_type& key) {
        auto it = container.insert_equal(value_type(key, mapped_type()));
        return *(it).second;
    }

    iterator begin() { return container.begin(); }
    const_iterator begin() const { return container.begin(); }
    iterator cbegin() const { return container.cbegin(); }
    reverse_iterator rbegin() { return container.rbegin(); }
    const_reverse_iterator rbegin() const { return container.rbegin(); }
    reverse_iterator crbegin() const { return container.rbegin(); }

    iterator end() { return container.end(); }
    const_iterator end() const { return container.end(); }
    iterator cend() const { return container.cend(); }
    reverse_iterator rend() { return container.rend(); }
    const_reverse_iterator rend() const { return container.rend(); }
    reverse_iterator crend() const { return container.rbegin(); }

    bool empty() const noexcept { return container.empty(); }
    size_type size() const noexcept { return container.size(); }

    void clear() { container.clear(); }
    void erase(const key_type& key) { container.erase(key); }
    void erase(iterator it) { container.erase(it); }
    void swap(self rhs) { container.swap(rhs.container); }

    iterator find(const key_type& key){return container.find(key);}
    iterator lower_bound(const key_type& key){return container.lower_bound(key); }
    iterator upper_bound(const  key_type& key){ return container.upper_bound(key); }
};
}  // namespace LL
