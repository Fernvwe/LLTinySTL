#ifndef __LLALGORITHM_H__
#define __LLALGORITHM_H__
namespace LL {
// universal swap
// It should be specializated if a container or other constructs were assigned.
template <class T>
void swap(T& a, T& b) noexcept {
    T tmp(a);
    a = b;
    b = tmp;
}
// Copies the elements in the range, defined by [first, last), to another range
// beginning at d_first.
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_first;
}
// Copies the elements from the range, defined by [first, last), to another
// range ending at d_last. The elements are copied in reverse order (the last
// element is copied first), but their relative order is preserved.
template <class BidirIt1, class BidirIt2>
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last) {
    while (first != last) {
        *(--d_last) = *(--last);
    }
    return d_last;
}
template <class T>
T max(const T& val1, const T& val2) {
    return val1 > val2 ? val1 : val2;
}
}  // namespace LL
#endif