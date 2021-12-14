#include <iostream>
#include "llvector.h"
int main(){
    // * the strategy of space expand need more thinking.
    LL::vector<int> foo;
    for(int i = 0; i < 100; ++i){
        foo.push_back(i);
    }  
    for(auto i : foo)
        std::cout << i << "\t";
    std::cout << std::endl;
    for(int i = 0; i < 100; ++i){
        foo.pop_back();
    }
    std::cout<< foo.size() << std::endl;
    for(int i = 0; i < 100; ++i){
        foo.emplace_back(10);
    }
    for(auto i : foo)
        std::cout << i << "\t";
    std::cout << std::endl;
    for(int i = 0; i < 100; ++i){
        foo.insert(foo.end() - 1, 20);
    }
    for(auto i : foo)
        std::cout << i << "\t";
    std::cout << std::endl;
    LL::vector<int> foo_2(foo);
    foo.clear();

    for(auto i : foo_2)
        std::cout << i << "\t";
    std::cout << std::endl;
    system("pause");
    return 0;
}