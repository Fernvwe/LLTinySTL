#include "llfunctional.h"
#include "llrb_tree.h"

namespace LL {
template <class Key, class Allocator = LL::allocator<Key>,
          class Compare = LL::less<Key> >
class set {
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

    // TODO reverse_iterator

    using iterator = typename Container_type::const_iterator;

   private:
    Container_type container;

   public:
    set() : container(Container_type()) {}
    iterator begin() { return container.cbegin(); }
    iterator end() { return container.cend(); }
    bool empty() { return container.empty(); }
    size_type size() { return container.size(); }
    void clear() { return container.clear(); }
    void insert(const value_type& x) { container.insert_unique(x); }
    void erase(const value_type& x) { container.erase(x); }
};
}  // namespace LL