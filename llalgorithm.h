#ifndef __LLALGORITHM_H__
#define __LLALGORITHM_H__
namespace LL{
    // universal swap
    // It should be specializated if a container or other constructs were assigned.
    template< class  T>
    void swap(T& a, T& b){
        T tmp(a);
        a = b;
        b = tmp;
    }
}
#endif