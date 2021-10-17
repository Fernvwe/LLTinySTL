#include <iostream>
#include "llvector.h"
#include <vector>
int main(){
    
    LL::vector<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.push_back(40);
    a.push_back(50);
    a.push_back(70);
    a.push_back(90);
    a.push_back(100);
    // a[10];
    for(auto it: a){
        std::cout << it <<" ";
    }
    std::cout<<std::endl;
    std::cout<<a.size()<<std::endl;
    std::cout<<a.empty()<<std::endl;
    std::cout<<a.back()<<std::endl;
    a.reserve();
    for(auto it: a){
        std::cout << it <<" ";
    }
    std::cout<<std::endl;
    // 
    a.insert(a.end(), 20);
    for(auto it: a){
        std::cout << it <<" ";
    }
    std::cout<<std::endl;
    // a.clear();
    a.erase(a.begin());
    a.pop_back();
    for(auto it: a){
        std::cout << it <<" ";
    }
    std::cout<<std::endl;
    std::cout<<a.size()<<std::endl;
    LL::vector<int> b;
    LL::swap(a,b);
    for(auto it: b){
        std::cout << it <<" ";
    }
    std::cout<<std::endl;
    LL::vector<int> c(10,0);
    for(auto it: c){
        std::cout << it <<" ";
    }
    std::cout<<std::endl;
    system("pause");
    return 0;
}