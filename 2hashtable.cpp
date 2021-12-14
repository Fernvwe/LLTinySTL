#include <iostream>

#include "llfunctional.h"
#include "llhashtable.h"
#include "llhash_fun.h"
int main() {
    LL::hashtable<int, int, LL::hash<int>, LL::equal_to<int>,
                  LL::identity<int>>
        iht(50, LL::hash<int>(), LL::equal_to<int>());
    for(int i = 0; i < 20; ++i){
        iht.insert_equal(i);
    }
    iht.insert_equal(15);
    for(auto i : iht){
        std::cout << i <<" ";
    }
    std::cout<<std::endl;
    return 0;
}