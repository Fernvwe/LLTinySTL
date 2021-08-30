#ifndef __LLMEMORY__
#define __LLMEMORY__

template<class Alloc>
struct allocator_traits{
    // member types
    using allocator_type    = Alloc;
	using value_type		= typename Alloc::value_type;
	using pointer			= typename Alloc::pointer;
	using const_pointer 	= typename Alloc::const_pointer;
	using reference 		= value_type&;
	using const_referrence	= const T&;
	using size_type 		= size_t;
	using difference_type 	= ptrdiff_t;
};

#endif  // __LLMEMORY__

