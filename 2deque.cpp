#include "lldeque.h"

int main(){
    LL::deque<int,LL::allocator<int>, static_cast<size_t>(10)> deq(static_cast<size_t>(10),0);
    return 0;
}