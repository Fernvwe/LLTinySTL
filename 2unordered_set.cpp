#include "llunordered_set.h"
#include <iostream>
int main(){
    LL::unordered_set<int> set;
    for(int i = 0; i < 10; ++i){
        set.insert(i);
    }
    for(auto i : set)
        std::cout<< i <<" ";
    std::cout << std::endl;
    return 0;
}