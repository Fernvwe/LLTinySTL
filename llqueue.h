#ifndef __LL_QUEUE_H__
#define __LL_QUEUE_H__
#include "lldeque.h"
namespace LL{
template <class T, class Container = deque<T> >
class queue {
    public:
        using container_type = Container;
        using value_type = typename Container::value_type;
        using size_type = typename Container::size_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
    private:
        using self = queue<T, deque<T>>;
        container_type container;
    public: 
        self operator=(const self& rhs){ container = rhs.container;}
        value_type front(){ return container.front();}
        bool empty(){return container.empty();}
        size_type size(){ return container.size(); }
        void push(const value_type& x ){ container.push_back(x); }
        void pop(){ container.pop_front(); }
        void swap(self & rhs){ container.swap(rhs.container); }

        bool operator==(const self& rhs){return container == rhs.container; }
}; 
}
#endif