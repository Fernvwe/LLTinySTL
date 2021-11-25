#ifndef __LLALLOC__
#define __LLALLOC__

#include <climits>
#include <cstddef>  // for ptrdiff_t,size_t
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <new>  // for placement new

#include "llutility.h" 
#include "lliterator.h"


/**
 * ! _* and __* present that  shouldn't be called.  
 *  
 */
namespace LL {

template <class T>
inline T* _allocate(ptrdiff_t size, T*) {
    std::set_new_handler(0);
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if (tmp == 0) {
        std::cerr << "out of memory" << std::endl;
        exit(0);
    }
    return tmp;
}

template <class T>
inline void _deallocate(T* buffer) {
    if(buffer == nullptr)   return;
    ::operator delete(buffer);
}
template <class T>
void _construct(T* ptr){
    ::new ((void*)(ptr)) T();
}
template <class Ty1, class Ty2>
void _construct(Ty1* ptr, const Ty2& value) {
    ::new ((void *)(ptr)) Ty1(value);
}
template <class Ty, class ...Args>
void _construct(Ty* ptr, Args&& ...args){
    ::new ((void *)(ptr)) Ty(forward<Args>(args) ...);
}
template <class T>
inline void _destroy_one(T* ptr, std::true_type) {}
template <class T>
inline void _destroy_one(T* ptr, std::false_type) {
    if( ptr != nullptr)
        ptr->~T();
}
template <class ForwardIter>
inline void _destory_cat(ForwardIter first, ForwardIter last, std::true_type){}
template <class ForwardIter>
inline void _destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
    for(; first != last; ++first)
        _destroy(&*first);
}
template <class T>
inline void _destroy(T ptr) {
    _destroy_one(ptr, std::is_trivially_destructible<T>{});
}
template <class ForwardIter>
inline void _destroy(ForwardIter first, ForwardIter last) {
    _destory_cat(first,last, std::is_trivially_destructible<
        typename iterator_traits<ForwardIter>::value_type
    >{});
}

template <class T>
class allocator {
   public:
    // the standard interface
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_referrence = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    // rebind allocator of type U
    template <class U>
    struct rebind {
        using other = allocator<U>;
    };
    pointer static  allocate(size_type n, const void* hint = 0) {
        return _allocate((difference_type)n, (pointer)0);
    }
    void static deallocate(pointer p) { _deallocate(p); }

    // the follow functions was remove in c++ 20
    void static construct(pointer p, const T& value) { _construct(p, value); }
    // the movable semnatic 
    template <class ...Args>
    void static construct(pointer p, Args&&... args){ 
        _construct(p, forward<Args>(args)...);
    } 
    // TODO there are need more thinking
    void static destory(pointer p) { _destroy(p); }
    void static destory(pointer first, pointer last){
        _destroy(first,last);
    }

    pointer address(reference x) { return (pointer)&x; }
    const_pointer const_address(const_referrence x) {
        return (const_pointer)&x;
    }
};
template <class T, class Alloc = allocator<T>>
class simple_alloc : public allocator<T> {
   public:
    using typename allocator<T>::pointer;
    static pointer allocate() { return _allocate(1, static_cast<pointer>(0)); }
    static void deallocate(pointer p) { return _deallocate(p); }
};
}  // namespace LL

#endif
