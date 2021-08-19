#ifndef __LLALLOC__
#define __LLALLOC__

#include <cstddef>// for ptrdiff_t.size_t
#include <new> // for placement new
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace LL{
template  <class T>
inline T* _allocate(ptrdiff_t size, T*){
	std::set_new_handler(0);
	T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if  (tmp == 0){
		std::cerr<<"out of memory" << std::endl;
		exit(0);
	}
}
template  <class T>
inline void _deallocate(T* buffer){
	::operator delete(buffer);
}
template <class T0,class T2>
inline void _construct(T0* p, const T2&  value){
	new(p)  T0(value);
}
template <class T>
inline void _destroy(T* ptr){
	ptr->~T();
}

template <class T>
class allocator{
public:
	// the standard interface
	typedef	T 		value_type;
	typedef	T* 		pointer;
	typedef const T* const_pointer;
	typedef T&		reference;
	typedef const T& const_referrence;
	typedef size_t	size_type;
	typedef  ptrdiff_t difference_type;
	// rebind allocator of type U
	template  <class U>
	struct rebind{
		typedef allocator<U> other;
	};
	pointer allocate(size_type n, const void* hint = 0){
		return _allocate((difference_type)n, (pointer)0);
	}
	void deallocate(pointer p, size_type n){ _deallocate(p); }
	void construct(pointer p, const T& value){
		_construct(p, value);
	}
	void destory(pointer p){ _destroy(p); }

	pointer  address(reference x){
		return (pointer)&x;
	}
	const_pointer const_address(const_referrence x){
		return (const_pointer)&x;
	}

};
}

#endif
