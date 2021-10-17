#ifndef __LLUTILITY_H__
#define __LLUTILITY_H__
#include "lltype_traits.h"
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

}
#endif


