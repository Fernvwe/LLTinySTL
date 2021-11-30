#ifndef __LL_RB_TREE_H__
#define __LL_RB_TREE_H__

#include "llalgorithm.h"
#include "llalloc.h"
#include "lliterator.h"
#include "llutility.h"
namespace LL {

using _rb_tree_color_type = bool;
const _rb_tree_color_type _rb_tree_red = false;
const _rb_tree_color_type _rb_tree_black = true;

template <class T>
struct _rb_tree_node {
    using color_type = _rb_tree_color_type;
    using ptr = _rb_tree_node<T>*;

    color_type color;
    ptr parent;
    ptr left;
    ptr right;
    T val;
    _rb_tree_node(const T& v)
        : val(v), parent(nullptr), left(nullptr), right(nullptr) {}
    static ptr minimum(ptr x) {
        while (x->left != nullptr) x = x->left;
        return x;
    }
    static ptr maximum(ptr x) {
        while (x->right != nullptr) x = x->right;
        return x;
    }
    void swap(_rb_tree_node<T> y) {
        LL::swap(color, y.color);
        LL::swap(parent, y.parent);
        LL::swap(left, y.left);
        LL::swap(right, y.right);
        LL::swap(val, y.val);
    }
};
template <class T>
_rb_tree_node<T>* connect34_impl(const _rb_tree_node<T>*& a,
                                 const _rb_tree_node<T>*& b,
                                 const _rb_tree_node<T>*& c,
                                 const _rb_tree_node<T>*& T1,
                                 const _rb_tree_node<T>*& T2,
                                 const _rb_tree_node<T>*& T3,
                                 const _rb_tree_node<T>*& T4);

template <class T>
bool inline _has_no_redchild(_rb_tree_node<T>* x, _rb_tree_node<T>*& t) {
    if (x->left && x->left->color == _rb_tree_red) {
        t = x->left;
        return false;
    }
    if (x->right && x->right->color == _rb_tree_red) {
        t = x->right;
        return false;
    }
    return true;
}

template <class T, class Ref, class Ptr>
struct _rb_tree_iterator {
    using iterator = _rb_tree_iterator<T, Ref, Ptr>;
    using const_iterator = _rb_tree_iterator<T, const Ref, const Ptr>;
    using link_type = _rb_tree_node<T>*;
    using reference = Ref;
    using pointer = Ptr;
    link_type _node;
    _rb_tree_iterator() : _node(nullptr) {}
    _rb_tree_iterator(link_type x) : _node(x) {}
    _rb_tree_iterator(const iterator& it) : _node(it._node) {}

    reference operator*() const { return _node->val; }

    bool operator==(const iterator& y) { return _node == y._node; }

    bool operator!=(const iterator& y) { return _node != y._node; }
    void _increment();
    void _decrement();
    iterator& operator++() {
        this->_increment();
        return *this;
    }
    iterator operator++(int) {
        auto tmp = *this;
        this->_increment();
        return tmp;
    }
    iterator& operator--() {
        this->_decrement();
        return *this;
    }
    iterator operator--(int) {
        auto tmp = *this;
        this->_decrement();
        return tmp;
    }
};

template <class T, class Ref, class Ptr>
void _rb_tree_iterator<T, Ref, Ptr>::_increment() {
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left) _node = _node->left;
    } else {
        auto par = _node->parent;
        while (_node == par->right) {
            _node = par;
            par = par->parent;
        }
        if (_node->right != par) _node = par;
    }
}

template <class T, class Ref, class Ptr>
void _rb_tree_iterator<T, Ref, Ptr>::_decrement() {
    if (_node->color == _rb_tree_red && _node->parent->parent == _node) {
        _node = _node->right;
    } else if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    } else {
        auto y = _node->parent;
        while (_node == y->left) {
            _node = y;
            y = y->parent;
        }
        _node = y;
    }
}

template <class Key, class Value, class KeyofValue, class Compare,
          class Alloc = allocator<Value>>
class _rb_tree {
   public:  // type define
    using tree_node = _rb_tree_node<Value>;
    using tree_node_allocator = LL::simple_alloc<tree_node>;
    using color_type = _rb_tree_color_type;

    using key_type = Key;
    using value_type = Value;
    using pointer = value_type*;
    using link_type = tree_node*;
    using reference = value_type&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator = _rb_tree_iterator<Value, Value&, Value*>;
    using const_iterator = _rb_tree_iterator<Value, const Value&, const Value*>;
    using reverse_iterator = LL::reverse_iterator<iterator>;
    using const_reverse_iterator = LL::reverse_iterator<const_iterator>;

   private:
    link_type get_node() { return tree_node_allocator::allocate(); }
    link_type create_node(const value_type& x) {
        link_type tmp = tree_node_allocator::allocate();
        LL::_construct(tmp, x);
        return tmp;
    }

   private:
    size_type node_count;
    link_type header;
    Compare key_compare;

   private:
    link_type root() const { return (link_type)header->parent; }
    link_type leftmost() const { return (link_type)header->left; }
    link_type rightmost() const { return (link_type)header->right; }

    static link_type& left(link_type x) { return (link_type&)x->left; }
    static link_type& right(link_type x) { return (link_type&)x->right; }
    static link_type& parent(link_type x) { return (link_type&)x->parent; }
    static reference value(link_type x) { return (reference)x->val; }
    static const Key& key(link_type x) { return KeyofValue()(x->val); }
    static color_type& color(link_type x) { return (color_type&)(x->color); }

   private:
    void empty_initialize() {
        header->color = _rb_tree_red;
        header->parent = nullptr;
        header->left = header;   // leftmost
        header->right = header;  // rightmost
    }
    // iterator _insert(link_type x, link_type y, const value_type& v);
    iterator _insert(link_type y, const value_type& v);
    void rebalance_rbtree_insert(const link_type& x);
    void rebalance_for_erase(link_type p, link_type x, link_type s);
    void erase_aux(link_type y, link_type x);
    void connect34(link_type g, link_type p, link_type v);
    link_type find_imp(const key_type& key) const;
    link_type lower_bound_impl(const key_type& key) const;
    link_type upper_bound_impl(const key_type& key) const;
    void destory_node_aux(link_type node);

   public:
    _rb_tree() : header(get_node()), node_count(0), key_compare(Compare()) {
        empty_initialize();
    }
    iterator begin() { return header->left; }
    const_iterator begin() const { return header->left; }
    iterator cbegin() const { return header->left; }
    reverse_iterator rbegin() { return end(); }
    const_reverse_iterator rbegin() const { return end(); }
    iterator end() { return header; }
    const_iterator end() const { return header; }
    iterator cend() const { return header; }
    reverse_iterator rend() { return begin(); }
    const_reverse_iterator rend() const { return begin(); }
    bool empty() const noexcept { return node_count == 0; }
    size_type size() { return node_count; }
    size_type count(const key_type& key)const;
    iterator find(const key_type& key) {
        return static_cast<iterator>(find_imp(key));
    }
    const_iterator find(const key_type& key) const {
        return static_cast<const_iterator>(find_imp(key));
    }
    // element operator
    pair<iterator, bool> insert_unique(const value_type& v);
    iterator insert_equal(const value_type& v);
    void erase(iterator posi);
    void erase(const value_type& x);
    void clear() {
        destory_node_aux(header->parent);
        header->parent = header;
    }
    // the first element not less than key
    iterator lower_bound(const key_type& key) { return lower_bound_impl(key); }
    const_iterator lower_bound(const key_type& key) const {
        return lower_bound_impl(key);
    }
    iterator upper_bound(const key_type& key) { return upper_bound_impl(key); }
    const_iterator upper_bound(const key_type& key) const {
        return upper_bound_impl(key);
    }
};
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
typename _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::link_type
_rb_tree<Key, Value, KeyofValue, Compare, Alloc>::upper_bound_impl(
    const key_type& key) const {
    link_type node = root();
    link_type par = header;
    while (node != nullptr) {
        if (key_compare(KeyofValue()(node->val), KeyofValue()(key))) {
            par = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return par;
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
typename _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::link_type
_rb_tree<Key, Value, KeyofValue, Compare, Alloc>::lower_bound_impl(
    const key_type& key) const {
    link_type node = root();
    link_type par = header;
    while (node != nullptr) {
        if (key_compare(KeyofValue()(node->val), KeyofValue()(key))) {
            node = node->right;
        } else {
            node = node->left;
            par = node;
        }
    }
    return par;
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
void _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::destory_node_aux(
    link_type node) {
    if (node == nullptr) return;
    destory_node_aux(node->left);
    destory_node_aux(node->right);
    tree_node_allocator::deallocate(node);
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
typename _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::link_type
_rb_tree<Key, Value, KeyofValue, Compare, Alloc>::find_imp(
    const key_type& key) const {
    auto node = root();
    if (node == header) return header;
    while (node != nullptr) {
        if (node->val == key) return node;
        if (key_compare(KeyofValue()(key), KeyofValue()(node->val))) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return header;
}

template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
void _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::rebalance_rbtree_insert(
    const link_type& x) {
    if (x == root()) {
        x->color = _rb_tree_black;
        return;
    }
    x->color = _rb_tree_red;
    link_type p = x->parent;
    if (p == root() || p->color == _rb_tree_black) return;
    link_type g = p->parent;
    link_type u = (p == g->left) ? g->right : g->left;
    if (u == nullptr || u->color == _rb_tree_black) {
        connect34(g, p, x);
        header->right = tree_node::maximum(root());
        header->left = tree_node::minimum(root());
    } else {
        u->color = _rb_tree_black;
        p->color = _rb_tree_black;
        if (g != root()) g->color = _rb_tree_red;
        rebalance_rbtree_insert(g);
    }
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
typename _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator
_rb_tree<Key, Value, KeyofValue, Compare, Alloc>::_insert(link_type y,
                                                          const value_type& v) {
    link_type z;
    if (y == header || key_compare(KeyofValue()(v), KeyofValue()(y->val))) {
        z = create_node(v);
        y->left = z;
        if (y == header) {
            header->parent = z;
            header->right = z;
        } else if (y == leftmost())
            // update leftmost;
            header->left = z;
    } else {
        z = create_node(v);
        y->right = z;
        if (y == rightmost()) header->right = z;
    }
    z->parent = y;
    rebalance_rbtree_insert(z);
    return z;
}

template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
typename _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator
_rb_tree<Key, Value, KeyofValue, Compare, Alloc>::insert_equal(
    const value_type& v) {
    link_type y = header;
    link_type x = root();
    // search for a sutiable position to insert
    while (x != nullptr) {
        if (key_compare(KeyofValue()(x->val), KeyofValue()(v))) {
            y = x;
            x = x->right;
        } else {
            y = x;
            x = x->left;
        }
    }
    ++node_count;
    return _insert(y, v);
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
pair<typename _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator, bool>
_rb_tree<Key, Value, KeyofValue, Compare, Alloc>::insert_unique(
    const value_type& v) {
    link_type y = header;
    link_type x = root();
    // search for a sutiable position to insert
    while (x != nullptr) {
        if (KeyofValue()(x->val) == KeyofValue()(v)) {
            return make_pair(static_cast<iterator>(x), false);
        }
        if (key_compare(KeyofValue()(x->val), KeyofValue()(v))) {
            y = x;
            x = x->right;
        } else {
            y = x;
            x = x->left;
        }
    }
    ++node_count;
    return make_pair(_insert(y, v), true);
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
void _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::rebalance_for_erase(
    link_type p, link_type x, link_type s) {
    link_type g = p->parent;
    link_type t = nullptr;
    if (s && s->color == _rb_tree_red) {  // BB-3: s is red
        s->color = _rb_tree_black;
        p->color = _rb_tree_red;
        link_type tmp;
        if (p->left == s) {  // zig
            tmp = _right_rotate(p, s);
        } else if (p->right == s) {  // zag
            tmp = _left_rotate(p, s);
        }
        if (g == header) {
            g->parent = tmp;
            tmp->parent = g;
        } else {
            if (g->left == p) {
                g->left = tmp;
            } else if (g->right == p) {
                g->right = tmp;
            }
            tmp->parent = g;
        }
        link_type news = (x == p->left) ? p->right : p->left;
        rebalance_for_erase(p, x, news);
    } else if (s && !_has_no_redchild(s, t)) {  // bb-1: s has a red child.
        _rb_tree_color_type parent_col = p->color;
        link_type b = nullptr;
        if (p->left == s) {      // zig
            if (s->left == t) {  // zig-zig
                t->color = _rb_tree_black;
                p->color = _rb_tree_black;
                s->color = parent_col;
                b = connect34_impl(t, s, p, t->left, t->right, s->right,
                                   p->right);
            } else if (s->right == t) {  // zig-zag
                s->color = _rb_tree_black;
                p->color = _rb_tree_black;
                t->color = parent_col;
                b = connect34_impl(s, t, p, s->left, t->left, t->right,
                                   p->right);
            }
        } else if (p->right == s) {
            if (s->left == t) {  // zag-zig
                s->color = _rb_tree_black;
                p->color = _rb_tree_black;
                t->color = parent_col;
                b = connect34_impl(p, t, s, p->left, t->left, t->right,
                                   s->right);
            } else if (s->right == t) {
                t->color = _rb_tree_black;
                p->color = _rb_tree_black;
                s->color = parent_col;
                b = connect34_impl(p, s, t, p->left, s->left, t->left,
                                   t->right);
            }
        }
        if (g == header) {
            g->parent = b;
            b->parent = g;
        } else {
            if (g->left == p) {
                g->left = b;
            } else if (g->right == p) {
                g->right = b;
            }
            b->parent = g;
        }
    } else if (p->color == _rb_tree_red) {  // bb-2R: parent is red.
        p->color = _rb_tree_black;
        if (s) s->color = _rb_tree_red;
    } else if (p->color == _rb_tree_black) {  // bb-2B: all is black.
        s->color = _rb_tree_red;
        if (g == header) return;
        link_type news = (g->left == p) ? g->right : g->left;
        rebalance_for_erase(g, p, news);
    }
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
void _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::erase(iterator posi) {
    link_type x = posi._node;
    erase_aux(x->parent, x);
}

template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
void _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::erase_aux(link_type y,
                                                                 link_type x) {
    if (!x->left) {
        link_type subx = x->right;
        link_type s = (x == y->right) ? y->left : y->right;
        if (x == root()) {
            y->parent = subx;  // y is header
            if (subx != nullptr) subx->color = _rb_tree_black;
        } else {
            if (x->color == _rb_tree_black)  // Fix first, then replace
                rebalance_for_erase(y, x, s);
            if (y->right == x) {
                y->right = subx;
                s = y->left;
            } else if (y->left == x) {
                y->left = subx;
                s = y->right;
            }
        }
        if (subx != nullptr) subx->parent = y;
        --node_count;
        if (node_count == 0) {
            header->left = header;   // leftmost
            header->right = header;  // rightmost
        } else if (x == rightmost())
            header->right = tree_node::maximum(root());
        else if (x == leftmost())
            header->left = tree_node::minimum(root());
        tree_node_allocator::deallocate(x);
        return;
    } else {
        link_type par = x;
        link_type succ = x->left;
        while (succ->right) {
            par = succ;
            succ = succ->right;
        }
        LL::swap(succ->val, x->val);
        erase_aux(par, succ);
    }
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
void _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::erase(
    const value_type& v) {
    link_type y = header;
    link_type x = root();
    // search for a sutiable position to insert
    while (x != nullptr) {
        if (KeyofValue()(x->val) == KeyofValue()(v)) {
            break;
        }
        if (key_compare(KeyofValue()(x->val), KeyofValue()(v))) {
            y = x;
            x = x->right;
        } else {
            y = x;
            x = x->left;
        }
    }
    if (x == nullptr) return;
    // if x->color is red and x is a leaf. Just to remove it.
    erase_aux(y, x);
}
template <class T>
_rb_tree_node<T>* connect34_impl(_rb_tree_node<T>* a, _rb_tree_node<T>* b,
                                 _rb_tree_node<T>* c, _rb_tree_node<T>* T1,
                                 _rb_tree_node<T>* T2, _rb_tree_node<T>* T3,
                                 _rb_tree_node<T>* T4) {
    a->left = T1;
    if (T1) T1->parent = a;
    a->right = T2;
    if (T2) T2->parent = a;
    c->left = T3;
    if (T3) T3->parent = c;
    c->right = T4;
    if (T4) T4->parent = c;
    b->left = a;
    b->right = c;
    a->parent = b;
    c->parent = b;
    return b;
}
template <class T>
_rb_tree_node<T>* _right_rotate(_rb_tree_node<T>* p, _rb_tree_node<T>* l) {
    p->left = l->right;
    if (l->right) l->right->parent = p;
    l->right = p;
    p->parent = l;
    return l;
}
template <class T>
_rb_tree_node<T>* _left_rotate(_rb_tree_node<T>* p, _rb_tree_node<T>* r) {
    p->right = r->left;
    if (r->left) r->left->parent = p;
    r->left = p;
    p->parent = r;
    return r;
}
template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
void _rb_tree<Key, Value, KeyofValue, Compare, Alloc>::connect34(link_type g,
                                                                 link_type p,
                                                                 link_type v) {
    link_type gg = g->parent;
    link_type b;
    if (p == g->left) {      // zig
        if (v == p->left) {  // zig-zig
            p->color = _rb_tree_black;
            p->parent = g->parent;
            if (g == root()) g->parent->parent = p;
            b = connect34_impl(v, p, g, v->left, v->right, p->right, g->right);
        } else {  // zig-zag
            v->parent = g->parent;
            if (g == root()) g->parent->parent = v;
            v->color = _rb_tree_black;
            b = connect34_impl(p, v, g, p->left, v->left, v->right, g->right);
        }
    } else {                  // zag
        if (v == p->right) {  // zag-zag
            p->parent = g->parent;
            if (g == root()) g->parent->parent = p;
            p->color = _rb_tree_black;
            b = connect34_impl(g, p, v, g->left, p->left, v->left, v->right);
        } else {  // zag-zig
            v->parent = g->parent;
            if (g == root()) g->parent->parent = v;
            v->color = _rb_tree_black;
            b = connect34_impl(g, v, p, g->left, v->left, v->right, p->right);
        }
    }
    g->color = _rb_tree_red;
    if (gg != header) {
        if (g == gg->left)
            gg->left = b;
        else
            gg->right = b;
    }
}
template <class T>
void swap(_rb_tree_node<T>& x, _rb_tree_node<T>& y) {
    x.swap(y);
}
}  // namespace LL
#endif