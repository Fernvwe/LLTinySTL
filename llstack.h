#ifndef __LL_STACK_H__
#define __LL_STACK_H__
#include "lldeque.h"

namespace LL {

template <class T, class Container = deque<T> >
class stack {
    public:
        using container_type = Container;
        using value_type = typename Container::value_type;
        using size_type = typename Container::size_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
    private:
        using self = stack<T, deque<T>>;
        container_type container;
    public:
        stack():container(container_type()){}
        self operator=(const self& rhs){ container = rhs.container;}
        value_type top(){ return container.front();}
        bool empty(){return container.empty();}
        size_type size(){ return container.size(); }
        void push(const value_type& x ){ container.push_front(x); }
        void pop(){ container.pop_front(); }
        void swap(self & rhs){ container.swap(rhs.container); }

        bool operator==(const self& rhs){return container == rhs.container; }
};
// todo 
// template<class T, class Container>
// bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs){ return lhs == rhs; }
// template<class T, class Container>
// bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs){ return lhs != rhs; }
// template<class T, class Container>
// bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs){ return lhs < rhs; }
// template<class T, class Container>
// bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs){ return lhs < rhs; }
}  // namespace LL
#endif