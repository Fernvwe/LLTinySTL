#ifndef __LL_PRIORITY_QUEUE_H__
#define __LL_PRIORITY_QUEUE_H__
#include <functional>
#include <initializer_list>
#include "lliterator.h"
#include "llvector.h"
#include "llalgorithm.h"

namespace LL {
inline size_t _parent(size_t index) { return (index - 1) / 2; }
inline size_t _lchild(size_t index) { return (index * 2) + 1; }
inline size_t _rchild(size_t index) { return (index + 1) * 2; }
template <class T, class Container = vector<T>,
          class Compare = std::less<typename Container::value_type> >
class priority_queue {
   public:
    using container_type = Container;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

   private:
    using self = priority_queue<T, Container, Compare>;

   public:
    Container c;
    Compare comp;

   private:
    void precolateUp(size_type posi);
    void precolateDown(size_type posi);
    value_type getBigChild(size_type posi){
        size_type lc = _lchild(posi);
        size_type rc = _rchild(posi);
        if(rc >= size()) 
            return lc;
        else 
            return comp(c[lc],c[rc]) ? rc : lc;
    }
   public:
    priority_queue() : c(container_type()), comp(Compare()) {}
    priority_queue(const container_type& x){
        c = x;
        // Floyd algorithm of building heap
        for(int i = (c.size()-1)/2; i >= 0; --i){
            precolateDown(i);
        }
    }
    self& operator=(const self& x){
        c = x.c;
        comp = x.comp;
    }
    value_type top() { return c[0]; }
    size_type size() { return c.size(); }
    void push(const value_type& x) {
        c.push_back(x);
        precolateUp(size() - 1);
    }
    template <class... Args>
    void emplace(Args... args);
    void pop(){
        swap(c[0], c[c.size() - 1]);
        c.pop_back();
        precolateDown(0);
    }
    void swap(self& rhs){
        swap(x,rhs.x);
        swap(comp, rhs.comp);
    }
};
template <class T, class Container, class Compare>
void priority_queue<T, Container, Compare>::precolateUp(size_type posi) {
    while (0 < posi) {
        size_type tmp = _parent(posi);
        if (comp(c[posi], c[tmp])) {
            break;
        }
        swap(c[tmp], c[posi]);
        posi = tmp;
    }
}
template <class T, class Container, class Compare>
void priority_queue<T, Container, Compare>::precolateDown(size_type posi) {
    if(c.size() < 2) return;
    size_type bigchild = getBigChild(posi);
    size_type ext = (c.size() - 2)/2;
    while(comp(c[posi],c[bigchild])){
        swap(c[posi], c[bigchild]);
        posi = bigchild;
        if(posi > ext) break;
        bigchild = getBigChild(posi);
    } 
}
}  // namespace LL
#endif