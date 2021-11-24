#ifndef __LLBTREE_H__
#define __LLBTREE_H__
#include <vector>
#include <algorithm>
namespace LL{

template <class T>
struct BTree_node{
    BTree_node* parent;
    std::vector<T> keys;
    std::vector<BTree_node*> childs;
};

template <class T>
class BTree{
    public:
        using ptr = BTree_node<T>*;
    private:
        size_t _size;
        size_t _order; // B-树的阶次
        ptr _root;
        ptr _hot;
    private:
        void sloveOverflow(BTree_node<T>* posi);
    public:
        size_t size() const {return _size;}
        BTree_node<T>* search(const T& x);
        bool insert(const T& x);
        bool remove(const T& x);
};
template <class T>
BTree_node<T>* BTree<T>::search(const T& x){
    auto node = _root;
    while(node){
        auto posi = std::search(node->keys.begin(), node->keys.end(), x); 
        size_t r = static_cast<size_t>(posi - node->keys.begin());
        if( r >= 0 && x == node->keys[r])
            return node;
        node = node->child[r + 1];
    }
    return nullptr;
}
template <class T>
void BTree<T>::sloveOverflow(BTree_node<T>* posi){

}
}
#endif