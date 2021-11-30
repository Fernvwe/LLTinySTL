#include "llset.h"
#include "llvector.h"
#include <cstdio>

int main(){
    LL::set<int> se_1;
    LL::multiset<int> se_2;
    LL::vector<int> nums = {2,8,4,2,1,7,9};
    auto ite = se_1.begin();
    for(int i : nums){
        se_1.insert(i);
    } 
    auto ptr = se_1.find(10);
    if(ptr == se_1.end())
        printf("This numbers can't be found!!");
    for(int i : nums){
        se_2.insert(i);
    } 
    for(auto i : se_2){
        printf("%d \t",i);
    }
    // *(i) = 10; error: assignment of read-only
    return 0;
}