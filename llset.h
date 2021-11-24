#include "llrb_tree.h"
#include "llfunctional.h"

namespace LL{
    template < 
        class Key,
        class Allocator = LL::allocator<Key>,
        class Compare = LL::less<Key>
    >class set{
        private:
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

            using iterator = const _rb_tree_iterator<Key>;
            // TODO reverse_iterator

            using Container_type = LL::_rb_tree<Key,Key,LL::identity<Key>, Compare>;
        private:
            Container_type container;

        public:
            set():container(Container_type());
            
    };
}