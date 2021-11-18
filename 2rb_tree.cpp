#include "llrb_tree.h"
#include "llfunctional.h"
#include "llvector.h"
#include <iostream>
#include <cstdlib>

using namespace LL;

int main(){
    // LL::vector<int> a = {1,7,2,3,4,5,6};
    LL::vector<int> a = {11,7,9,2,5,3,4}; 
    _rb_tree<int,int, ::identity<int>, ::less<int>> my_tree;
// insert testing
    for(int i = 0; i < a.size(); ++i){
        my_tree.insert_equal(a[i]);
    }
    auto it = my_tree.begin();
    for(;it  != my_tree.end(); ++it)
        std::cout << *it << "\t";
    std::cout<<std::endl;
// erase testing
    // for(int i = 0; i < a.size()-2; ++i)
    //     my_tree.erase(a[i]);
    my_tree.erase(9);
    it = my_tree.begin();
    for(;it != my_tree.end(); ++it)
        std::cout << *it << "\t";
    std::cout<<std::endl;
    system("pause");
    return 0;
}