#include<cstdio>
#include<iostream>
#include<type_traits>
#include<utility>

int foo(const int& a){
    ::printf("foo 1!\n");
    return a;
}

int foo(int && a){
    ::printf("foo 2!\n");
    return a;
}

void Foo(const int & a){
    ::printf("FOO 1 \n");
}
void Foo(int && a){
    ::printf("FOO 2 \n");
    foo(a); // 即使 a 本身是一个右值引用,但是在下层调用时还是会被设定为非右值
    foo(std::move(a)); // 使用std::move 就可以将内容转化右值引用
}
int main(){
    Foo(int(10));
    system("pause");
}