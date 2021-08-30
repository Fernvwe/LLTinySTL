#ifndef __LLLIST__
#define __LLLIST__

#include <cstddef>  // for ptrdiff_t,size_t

#include "llalloc.h"
#include "lliterator.h"
namespace LL {

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
    using pointer = Allocator::pointer;
    using const_pointer = Allocator::const_pointer;
    using iterator = __list_iterator<T>;  
    using const_iterator = ;
    using reverse_iterator = ;
    using const_reverse_iterator = ;
    using link_type = __list_node<T>*
private:
    // data member
    link_type node; // just a node pointer, which can perform the whole list

public:
    // it return a iterator, but static_cast<link_type>((*node).next) is a link_type,
    // Implicit type conversion is occured,link_type --> iterator.
    iterator begin(){ return static_cast<link_type>((*node).next); }
    iterator end(){ return node; }
    bool empty() const{ return node->next == node; }
    difference_type size() const{
        return distance(begin(), end())
    }
    reference front(){return *begin(); }
    reference back(){ return *(--end())}

    // constructor
    list();  // TODO need to define
    ~list();
    // TODO there are much function which aren't decalred.
    // member fucntions
    void push_back(T t) {}
    void push_front(T t);
};

template <class T>
struct __list_iterator : public literator<bidirectional_iterator_tag, T> {
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
    pointer operator->() const {return &(operator*())}  // ? need to revise
    iterator&
    operator++() {
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
template <class T>
struct __list_node {
   public:
    using ptr = __list_node<T>*;
    // data member
    ptr pre;
    ptr next;
    T data;
};



}  // namespace LL
#endif
