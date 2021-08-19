#ifndef __LLLIST__
#define __LLLIST__
namespace LL{
template<class T> 
struct _list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};
template<class T, class Ref, class Ptr>
struct _list_iterator{
    typedef _list_iterator<T, T&, T*> iterator;
    typedef _list_iterator<T, Ref, Ptr> self;
    // the interface of stl
    typedef bidirectional_iterator_tag  iterator_category; //1
    typedef T value_type;		//2 
    typedef Ptr pointer;		//3 
    typedef Ref reference; 	//4
    typedef _list_node<T>* link_type; 
    typedef size_t  size_type; 
    typedef ptrdiff_t difference_type; //5  

    link_type node;
    // constructor 
    _list_iterator(){}
    _list_iterator(link_type x):node(x){}

};
}
#endif