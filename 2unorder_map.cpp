#include "llunordered_set.h"

int main(){
    LL::unordered_set<int> set;
    for(int i  = 0; i < 10; ++i){
        set.insert(i);
    }
    return 0;
}