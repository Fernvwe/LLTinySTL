#ifndef __LL_HASHTABLE_H__
#define __LL_HASHTABLE_H__
#include <algorithm>

#include "llalloc.h"
#include "llfunctional.h"
#include "llhash_fun.h"
#include "lliterator.h"
#include "lluninitialized.h"
#include "llvector.h"
namespace LL {

template <class Val>
struct hashtable_node {
    hashtable_node* next;
    Val val;
};

template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
class hashtable;
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
struct hashtable_const_iterator;

template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
struct hashtable_iterator;

template <class Val>
struct hashtable_const_local_iterator;

template <class Val>
struct hashtable_local_iterator;
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
struct hashtable_iterator {
    using htb = hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using iterator =
        hashtable_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using const_iterator =
        hashtable_const_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using node = hashtable_node<Val>;

    using iterator_category = LL::forward_iterator_tag;
    using value_type = Val;
    using pointer = Val*;
    using reference = Val&;
    using difference_type = ptrdiff_t;
    using size_type = std::size_t;

    node* cur;
    htb* ht;

    hashtable_iterator(node* n, htb* tab) : cur(n), ht(tab) {}
    hashtable_iterator() {}
    hashtable_iterator(const iterator& rhs) : cur(rhs.cur), ht(rhs.ht) {}
    hashtable_iterator(const const_iterator& rhs) : cur(rhs.cur), ht(rhs.ht) {}
    reference operator*() const { return cur->val; }
    pointer operator->() const { return &(operator*()); }
    iterator& operator++();
    iterator operator++(int) {
        iterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const iterator& it) { return cur == it.cur; }
    bool operator!=(const iterator& it) { return cur != it.cur; }
};
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
typename hashtable_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>::iterator&
hashtable_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>::operator++() {
    const node* old = cur;
    cur = cur->next;
    if (!cur) {  // take the next available bucket
        size_type ind = ht->get_bkt_posi(old->val);
        while (!cur && ++ind < ht->bucket_size) {
            cur = ht->bucket[ind];
        }
    }
    return *this;
}
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
struct hashtable_const_iterator {
    using htb = hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using iterator =
        hashtable_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using const_iterator =
        hashtable_const_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using node = hashtable_node<Val>;

    using iterator_category = LL::forward_iterator_tag;
    using value_type = Val;
    // 常量迭代器和普通迭代器的差别在于是否允许通过迭代器访问元素.
    using pointer = const Val*;
    using reference = const Val&;
    using difference_type = ptrdiff_t;
    using size_type = std::size_t;

    node* cur;
    htb* ht;

    hashtable_const_iterator(node* n, htb* tab) : cur(n), ht(tab) {}
    hashtable_const_iterator() {}
    hashtable_const_iterator(const iterator& rhs) : cur(rhs.cur), htb(rhs.ht) {}
    hashtable_const_iterator(const const_iterator& rhs)
        : cur(rhs.cur), ht(rhs.ht) {}
    reference operator*() const { return cur->val; }
    pointer operator->() const { return &(operator*()); }
    const_iterator& operator++();
    const_iterator operator++(int) {
        const_iterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const const_iterator& it) { return cur == it.cur; }
    bool operator!=(const const_iterator& it) { return cur != it.cur; }
};
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
typename hashtable_const_iterator<Val, Key, HashFunc, EqualKey,
                                  KeyofValue>::const_iterator&
hashtable_const_iterator<Val, Key, HashFunc, EqualKey,
                         KeyofValue>::operator++() {
    const node* old = cur;
    cur = cur->next;
    if (!cur) {  // take the next available bucket
        size_type ind = ht->get_bkt_posi(old->val);
        while (!cur && ++ind < ht->bucket_size) {
            cur = ht->bucket[ind];
        }
    }
    return *this;
}

template <class Val>
struct hashtable_local_iterator {
    using iterator_category = LL::forward_iterator_tag;
    using value_type = Val;
    using pointer = Val*;
    using reference = Val&;
    using difference_type = ptrdiff_t;
    using size_type = std::size_t;

    using node_ptr = hashtable_node<Val>*;
    using local_iterator = hashtable_local_iterator<Val>;
    using const_local_iterator = hashtable_const_local_iterator<Val>;
    node_ptr* cur;

    hashtable_local_iterator(const node_ptr& rhs) : cur(rhs) {}
    hashtable_local_iterator(const local_iterator& rhs) : cur(rhs.node) {}
    hashtable_local_iterator(const const_local_iterator& rhs) : cur(rhs.node) {}
    reference operator*() const { return cur->val; }
    pointer operator->() const { return &(operator*()); }
    local_iterator& operator++() {
        cur = cur->next;
        return *this;
    }
    local_iterator operator++(int) {
        local_iterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const local_iterator& it) { return cur == it.cur; }
    bool operator!=(const local_iterator& it) { return cur != it.cur; }
};

template <class Val>
struct hashtable_const_local_iterator {
    using iterator_category = LL::forward_iterator_tag;
    using value_type = Val;
    using pointer = const Val*;
    using reference = const Val&;
    using difference_type = ptrdiff_t;
    using size_type = std::size_t;

    using node_ptr = hashtable_node<Val>*;
    using local_iterator = hashtable_local_iterator<Val>;
    using const_local_iterator = hashtable_const_local_iterator<Val>;
    node_ptr* cur;

    hashtable_const_local_iterator(const node_ptr& rhs) : cur(rhs) {}
    hashtable_const_local_iterator(const local_iterator& rhs) : cur(rhs.node) {}
    hashtable_const_local_iterator(const const_local_iterator& rhs)
        : cur(rhs.node) {}
    reference operator*() const { return cur->val; }
    pointer operator->() const { return &(operator*()); }
    local_iterator& operator++() {
        cur = cur->next;
        return *this;
    }
    local_iterator operator++(int) {
        local_iterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const local_iterator& it) { return cur == it.cur; }
    bool operator!=(const local_iterator& it) { return cur != it.cur; }
};

/**
 *
 */
enum { _nums_primes = 28 };
static const unsigned long _prime_list[_nums_primes] = {
    53ul,         97ul,         193ul,       389ul,       769ul,
    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
    1610612741ul, 3221225473ul, 4294967291ul};
inline unsigned long _next_prime(unsigned long n) {
    auto first = _prime_list;
    auto last = _prime_list + _nums_primes;
    auto pos = std::lower_bound(first, last, n);
    return pos == last ? *(last - 1) : *pos;
}
/**
Value： 节点的实值类型
Key：   节点的键值类型
HashFcn： hash function的类型
KeyofValue：从节点中取出键值的方法（函数或仿函数）
EqualKey：判断键值是否相同的方法（函数或仿函数）
Alloc：空间配置器
*/
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
class hashtable {
   public:
    using key_type = Key;
    using value_type = Val;
    using hasher = HashFunc;
    using key_equal = EqualKey;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator =
        hashtable_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using const_iterator =
        hashtable_const_iterator<Val, Key, HashFunc, EqualKey, KeyofValue>;
    using local_iterator = hashtable_local_iterator<Val>;
    using const_local_iterator = hashtable_const_local_iterator<Val>;

   public:
    using node_type = hashtable_node<Val>;
    using node_ptr = node_type*;
    using bucket_type = LL::vector<node_ptr>;

    using allocator_type = LL::allocator<Key>;
    using data_allocator = LL::allocator<Val>;
    using node_allocator = LL::allocator<node_type>;

    using self = hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>;

   public:
    bucket_type bucket;
    size_type bucket_size;
    size_type nums_elements;
    hasher hash;
    key_equal equal;

   private:
    node_ptr get_node(const value_type& val);
    void delete_node(node_ptr* ptr) {
        LL::_destroy(&ptr->val);
        node_allocator::deallocate(ptr);
    }
    void initialize_buckets(size_type n);
    node_ptr get1st_node();
    LL::pair<iterator, bool> insert_unique_noresize(const value_type& val);
    iterator insert_equal_noresize(const value_type& val);

   public:
    hashtable(size_type n, const HashFunc& hf, const EqualKey& eql)
        : hash(hf), bucket_size(n), equal(eql), nums_elements(0) {
        initialize_buckets(n);
    }

    hashtable(const hashtable& rhs)
        : hash(rhs.hf),
          bucket_size(rhs.bucket_size),
          equal(rhs.equal),
          nums_elements(rhs.nums_elements) {
        copy_from(rhs);
    }
    hashtable(hashtable&& rhs)
        : hash(rhs.hash),
          bucket_size(rhs.bucket_size),
          equal(rhs.equal),
          nums_elements(rhs.nums_elements) {
        initialize_buckets(bucket_size);
        for (size_type i = 0; i < bucket_size; ++i) {
            bucket[i] = rhs.bucket[i];
            rhs.bucket[i] = nullptr;
        }
    }
    self& operator=(const self& rhs) {
        hash = rhs.hash;
        bucket_size = rhs.bucket_size;
        equal = rhs.equal;
        copy_from(rhs);
    }
    self& operator=(self&& rhs) {
        hash = rhs.hash;
        bucket_size = rhs.bucket_size;
        equal = rhs.equal;
        nums_elements = rhs.nums_elements;
        initialize_buckets(bucket_size);
        for (size_type i = 0; i < bucket_size; ++i) {
            bucket[i] = rhs.bucket[i];
            rhs.bucket[i] = nullptr;
        }
    }
    iterator begin() { return iterator(get1st_node(), this); }
    const_iterator begin() const { return begin(); }
    iterator cbegin() const { return iterator(get1st_node(), this); }
    iterator end() { return iterator(nullptr, this); }
    const_iterator end() const {
        return const_iterator(nullptr, const_cast<self*>(this));
    }
    iterator cend() const { return iterator(nullptr, this); }
    bool empty() const { return get1st_node() == nullptr; }
    size_type size() const { return nums_elements; }
    size_type maxsize() const { return bucket_size; }

    LL::pair<iterator, bool> insert_unique(const value_type& val) {
        resize(nums_elements + 1);
        return insert_unique_noresize(val);
    }
    iterator insert_equal(const value_type& val) {
        resize(nums_elements + 1);
        return insert_equal_noresize(val);
    }
    void resize(const size_type& n);
    size_type get_bkt_posi_imp(const key_type& key,
                               const size_type& n_buckets) {
        return hash(key) / n_buckets;
    }
    size_type get_bkt_posi(const value_type& val) {
        return get_bkt_posi_imp(KeyofValue()(val), bucket_size);
    }
    size_type get_bkt_posi(const value_type& val, const size_type& n_buckets) {
        return get_bkt_posi_imp(KeyofValue()(val), n_buckets);
    }
    void clear();
    void copy_from(const hashtable& ht);

    iterator erase(iterator posi);
    iterator find(const key_type& key);
    size_type count(const key_type& key) { return find(key) == end() ? 0 : 1; }
    size_type multi_count(const key_type& key) {
        size_type posi = get_bkt_posi(key);
        size_type count = 0;
        node_ptr tmp = bucket[posi];
        while (tmp != nullptr) {
            if (key == KeyofValue()(tmp->val)) ++count;
            tmp = tmp->next;
        }
        return count;
    }
    void swap(self& rhs){
        LL::swap(bucket, rhs.bucket);
        LL::swap(bucket_size, rhs.bucket_size);
        LL::swap(equal, rhs.equal);
        LL::swap(hash, rhs.hash);
        LL::swap(nums_elements, rhs.nums_elements);
    }
};
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
typename hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::iterator
hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::find(const key_type& key) {
    size_type posi = get_bkt_posi(key);
    node_ptr tmp = bucket[posi];
    while (tmp != nullptr) {
        if (key == KeyofValue()(tmp->val)) return iterator(tmp, this);
        tmp = tmp->next;
    }
    return iterator(nullptr, this);
}
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
typename hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::iterator
hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::erase(iterator posi) {
    size_type bucketPosi = get_bkt_posi(posi.cur->val);
    iterator ans = ++posi;
    node_ptr tmp = bucket[bucketPosi], pre = nullptr;
    for (; tmp != nullptr; tmp = tmp->next, pre = tmp) {
        if (KeyofValue()(tmp->val) == KeyofValue()(posi.cur->val)) {
            if (KeyofValue()(tmp->val) ==
                KeyofValue()(bucket[bucketPosi].cur->val)) {
                bucket[bucketPosi] = tmp->next;
            } else {
                pre->next = tmp->next;
            }
            node_allocator::deallocate(tmp);
        }
    }
    return ans;
}
// 作用：完整的从另一hashtable复制到当前hashtable中
// 修改成员变量： bucket，nums_elements
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
void hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::copy_from(
    const hashtable& ht) {
    clear();
    bucket = ht.bucket;  // 这里仅复制指针,要再复制一个内容.
    for (size_type i = get1st_node(); i < bucket_size; ++i) {
        node_ptr tmp = bucket[i];
        while (tmp) {
            node_ptr tmpNext = tmp->next;
            tmp = get_node(tmp->val);  // 申请一个新的空间保存val
            tmp->next = tmpNext;  // 新空间的next指向原本的下一个node
            tmp = tmpNext;        // 转到下一node
        }
    }
    nums_elements = ht.nums_elements;
}
// clear() -- 清楚容器所包含所有的数据,并且将所有的bucket[i]设置为nullptr
//  ! 注意: 不光要释放内部所申请的node,同时也要释放node指向的val.
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
void hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::clear() {
    node_ptr first = get1st_node();
    for (size_type i = get_bkt_posi(first->val); i < bucket_size; ++i) {
        first = bucket[i];
        while (first) {
            auto first_next = first->next;
            _destory(&first->val);
            node_allocator::deallocate(first);
            first = first_next;
        }
        bucket[i] = nullptr;
    }
    nums_elements = 0;
}
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
typename hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::node_ptr
hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::get1st_node() {
    for (size_type i = 0; i < bucket_size; ++i) {
        if (bucket[i] != nullptr) return bucket[i];
    }
    return nullptr;
}
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
typename hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::iterator
hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::insert_equal_noresize(
    const value_type& val) {
    size_type posi = get_bkt_posi(val, bucket_size);
    node_ptr new_node = get_node(val);
    for (node_ptr tmp = bucket[posi]; tmp != nullptr; tmp = tmp->next) {
        if (equal(KeyofValue()(tmp->val), KeyofValue()(val))) {
            node_ptr tmp_next = tmp->next;
            tmp->next = new_node;
            new_node->next = tmp_next;
            return iterator(new_node, this);
        }
    }
    new_node = get_node(val);
    new_node->next = bucket[posi];
    bucket[posi] = new_node;
    ++nums_elements;
    return iterator(new_node, this);
}
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
LL::pair<typename hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::iterator,
         bool>
hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::insert_unique_noresize(
    const value_type& val) {
    size_type posi = get_bkt_posi(val, bucket_size);
    for (node_ptr tmp = bucket[posi]; tmp != nullptr; tmp = tmp->next) {
        if (equal(KeyofValue()(tmp->val), KeyofValue()(val))) {
            return make_pair(iterator(tmp, this), false);
        }
    }
    node_ptr new_node = get_node(val);
    new_node->next = bucket[posi];
    bucket[posi] = new_node;
    ++nums_elements;
    return make_pair(iterator(bucket[posi], this), true);
}

template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
void hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::resize(
    const size_type& n) {
    if (n > bucket_size) {
        const size_type n_buckets = _next_prime(n);
        bucket_type tmp(n_buckets, nullptr);
        for (size_type i = 0; i < bucket_size; ++i) {
            node_ptr item_btk = bucket[i];
            while (item_btk) {
                size_type new_btk_posi = get_bkt_posi(item_btk->val, n_buckets);
                bucket[i] = item_btk->next;
                //! make the node as the header of current bucket.
                item_btk->next = tmp[new_btk_posi];
                tmp[new_btk_posi] = item_btk;
                item_btk = bucket[i];
            }
        }
        bucket.swap(tmp);
        bucket_size = n_buckets;
    }
}
// initial buckets and set nodeptr as nullptr

template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
void hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::initialize_buckets(
    size_type n) {
    const size_type n_buckets = _next_prime(n);
    bucket = bucket_type(n_buckets, nullptr);
}
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
typename hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::node_ptr
hashtable<Val, Key, HashFunc, EqualKey, KeyofValue>::get_node(
    const value_type& val) {
    node_ptr n = node_allocator::allocate(1);
    n->next = nullptr;
    try {
        LL::_construct(&n->val, val);
        return n;
    } catch (...) {
        node_allocator::deallocate(n);
    }
    return nullptr;
}
template <class Val, class Key, class HashFunc, class EqualKey,
          class KeyofValue>
void swap(hashtable<Val, Key, HashFunc, EqualKey, KeyofValue> a,
          hashtable<Val, Key, HashFunc, EqualKey, KeyofValue> b) {
    a.swap(b);
}
}  // namespace LL
#endif