#ifndef __LLCONSTRUCT_H__
#define __LLCONSTRUCT_H__

#include <assert.h>
#include <new.h>
#include "llutility.h"
#include "lliterator.h"

namespace LL {
template <class InputIt, class T>
void unintialize_fill(InputIt first, InputIt last, const T& val) {
    assert(first <= last);
    for (; first < last; ++first) *first = val;
}
//  TODO using std::construct
template <class InputIt, class T>
void construct(InputIt* posi, const T& val) {
    ::new( (void *)(posi)) InputIt(val);
}
template <class InputIt, class ...Args>
void construct(InputIt* posi, Args&& ...args) {
   ::new( (void *)(posi) ) InputIt(forward<Args>(args) ...); // calling constructor of type T
}
}  // namespace LL
#endif