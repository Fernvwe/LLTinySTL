#ifndef __LLCONSTRUCT_H__
#define __LLCONSTRUCT_H__

#include <new.h>

namespace LL {
template <class InputIt, class T>
void unintialize_fill(InputIt first, InputIt last, const T& val) {
    assert(first <= last);
    for (; first < last; ++first) *first = val;
}

template <class Ty>
void construct(Ty* ptr){
    ::new ((void *) ptr) Ty();
}
template <class Ty1, class Ty2>
void construct(Ty1* ptr, const Ty2& val){
    ::new ((void *) ptr) Ty1(val);
}
template <class Ty, class ...Args>
void construct(Ty* ptr, Args&& ...args) {
   ::new( (void *)(ptr) ) Ty(forward<Args>(args) ...); // calling constructor of type T
}
}  // namespace LL
#endif