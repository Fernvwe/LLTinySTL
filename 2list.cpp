#include "lllist.h"
#include <algorithm>
#include <vector>
#include <iostream>
int main(){
    LL::list<int> a;
    // element operator test
    a.push_back(10);
    a.push_front(20);
    for(auto i : a){
       std::cout<<i<<std::endl; 
    }
    a.pop_back();
    a.pop_front();
    a.pop_back(); // Malicious deletion, OK
    // constuctor test
    std::vector<int> nums{7,1,2,3,4};
    std::sort(nums.begin(),nums.end());
        // TODO need reconstruct for robust
    LL::list<int> b(nums.begin(), nums.end());
    b.clear();
    for(auto i:b){
       std::cout<<i<<std::endl; 
    }
    return 0;
}