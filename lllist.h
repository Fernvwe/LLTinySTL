#ifndef __LLLIST__
#define __LLLIST__

#include <cstddef>  // for ptrdiff_t,size_t

#include "llalgorithm.h"
#include "llalloc.h"
#include "lliterator.h"

namespace LL {
template <class T>
class __list_node {
   public:
    using ptr = __list_node<T>*;
    // data member
    ptr pre;
    ptr next;
    T data;
};
template <class T>
class __list_iterator : public iterator<bidirectional_iterator_tag, T> {
   public:
    // base class member type;
    using iterator_category = bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;
    // member type
    using link_type = __list_node<T>*;

    using size_type = std::size_t;
    using iterator = __list_iterator<T>;
    // member data
    link_type node;

    // constructor
    __list_iterator(link_type x) : node(x) {}
    __list_iterator() {}
    __list_iterator(const iterator& x) : node(x.node) {}

    // * operator overload
    bool operator==(const iterator& x) const { return node == x.node; }
    bool operator!=(const iterator& x) const { return node != x.node; }
    // dereference, take the value of __list_node
    reference operator*() const { return (*node).data; }
    // standard pratice of memeber access
    pointer operator->() const { return &(operator*()); }
    iterator& operator++() {
        node = static_cast<link_type>((*node).next);
        return *this;
    }
    iterator& operator--() {
        node = static_cast<link_type>((*node).pre);
        return *this;
    }
    iterator operator++(int) {
        iterator tmp = *this;
        ++*this;
        return tmp;
    }
    iterator operator--(int) {
        iterator tmp = *this;
        --*this;
        return tmp;
    }
};
/**
 * container list
 * list is a circular bidiraction link list
 */
template <class T, class Allocator = allocator<T> >
class list {
   public:
    // member types define
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename Allocator::const_pointer;
    using iterator = __list_iterator<T>;
    // using const_iterator = ;
    // using reverse_iterator = ;
    // using const_reverse_iterator = ;
    using link_type = __list_node<T>*;

   private:
    using list_node = __list_node<T>;
    // this allocator is designed for
    using list_node_alloc = simple_alloc<list_node>;
    link_type get_node() { return list_node_alloc::allocate(); }
    void put_node(link_type p) { list_node_alloc::deallocate(p); }
    link_type create_node(const T& x) {
        // ! in STL source code analysis, there is a global function
        // construct().
        link_type p = get_node();
        p->data = x;
        return p;
    }
    void destory_node(link_type p) { put_node(p); }
    void empty_initialize() {
        node = get_node();
        node->pre = node;
        node->next = node;
    }

   private:
    // data member
    link_type node;  // just a node pointer, which can perform the whole list
   public:
    // default constructor, a empty list and a node.
    list() { empty_initialize(); }
    // other type iterator constructor
    template <class IteratorOther>
    list(IteratorOther begin, IteratorOther end) {
        // because the list is bidirection iterator, so we only need the
        // operator ++.
        empty_initialize();
        while (begin != end) {
            push_back(*begin);
            ++begin;
        }
    }
    // it return a iterator, but static_cast<link_type>((*node).next) is a
    // link_type, Implicit type conversion is occured,link_type --> iterator.
    iterator begin() { return static_cast<link_type>((*node).next); }
    iterator end() { return node; }
    bool empty() const { return node->next == node; }
    difference_type size() const { return distance(begin(), end()); }
    reference front() { return *begin(); }
    reference back() { return *(--end()); }
    iterator insert(iterator posi, const T& t) {
        link_type tmp = create_node(t);
        // In a bidirection link list, inserting a node needs 4 process at
        // least. In the STL standard, the position of insert operator is
        // in front of iterator .
        posi.node->pre->next = tmp;
        tmp->next = posi.node;
        tmp->pre = posi.node->pre;
        posi.node->pre = tmp;
        return tmp;
    }
    iterator erase(iterator position) {
        link_type prev_node = position.node->pre;
        link_type next_node = position.node->next;
        prev_node->next = next_node;
        next_node->pre = prev_node;
        destory_node(position.node);
        return iterator(next_node);
    }
    // member fucntions
    // element operates
    void push_back(const T& t) { insert(end(), t); }
    void pop_back() {
        iterator tmp = end();
        erase(--tmp);
    }
    void push_front(const T& t) { insert(begin(), t); }
    void pop_front() { erase(begin()); }
    // Move all elements in [first, last) to before position
    void transfer(iterator posi, iterator first, iterator last) {
        // avoid Repeat operation
        if (posi != last) {
            link_type head = static_cast<link_type>(first.node->pre);
            link_type tail = last.node;
            link_type tmp = (--last).node;
            head->next = tail;
            tail->pre = head;
            head = posi.node->pre;
            tail = posi.node;
            head->next = first.node;
            first.node->pre = head;
            tmp->next = tail;
            tail->pre = tmp;
        }
    }

    void clear();
    void remove(const T& value);
    void merge(list& x);
    void reverse();
    void sort();
    void _list_sort(iterator l, iterator r);
    // void _divide(iterator l, iterator r);
    // void _merge(iterator lsta, iterator lend, iterator rsta, iterator rend);
    void swap(list& x) { LL::swap(node, x.node); }
    // Join x before the position pointed to by posi, x must be different from
    // *this.
    void splice(iterator posi, list& x) {
        if (!x.empty()) transfer(posi, x.begin(), x.end());
    }
    // Join i before the position pointed to by posi, position and i could
    // point the same one.
    void splice(iterator posi, list&, iterator i) {
        iterator j = i;
        ++j;
        if (posi == i || posi == j) return;
        transfer(posi, i, j);
    }
    void splice(iterator posi, list&, iterator first, iterator last) {
        if (first != last) transfer(posi, first, last);
    }
};

template <class T, class Allocator>
void list<T, Allocator>::clear() {
    link_type cur = static_cast<link_type>(node->next);
    while (cur != node) {
        link_type tmp = cur;
        cur = cur->next;
        destory_node(tmp);
    }
    node->next = node;
    node->pre = node;
}
template <class T, class Allocator>
void list<T, Allocator>::remove(const T& value) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
        iterator next = first;
        ++next;
        if (*first == value) erase(first);
        first = next;
    }
}
// join x in this list. Both list must be sorted.
template <class T, class Allocator>
void list<T, Allocator>::merge(list<T, Allocator>& x) {
    iterator fir1 = begin();
    iterator last1 = end();
    iterator fir2 = x.begin();
    iterator last2 = x.end();

    while (fir1 != last1 && fir2 != last2) {
        if (*fir2 < *fir1) {
            iterator next = fir2;
            transfer(fir1, fir2, ++next);
            fir2 = next;
        } else
            ++fir1;
        if (fir2 != last2) transfer(last1, fir2, last2);
    }
}
template <class T, class Allocator>
void list<T, Allocator>::reverse() {
    // if size of list is 1 or 2, this operation is meaningless.
    if (node->next == node || node->next->next == node) return;
    iterator first = begin();
    ++first;
    while (first != end()) {
        iterator old = first;
        ++first;
        transfer(begin(), old, first);
    }
}
// template <class T, class Allocator>
// void list<T, Allocator>::_merge(list<T, Allocator>::iterator lsta,
//                                 list<T, Allocator>::iterator lend,
//                                 list<T, Allocator>::iterator rsta,
//                                 list<T, Allocator>::iterator rend) {
//     using ite =list<T, Allocator>::iterator;
//     ite head = lsta;
//     list<T, Allocator> tmp;
//     while(lsta.node != lend.node && rsta.node != rend.node){
//         if(lsta.node->data < rsta.node->data){
//             tmp.push_back(lsta.node->data);
//             ++lsta;
//         }else{
//             tmp.push_back(rsta.node->data);
//         }
//     }
// }
// template <class T, class Allocator>
// void list<T, Allocator>::_divide(list<T, Allocator>::iterator l,
//                                  list<T, Allocator>::iterator r) {
//     using ite = list<T, Allocator>::iterator;
//     using list = list<T, Allocator>;
//     if (l.node->next == r.node) return;
//     ite slow = l, fast = l;
//     while (fast.node != r.node) {
//         ++fast;
//         ++fast;
//         ++slow;
//     }
//     list lef(l,slow);
//     list rig(slow,r);
//     merge(lef,rig);
// }
template <class T, class Allocator>
void list<T, Allocator>::_list_sort(typename list<T, Allocator>::iterator l,
                                    typename list<T, Allocator>::iterator r) {
    using ite = typename list<T, Allocator>::iterator;
    if (l.node->next == r.node) return;
    ite slow(l), fast(l);
    while (fast.node != r.node && fast.node->next != r.node) {
        ++fast;
        ++fast;
        ++slow;
    }
    _list_sort(l, slow);
    _list_sort(slow, r);
    list<T, Allocator> tmp;
    ite i(l), j(slow);
    while (i != slow && j != r) {
        if (*i <= *j) {
            tmp.push_back(*i);
            ++i;
        } else {
            tmp.push_back(*j);
            ++j;
        }
    }
    while (i != slow) {
        tmp.push_back(*i);
        ++i;
    }
    while (j != r) {
        tmp.push_back(*j);
        ++j;
    }
    ite data(tmp.begin());
    while (l.node != r.node) {   
        *l = *data;
        ++l;
        ++data;
    }
}
// sort() member function
template <class T, class Allocator>
void list<T, Allocator>::sort() {
    // mergeSort
    if (node == node->next || node == node->next->next) return;
    _list_sort(begin(), end());
}

template <typename T>
void swap(list<T>& a, list<T> b) {
    a.swap(b);
}
}  // namespace LL
#endif
