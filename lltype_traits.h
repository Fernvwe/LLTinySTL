#ifndef __LLTYPE_TRAITS__
#define __LLTYPE_TRAITS__

namespace LL{
// bool class object
struct __true_type{};
struct __false_type{};

// type_traits
template<class type>
struct __type_traits{
    using thsi_dummy_member_must_be_first = __true_type;
    // the default type is false.
    using has_trivial_default_constructor = __false_type;
    using has_trivial_copy_constructor = __false_type;
    using has_trivial_assignment_operator = __false_type;
    using has_trivial_destructor = __false_type;
    using is_POD_type = __false_type;
};
// specialization type_traits
template<>
struct __type_traits<char>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};

template<>
struct __type_traits<unsigned char>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};
template<>
struct __type_traits<short>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};
template<>
struct __type_traits<unsigned short>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};template<>
struct __type_traits<int>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};
template<>
struct __type_traits<unsigned int>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};
template<>
struct __type_traits<long>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};

template<>
struct __type_traits<unsigned long>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};

template<>
struct __type_traits<double>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};
template <class T>
struct __type_traits<T*>{
    using thsi_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __true_type;
    using has_trivial_copy_constructor = __true_type;
    using has_trivial_assignment_operator = __true_type;
    using has_trivial_destructor = __true_type;
    using is_POD_type = __true_type;
};

}

#endif