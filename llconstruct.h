#ifndef __LLCONSTRUCT_H__
#define __LLCONSTRUCT_H__

#include <assert.h>
#include <new.h>

namespace LL {
template <class InputIt, class T>
void unintialize_fill(InputIt first, InputIt last, const T& val) {
    assert(first < last);
    for (; first < last; ++first) *first = val;
}

template <class InputIt, class T>
void construct(InputIt posi, const T& val) {
    *(posi) = val;
}
}  // namespace LL
#endif