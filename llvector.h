#ifndef __LLVECTOR_H__
#define __LLVECTOR_H__

#include <assert.h>

#include <initializer_list>  // using initializer_list of stl
#include <stdexcept>
#include <type_traits>

#include "llalgorithm.h"
#include "llalloc.h"
#include "lliterator.h"
/**
 * The complexity (efficiency) of common operations on vectors is as follows:
 *      Random access - constant O(1)
 *      Insertion or removal of elements at the end - amortized constant O(1)
 *      Insertion or removal of elements - linear in the distance to the end of
 *the vector O(n)
 **/
namespace LL {
template <class T, class Alloc = LL::allocator<T>>
class vector {
   public:
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using difference_type = ptrdiff_t;
    using allocator_type = Alloc;
    using const_reverse_iterator = reverse_iterator<const_iterator>;
    using reverse_iterator = reverse_iterator<iterator>;

   private:
    iterator start;
    iterator finish;
    iterator end_of_storage;
    size_type capacity = 7;

   private:
    void insert_aux(const_iterator posi, const value_type& t);
    void remove(const iterator& posi);
    void reallocate_space();

   public:
    // construct/copy/destory
    explicit vector(const Alloc& = Alloc());
    explicit vector(size_type n);
    vector(size_type n, const T& value, const Alloc& = Alloc());
    template <class InputIt, class = typename std::enable_if<
                                 !std::is_integral<InputIt>::value>::type>
    vector(InputIt first, InputIt last, const Alloc& = Alloc());
    vector(vector&&);
    vector(const vector&, const Alloc&);
    vector(vector&&, const Alloc&);
    // TODO initializer_list<T>
    vector(std::initializer_list<T>);
    ~vector();
    vector<T, Alloc>& operator=(const vector<T, Alloc>& x);
    vector<T, Alloc>& operator=(vector<T, Alloc>&& x);

    template <class InputIt>
    void assign(InputIt first, InputIt last);
    void assgin(size_type n, const T& t);
    allocator_type get_Alloc() const noexcept { return Alloc(); }

    iterator begin() noexcept { return start; }
    const_iterator begin() const noexcept { return start; }
    iterator end() noexcept { return finish; }
    const_iterator end() const noexcept { return finish; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept {
        return reverse_iterator(begin());
    }

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend() const noexcept { return rend(); }
    // capacity
    size_type size() { return static_cast<size_type>(end() - begin()); }
    bool empty() { return begin() == end(); }
    T max_size() { return capacity; }

    // element  access
    reference operator[](size_type n) {
        assert(n < size());
        return *(begin() + n);
    }
    reference front() { return *(begin()); }
    reference back() { return *(end() - 1); }
    reference at(size_type pos) {
        assert(pos < size());
        return *(begin() + pos);
    };
    // modifier
    void push_back(value_type&& t);
    void push_back(const value_type& t);
    template <class... Args>
    void emplace_back(Args&&... args);
    void pop_back() { remove(end() - 1); }
    void reserve();
    void clear();
    void insert(const_iterator posi, const value_type& t);
    template <class InputIt>
    void insert(const_iterator posi, InputIt first, InputIt last);
    void erase(const_iterator posi) { remove(posi); }
    void erase(const_iterator first, const_iterator last);

    void swap(vector<T>& rhs) {
        LL::swap(start, rhs.start);
        LL::swap(finish, rhs.finish);
        LL::swap(end_of_storage, rhs.end_of_storage);
        LL::swap(capacity, rhs.capacity);
    }
};
template <class T, class Alloc>
void vector<T, Alloc>::reallocate_space() {
    capacity = 2 * capacity;
    difference_type vec_size = size();
    iterator new_start = Alloc::allocate(capacity);
    copy(start, finish, new_start);
    LL::swap(start, new_start);
    Alloc::deallocate(new_start);
    finish = start + vec_size;
    end_of_storage = start + capacity;
}
template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(const_iterator posi, const value_type& t) {
    auto pos = const_cast<iterator>(posi);
    if (finish == end_of_storage) {
        difference_type gap = pos - start;
        reallocate_space();
        pos = start + gap;
    }
    if (pos > finish) {
        throw "out of bound!";
    } else {
        copy_backward(pos, finish, finish + 1);
        *pos = t;
    }
    ++finish;
}
template <class T, class Alloc>
void vector<T, Alloc>::insert(const_iterator posi, const value_type& t) {
    if(posi == finish)
        push_back(t);
    else
        insert_aux(posi, t);
}
template <class T, class Alloc>
template <class InputIt>
void vector<T, Alloc>::insert(const_iterator posi, InputIt first,
                              InputIt last) {
    assert(first <= last);
    while (first < last) {
        insert(posi, *first);
        ++first;
    }
}
template <class T, class Alloc>
void vector<T, Alloc>::push_back(const vector<T, Alloc>::value_type& t) {
    if (finish != end_of_storage) {
        *finish = t;
    } else {
        reallocate_space();
        allocator_type::construct(finish,t);
    }
    ++finish;
}
template <class T, class Alloc>
void vector<T, Alloc>::push_back(value_type&& t) {
    emplace_back(move(t));    
}
template <class T, class Alloc>
template <class... Args>
void vector<T,Alloc>::emplace_back(Args&&... args){
    if(finish != end_of_storage){
        allocator_type::construct(finish, args...);
    }else{
        reallocate_space();
        allocator_type::construct(finish, args...);
    }
    ++finish;
}
template <class T, class Alloc>
void vector<T, Alloc>::reserve() {
    size_t l = 0, r = size() - 1;
    iterator sta = begin();
    while (l <= r) {
        LL::swap(*(sta + l), *(sta + r));
        ++l;
        --r;
    }
}
template <class T, class Alloc>
void vector<T, Alloc>::clear() {
    allocator_type::desoty(start, finish);
    finish = start;
}
template <class T, class Alloc>
void vector<T, Alloc>::remove(const iterator& posi) {
    allocator_type::destory(posi);
    copy(posi + 1, finish, posi); 
    --finish;
}
template <class T>
void swap(vector<T>& i, vector<T>& j) {
    i.swap(j);
}
template <class T, class Alloc>
vector<T, Alloc>::vector(const Alloc& alloc) {
    start = alloc.allocate(capacity);
    finish = start;
    end_of_storage = start + capacity;
}
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const T& value, const Alloc& alloc) {
    while (n > capacity) {
        capacity *= 2;
    }
    start = alloc.allocate(capacity);
    finish = start;
    end_of_storage = start + capacity;
    size_type i = 0;
    while (i < n) {
        *(start + i) = value;
        ++i;
    }
    finish = start + i;
}
template <class T, class Alloc>
template <class InputIt, class>
vector<T, Alloc>::vector(InputIt first, InputIt last, const Alloc& alloc) {
    while (capacity < last - first) capacity *= 2;
    start = alloc.allocate(capacity);
    end_of_storage = start + capacity;
    iterator tmp = start;
    while (first < last) {
        *tmp = *first;
        ++first;
        ++tmp;
    }
    finish = tmp;
}
// ! some error , need to revise
template <class T, class Alloc>
vector<T, Alloc>::vector(vector&& rhs)
    : start(rhs.start),
      finish(rhs.finish),
      capacity(rhs.capacity),
      end_of_storage(rhs.end_of_storage) {
    rhs.start = nullptr;
    rhs.finish = nullptr;
    rhs.end_of_storage = nullptr;
}
template <class T, class Alloc>
vector<T, Alloc>::vector(std::initializer_list<T> arr) {
    Alloc alloc;
    while (capacity < arr.size()) capacity += capacity;
    start = alloc.allocate(capacity);
    iterator tmp = start;
    for (auto const_val : arr) {
        *tmp = const_val;
        ++tmp;
    }
    finish = tmp;
}
template <class T, class Alloc>
vector<T, Alloc>::~vector() {
    Alloc alloc;
    alloc.deallocate(start);
    finish = nullptr;
    end_of_storage = nullptr;
}
template <class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& x) {
    start = x.start;
    finish = x.finish;
    capacity = x.capacity;
    end_of_storage = x.end_of_storage;
    return *this;
}
template <class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(vector<T, Alloc>&& x) {
    start = x.start;
    finish = x.finish;
    capacity = x.capacity;
    end_of_storage = x.end_of_storage;
    x.start = nullptr;
    x.finish = nullptr;
    x.capacity = nullptr;
}
template <class T, class Alloc>
void vector<T, Alloc>::erase(const_iterator first, const_iterator last) {
    assert(first < last);
    if (last >= finish) {
        return;
    }
    iterator tmp = static_cast<iterator>(last);
    tmp--;
    while (tmp < first) {
        remove(tmp);
        --tmp;
    }
}
template <class T, class Alloc>
template <class InputIt>
void vector<T, Alloc>::assign(InputIt first, InputIt last) {
    if (static_cast<size_type>(last - first) > size()) {
        throw "out of range";
        return;
    }
    iterator tmp = start;
    while (first != last) {
        *tmp = *first;
        ++tmp;
        ++first;
    }
}
template <class T>
void swap(vector<T> x, vector<T> y){
    x.swap(y);
}
}  // namespace LL
#endif
