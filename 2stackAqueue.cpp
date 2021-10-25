#include "llstack.h"
#include "llqueue.h"
#include <cstdio>
#include <iostream>

int main(){
    LL::stack<int> sta;
    for(int i = 0; i < 1000; ++i)
        sta.push(i);
    std::printf("%d\n", sta.size());
    for(int i = 0; i < 1000; ++i)
        sta.pop();
    std::printf("%d\n", sta.size());
    if(sta.empty())
        std::printf("the stack is empty.");
    LL::queue<int> que;
    for(int i = 0; i < 1000; ++i)
        que.push(i);
    std::printf("%d\n", que.size());
    for(int i = 0; i < 1000; ++i)
        que.pop();
    std::printf("%d\n", que.size());
    if(que.empty())
        std::printf("the queue is empty.");
    system("pause");
    return 0;
}