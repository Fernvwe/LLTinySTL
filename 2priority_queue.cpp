#include <iostream>

#include "llpriority_queue.h"
#include "llvector.h"

int main() {
    LL::priority_queue<int> pq;
    for (int i = 0; i < 100; ++i) {
        pq.push(i);
    }
    for (int i = 0; i < 100; ++i) {
        std::cout << pq.top() << "\t";
        pq.pop();
    }
    std::cout << std::endl;
    LL::vector<int> n = {1,2,3,4,5,6};
    LL::priority_queue<int> a(n);
    a.pop();
    a.pop();
    a.pop();
    for(auto i : a.c)
        std::cout << i << "\t";
    a.pop();
    for(auto i : a.c)
        std::cout << i << "\t";
    std::cout << std::endl;
    system("pause");
    return 0;
}