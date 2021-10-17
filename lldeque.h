#ifndef __LLDEQUE_H__
#define __LLDEQUE_H__

#include <initializer_list>
#include <type_traits>

#include "llalgorithm.h"
#include "llalloc.h"
#include "llconstruct.h"
#include "lliterator.h"
#include "llutility.h"

namespace LL {

template <class T, class Alloc = LL::allocator<T>, size_t BufSiz = 7>
class __deque_iterator {
   public:
    using iterator_category = LL::random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;
    using size_type = std::size_t;
    using self = __deque_iterator<T, Alloc, BufSiz>;

   public:
    pointer cur;
    pointer first;
    pointer last;
    pointer* node;  // node point to the element of map
   public:
    __deque_iterator() {}
    __deque_iterator(pointer* x) {
        node = x;
        first = *(node);
        last = *(node) + BufSiz;
        cur = first;
    }
    pointer operator->() const { return &(operator*()); }
    self& operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--() {
        --cur;
        if (cur < first) {
            set_node(node - 1);
            cur = last - 1;
        }
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }
    reference operator*() { return *cur; }
    // TODO 研究为什么 operator += 这样书写!!!
    self& operator+=(difference_type n) {
        difference_type offset = static_cast<difference_type>(cur - first + n);
        if (offset >= 0 && offset < BufSiz) {
            cur += n;
        } else {
            difference_type node_offset =
                offset > 0
                    ? offset / static_cast<difference_type>(BufSiz)
                    : -static_cast<difference_type>((-offset - 1) / BufSiz) - 1;
            set_node(node + node_offset);
            cur = first + (offset - BufSiz * node_offset);
        }
        return *this;
    }
    self operator+(difference_type n) {
        self tmp = *this;
        return tmp += n;
    }
    self& operator-=(difference_type n) { return *this += -n; }
    self operator-(difference_type n) {
        self tmp = *this;
        return tmp -= n;
    }
    difference_type operator-(const self& x) const {
        difference_type offset =
            static_cast<difference_type>(cur - first + (x.last - x.cur));
        difference_type node_offset =
            static_cast<difference_type>(node - x.node - 1);
        return offset + node_offset * BufSiz;
    }
    reference operator[](difference_type n) const { return *(*this + n); }
    bool operator==(const self& rhs) const { return rhs.cur == cur; }
    bool operator!=(const self& rhs) const { return !(*this == rhs); }
    bool operator<(const self& rhs) const {
        return node == rhs.node ? cur < rhs.cur : node < rhs.node;
    }
    void set_node(pointer* new_node) {
        node = new_node;
        first = *new_node;
        last = first + static_cast<difference_type>(BufSiz);
    }
};

template <class T, class Allocator = LL::allocator<T>, size_t BufSiz = 7>
class deque {
   public:
    using pointer = T*;
    using iterator = __deque_iterator<T>;
    using const_iterator = __deque_iterator<const T>;
    using reverse_iterator = reverse_iterator<iterator>;
    using const_reverse_iterator = const reverse_iterator;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using allocator_type = Allocator;

   private:
    using map_pointer = pointer*;  // pointer array
    using map_alloc_type = LL::allocator<pointer>;

   private:
    iterator start;
    iterator finish;
    map_pointer map;
    size_type map_size = 11;

   private:
    void _insert_after_aux(iterator posi, const T& t);
    void create_map_and_nodes(size_type n);
    void fill_initialize(size_type n, const value_type& t);
    void push_back_aux(const value_type& t);
    void push_front_aux(const value_type& t);
    void pop_back_aux();
    void pop_front_aux();
    void reserve_map_at_back(size_type nodes_to_add = 1);
    void reserve_map_at_front(size_type nodes_to_add = 1);
    void reallocate_map(size_type nodes_to_add, bool add_at_front);

   public:
    // construct/copy/destroy:
    explicit deque(const Allocator& = Allocator());
    explicit deque(size_type n);
    deque(size_type n, const T& value);
    template <class InputIterator,
              class = typename std::enable_if<
                  !std::is_integral<InputIterator>::value>::type>
    deque(InputIterator first, InputIterator last);
    deque(const deque<T, Allocator>& x);
    deque(deque<T, Allocator>&&);
    deque(std::initializer_list<T>);
    ~deque();
    deque<T, Allocator>& operator=(const deque<T, Allocator>& x);
    deque<T, Allocator>& operator=(deque<T, Allocator>&& x);
    deque<T, Allocator>& operator=(std::initializer_list<T>);
    template <class InputIterator,
              class = typename std::enable_if<
                  !std::is_integral<InputIterator>::value>::type>
    void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const T& t);
    void assign(std::initializer_list<T>);
    allocator_type get_allocator() const noexcept { return allocator_type(); }

    // iterators:
    iterator begin() noexcept { return start; }
    const_iterator begin() const noexcept { return start; }
    iterator end() noexcept { return finish; }
    const_iterator end() const noexcept { return finish; }

    reverse_iterator rbegin() noexcept {
        return static_cast<reverse_iterator>(finish);
    }
    const_reverse_iterator rbegin() const noexcept {
        return static_cast<reverse_iterator>(finish);
    }
    reverse_iterator rend() noexcept {
        return static_cast<reverse_iterator>(start);
    }
    const_reverse_iterator rend() const noexcept {
        return static_cast<reverse_iterator>(start);
    }

    const_iterator cbegin() noexcept { return start; }
    const_iterator cend() noexcept { return finish; }
    const_reverse_iterator crbegin() noexcept {
        return static_cast<reverse_iterator>(finish);
    }
    const_reverse_iterator crend() noexcept {
        return static_cast<reverse_iterator>(start);
    }

    // capacity:
    size_type size() const noexcept {
        return static_cast<size_type>(finish - start);
    }
    size_type max_size() const noexcept;
    void resize(size_type sz);
    void resize(size_type sz, const T& c);
    void shrink_to_fit();
    bool empty() const noexcept { return start == finish; }

    // element access:
    reference operator[](size_type n) {
        return start[static_cast<difference_type>(n)];
    }
    const_reference operator[](size_type n) const {
        return start[static_cast<difference_type>(n)];
    }
    reference at(size_type n) { return start[static_cast<difference_type>(n)]; }
    const_reference at(size_type n) const {
        return start[static_cast<difference_type>(n)];
    }
    reference front() { return *start; }
    const_reference front() const { return *start; }
    reference back() {
        // return *(finish - 1);
        iterator tmp = finish;
        --tmp;
        return *tmp;
    }
    const_reference back() const;

    // modifiers:
    template <class... Args>
    void emplace_front(Args&&... args);
    template <class... Args>
    void emplace_back(Args&&... args);
    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args);

    void push_front(const T& x);
    //void push_front(T&& x){ emplace_front(move(x)); }
    void push_back(const T& x);
    //void push_back(T&& x){ emplace_back(move(x)); }

    iterator insert(iterator position, const T& x);
    // iterator insert(const_iterator position, T&& x);
    iterator insert(iterator position, size_type n, const T& x);
    template <class InputIterator>
    iterator insert(iterator position, InputIterator first, InputIterator last);
    iterator insert(iterator position, std::initializer_list<T>);

    void pop_front();
    void pop_back();

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void swap(deque<T, Allocator>&);
    void clear() noexcept;
};

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::create_map_and_nodes(size_type n) {
    map_alloc_type map_alloc;
    allocator_type node_allco;
    size_type node_size = static_cast<size_type>(n / BufSiz + 1);
    // ! the node assgin strategy need redesign.
    map_size = max(node_size + 4, map_size);
    map = map_alloc.allocate(map_size);
    map_pointer nstart = map + (map_size - node_size) / 2;
    // nstart 本身也是一个空间,所以 nfinish被设定为 -1的情况
    map_pointer nfinish = nstart + node_size - 1;
    // ! there may occur exception
    for (map_pointer cur = nstart; cur <= nfinish; ++cur)
        *cur = node_allco.allocate(BufSiz);
    start.set_node(nstart);
    start.cur = *nstart;
    finish.set_node(nfinish);
    finish.cur = *nfinish + static_cast<difference_type>(n % BufSiz);
}
template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::fill_initialize(size_type n,
                                                  const value_type& t) {
    create_map_and_nodes(n);
    map_pointer cur;
    for (cur = start.node; cur < finish.node; ++cur)
        unintialize_fill(*cur, *cur + BufSiz, t);
    unintialize_fill(finish.first, finish.cur, t);
}
template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator, BufSiz>::deque(size_type n, const value_type& t)
    : start(), finish(), map(nullptr) {
    fill_initialize(n, t);
}

template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator, BufSiz>::deque(const Allocator& alloc)
    : start(), finish(), map(nullptr) {
    map_alloc_type map_alloc;
    allocator_type node_alloc;
    map = map_alloc.allocate(map_size);
    map_pointer n_start = map + map_size / 2;
    *(n_start) = node_alloc.allocate(BufSiz);
    start.set_node(n_start);
    finish.set_node(n_start);
    start.cur = start.first;
    finish.cur = start.first;
}

template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator, BufSiz>::deque(size_type n)
    : start(), finish(), map(nullptr) {
    create_map_and_nodes(n);
}
template <class T, class Allocator, size_t BufSiz>
template <class InputIterator, class>
deque<T, Allocator, BufSiz>::deque(InputIterator first, InputIterator last) {
    size_type n = static_cast<size_type>(last - first);
    create_map_and_nodes(n);
    iterator tmp = start;
    for (; first < last; ++first) {
        construct(tmp, *first);
        ++tmp;
    }
}

template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator, BufSiz>::deque(const deque<T, Allocator>& x) {
    size_type n = x.size();
    create_map_and_nodes(n);
    iterator tmp = start;
    iterator x_tmp = x.begin();
    while (x_tmp < x.end()) {
        construct(tmp, *x_tmp);
        ++tmp;
        ++x_tmp;
    }
}
template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator, BufSiz>::deque(deque<T, Allocator>&& x) {
    size_type n = x.size();
    create_map_and_nodes(n);
    iterator tmp = start;
    iterator x_tmp = x.begin();
    while (x_tmp < x.end()) {
        construct(tmp, *x_tmp);
        ++tmp;
        ++x_tmp;
    }
}
template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator, BufSiz>::deque(std::initializer_list<T> x) {
    create_map_and_nodes(x.size());
    iterator tmp = start;
    for (auto const_val : x) {
        construct(tmp.cur, const_val);
        ++tmp;
    }
}
template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator, BufSiz>::~deque() {
    allocator_type node_alloc;
    map_alloc_type map_alloc;
    for (iterator tmp = start; start != finish; ++start) {
        node_alloc.destory(start.cur);
    }
    map_alloc.deallocate(map);
}

template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator>& deque<T, Allocator, BufSiz>::operator=(
    const deque<T, Allocator>& x) {
    if (x != *this) {
        start = x.start;
        finish = x.finish;
        map_size = x.map_size;
        map = x.map;
    }
    return *this;
}

template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator>& deque<T, Allocator, BufSiz>::operator=(
    deque<T, Allocator>&& x) {
    swap(x);
    return *this;
}

template <class T, class Allocator, size_t BufSiz>
deque<T, Allocator>& deque<T, Allocator, BufSiz>::operator=(
    std::initializer_list<T> x) {
    deque tmp(x);
    swap(x);
    return *this;
}
template <class T, class Allocator, size_t BufSiz>
template <class InputIterator,
          class>  // using SFINAE to avoid some matching problems
void deque<T, Allocator, BufSiz>::assign(InputIterator first,
                                         InputIterator last) {
    for (iterator tmp = start; tmp < finish && first < last; ++tmp) {
        construct(tmp, *first);
        ++tmp;
        ++first;
    }
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::assign(size_type n, const T& t) {
    iterator tmp = start;
    while (n-- > 0 && tmp < finish) {
        construct(tmp.cur, t);
        ++tmp;
    }
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::assign(std::initializer_list<T> _list) {
    iterator tmp = start;
    for (auto val : _list) {
        if (tmp < finish) construct(tmp++, val);
    }
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::push_back(const T& x) {
    if (finish.cur != finish.last - 1) {
        construct(finish.cur, x);
        ++finish.cur;
    } else {
        push_back_aux(x);
    }
}
template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::push_front(const T& x) {
    if (start.cur != start.first) {
        --start.cur;
        construct(start.cur, x);
    } else {
        push_front_aux(x);
    }
}
template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::push_back_aux(const T& x) {
    if (finish.node + 1 == map + map_size) reserve_map_at_back();
    allocator_type buffer_alloc = Allocator();
    *(finish.node + 1) = buffer_alloc.allocate(BufSiz);
    *(finish.cur) = x;
    ++finish;
}
template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::push_front_aux(const T& x) {
    if (start.node == map) reserve_map_at_front();
    allocator_type buffer_alloc = Allocator();
    *(start.node - 1) = buffer_alloc.allocate(BufSiz);
    --start;
    // 这里还有一个空间,可以直接存入数据.而后再跳转到下一Buffer
    *(start.cur) = x;
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::pop_back() {
    assert(size() > 0);
    if (finish.cur != finish.first || finish.node == start.node) {
        _destroy(--finish.cur);
    } else {
        pop_back_aux();
    }
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::pop_back_aux() {
    // finish.cur -1 == finish.start && finish.node != start.node
    // free node
    allocator_type node_alloc;
    map_pointer tmp = finish.node;
    --finish;
    _destroy(finish.cur);
    node_alloc.deallocate(*tmp);
    tmp = nullptr;
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::pop_front() {
    assert(size() > 0);
    if (start.cur != start.last - 1 || start.node == finish.node) {
        pointer tmp = start.cur++;
        _destroy(tmp);
    } else {
        pop_front_aux();
    }
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::pop_front_aux() {
    allocator_type node_alloc;
    map_pointer tmp_node = start.node;
    pointer tmp_cur = start.cur;
    _destroy(tmp_cur);
    node_alloc.deallocate(*tmp_node);
    ++start;
}

template <class T, class Allocator, size_t BufSiz>
typename deque<T, Allocator, BufSiz>::iterator
deque<T, Allocator, BufSiz>::erase(iterator position) {
    if(position == finish - 1){
        pop_back();
    }else if(position == start){
        pop_front();
    }else{
        copy(position + 1, finish, position);
        pop_back();
    }
    return position;
}
template <class T, class Allocator, size_t BufSiz>
typename deque<T, Allocator, BufSiz>::iterator
deque<T,Allocator,BufSiz>::erase(iterator first, iterator last){
    size_type _len = static_cast<difference_type>(last - first);
    assert(_len < size());
    copy(last,finish,first);
    for(int i = 0; i < _len; ++i)
        pop_back();
    return first;
}

template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::reserve_map_at_back(size_type nodes_to_add) {
    // * 任务是申请新的空间,同时保持相对的map分布不变.
    if (nodes_to_add + 1 > map_size - static_cast<size_type>(finish.node - map))
        reallocate_map(nodes_to_add, false);
}
template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::reserve_map_at_front(size_type nodes_to_add) {
    // * 任务是申请新的空间,同时保持相对的map分布不变.
    if (nodes_to_add + 1 > static_cast<size_type>(start.node - map))
        reallocate_map(nodes_to_add, true);
}
template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::reallocate_map(size_type nodes_to_add,
                                                 bool add_at_front) {
    size_type old_num_nodes = finish.node - start.node + 1;
    size_type new_num_nodes = old_num_nodes + nodes_to_add;

    map_pointer new_nstart;
    // 如果出现一端数据过于长,而一端几乎没有数据,则重新修改node的起点
    if (map_size > 2 * new_num_nodes) {
        // 为什么当 add_at_front is true,
        // 起点会向后偏移,为在前面插入的元素留下空间
        new_nstart = map + (map_size - new_num_nodes) / 2 +
                     (add_at_front ? nodes_to_add : 0);
        if (new_nstart < start.node)
            copy(start.node, finish.node + 1, new_nstart);
        else
            copy_backward(start.node, finish.node + 1,
                          new_nstart + old_num_nodes);
    } else {  // 如果实在是空间不足,则需要重新申请一个map空间
        map_alloc_type map_alloc;
        size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
        map_pointer new_map = map_alloc.allocate(new_map_size);
        new_nstart = new_map + (new_map_size - new_num_nodes) / 2 +
                     (add_at_front ? nodes_to_add : 0);
        copy(start.node, finish.node + 1, new_nstart);
        map_alloc.deallocate(map);
        map = new_map;
        map_size = new_map_size;
    }
    start.set_node(new_nstart);
    finish.set_node(new_nstart + old_num_nodes - 1);
}

template <class T, class Allocator, size_t BufSiz>
typename deque<T, Allocator, BufSiz>::iterator
deque<T, Allocator, BufSiz>::insert(iterator posi, const value_type& t) {
    if (posi == finish)
        push_back(t);
    else if (posi == start - 1)
        push_front(t);
    else {
        if (static_cast<difference_type>(posi - start) > size() / 2) {
            value_type end_val = *((finish - 1).cur);
            copy_backward(posi, finish - 1, finish);
            *posi.cur = t;
            push_back(end_val);
        } else {
            value_type sta_val = *(start.cur);
            copy(start + 1, posi + 1, start);
            *posi.cur = t;
            push_front(sta_val);
        }
    }
    return posi;
}

// template <class T, class Allocator, size_t BufSiz>
// template <class... Args>
// void deque<T,Allocator,BufSiz>::emplace_back(Args&&... args){
//     if(finish.cur != finish.last - 1){
//         construct(finish.cur, forward<Args>(args)...);
//         ++finish.cur;
//     }else{
//         reserve_map_at_back();
//         construct(finish.cur, forward<Args>(args)...);
//         ++finish;
//     }
// }
template <class T, class Allocator, size_t BufSiz>
void deque<T, Allocator, BufSiz>::swap(deque<T, Allocator>& x) {
    swap(start, x.start);
    swap(finish, x.finish);
    swap(map, x.map);
    swap(map_size, x.map_size);
}
template <typename T>
void swap(deque<T> x, deque<T> y) {
    x.swap(y);
}
}  // namespace LL

#endif
