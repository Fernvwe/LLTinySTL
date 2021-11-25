#include "llset.h"
#include "llvector.h"
#include <cstdio>

int main(){
    LL::set<int> se;
    LL::vector<int> nums = {2,8,4,2,1,7,9};
    for(int i : nums){
        se.insert(i);
    } 
    nums.clear();
    for(auto i : se)
        nums.push_back(i);
    // *(i) = 10; error: assignment of read-only
    return 0;
}