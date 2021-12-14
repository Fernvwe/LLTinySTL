#ifndef __LL_UNINITIALIZD_H__
#define __LL_UNINITIALIZD_H__
#include <type_traits>
#include "llalloc.h"
#include "lliterator.h"
#include "llalgorithm.h"

namespace LL {
template <class InputIt, class ForwardIter>
ForwardIter
unchecked_uninit_copy(InputIt first, InputIt last, ForwardIter result, std::true_type){
    return LL::copy(first,last,result);
}
template <class InputIt, class ForwardIter>
ForwardIter
unchecked_uninit_copy(InputIt first, InputIt last, ForwardIter result, std::false_type){
   auto cur = result;
   try{
       for(; first != last; ++first)
           LL::_construct(&*cur, *first); 
   }catch(...){
       for(;result != cur; ++result)
            LL::_destroy(&*result);
   } 
   return cur;
}
template <class InputIt, class ForwardIter>
ForwardIter uninitialized_copy(InputIt first, InputIt last,
                               ForwardIter result) {
    return  unchecked_uninit_copy(
                first, last,result,
                std::is_trivially_copyable<
                    typename iterator_traits<ForwardIter>::value_type
                    >{}
            );
}

}  // namespace LL
#endif