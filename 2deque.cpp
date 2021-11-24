#include "lldeque.h"
#include <iostream>
#include <cstdio>
#include <string>
int main(){
    LL::deque<int> b;
    LL::deque<int> c(6);
    LL::deque<int> d = {1,2,3,4,5,6,7,8};
    LL::deque<int> f(10,8);
    
    std::cout<< b.size() << std::endl;
    std::cout<< c.size() << std::endl;
    std::cout<< d.size() << std::endl;
    std::cout<< f.size() << std::endl;
    // brute testing for eleemnt operator
    for(int i = 0; i < 1000; ++i){
        b.insert(b.end(), i);
    }
    for(int i = 1000; i < 2000; ++i){
        b.push_back(i);
    }
    for(int i = -1; i > -1000; --i){
        b.insert(b.begin() - 1, i);
    }
    for(int i = -1000; i > -2000; --i){
        b.push_front(i);
    }
    for(int i = 0; i < 5; ++i){
        b.push_back(2); // calling push_back(int&&)
    }
    for(int i = 0; i < 5; ++i){
        b.push_front(10);
    }
    b.insert(b.end() - 2, 0);
    b.insert(b.begin(), 0);
    for(auto a : b){
        std::cout<< a << "\t";
    }
    std::cout<<std::endl;
    f.assign(4,2);
    for(auto val : f){
        ::printf("%d\t", val);
    }
    ::printf("\n");
    // brute testing for element delete
    for(int i = 0; i < 1000; ++i){
        b.pop_back();
    }
    for(int i = 0; i < 1000; ++i){
        b.pop_front();
    }
    ::printf("%d \n", b.size());
    for(auto i : b){
        ::printf("%ld\t",i);
    }
    ::printf("\n");
    for(int i = 0; i < 1000; ++i){
        b.erase(b.end() - 2);
    }
    ::printf("%ld \n", b.size());
    b.erase(b.begin(), b.begin() + 200);
    ::printf("%ld \n", b.size());

    system("pause");
    return 0;
}