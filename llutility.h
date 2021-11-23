#ifndef __LLUTILITY_H__
#define __LLUTILITY_H__
#include "lltype_traits.h"
#include "llalgorithm.h"
namespace LL{

template<class T>
typename remove_reference<T>::type && move(T&& t) noexcept{
    return static_cast<typename remove_reference<T>::type &&>(t);
}


template< class T >
T&& forward( typename std::remove_reference<T>::type& t ) noexcept{
    return static_cast<T&&>(t); // reference folding
}
template< class T >
T&& forward( typename std::remove_reference<T>::type&& t ) noexcept{
    return static_cast<T&&>(t);
}

template <class T1, class T2>
struct pair{
    using first_type = T1;
    using second_type = T2;

    first_type first;
    second_type second;

    pair():first(),second(){}
    template <class U, class V>
    pair(const pair<U,V>& x):first(x.first),second(x.second){}

    pair(const first_type& u, const second_type & v ){
        first = u;
        second = v;
    }

    pair<T1,T2>& operator=(const pair<T1,T2>& x){
        first = x.first;
        second = x.second;
    }

    void  swap(pair<T1,T2>& rhs){
        LL::swap(first,rhs.first);
        LL::swap(second, rhs.second);
    }
};

template <class T1, class T2>
LL::pair<T1,T2> make_pair(T1 t, T2 u){
    pair<T1,T2> tmp(t,u);
    return tmp;
}
template <class T1, class T2>
void swap(pair<T1,T2>& lhs, pair<T1,T2>& rhs){
    lhs.swap(rhs);
}
}
#endif


