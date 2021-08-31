#include <iostream>
#include <vector>

#include "llalloc.h"
template <class T>
struct __list_node {
   public:
    using ptr = __list_node<T>*;
    // data member
    ptr pre;
    ptr next;
    T data;
};
int main() {
    //test the allocator for __list_node
    using list_node_alloc = LL::allocator<__list_node<int>>;
    list_node_alloc a;
    __list_node<int>::ptr p = a.allocate(1);
    int ia[5] = {0, 1, 2, 3, 4};
    unsigned int i;
    std::vector<int, LL::allocator<int> > iv(ia, ia + 5);
    for (i = 0; i < iv.size(); i++) {
        std::cout << iv[i] << ' ';
    }
    std::cout << std::endl;
}
