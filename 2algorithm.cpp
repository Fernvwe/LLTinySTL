#include <iostream>
#include "llalgorithm.h"
#include "llvector.h"
int main(){
    LL::vector<int> nums = {1,3,4,2,1};
    LL::copy(nums.begin(), nums.end(), nums.begin() + 1);
    for(auto val : nums){
        std::cout<< val << " ";
    }
    std::cout<<std::endl;
    system("pause");
    return 0;
}